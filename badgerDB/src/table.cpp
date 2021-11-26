#include <cerrno>

#include "../include/table.hpp"
const int BUFFER_SIZE = 512;

// Constructor
table::table(string table_name, file_manager fm)
{
	this->record_num = 0;
	this->block_size = fm.get_block_size();
	this->table_name = table_name;
	this->fm = fm;
	fm.add_block(table_name);
}

// Private utility functions
pair<int, int> table::get_block_id_and_offset(int record_idx, int record_size)
{
	int block_record_num = this->block_size / record_size;
	int block_idx = record_idx / block_record_num;
	int offset = (record_idx % block_record_num) * record_size;
	return make_pair<>(block_idx, offset);
}

string table::get_table_name()
{
	return this->table_name;
}

bool table::check_one_field(int record_value, string op, int threshold)
{
	if (strcmp(op.c_str(), ">") == 0)
	{
		return record_value > threshold;
	}

	if (strcmp(op.c_str(), "<") == 0)
	{
		return record_value < threshold;
	}

	if (strcmp(op.c_str(), ">=") == 0)
	{
		return record_value >= threshold;
	}

	if (strcmp(op.c_str(), "<=") == 0)
	{
		return record_value <= threshold;
	}

	if (strcmp(op.c_str(), "==") == 0)
	{
		return record_value == threshold;
	}

	if (strcmp(op.c_str(), "!=") == 0)
	{
		return record_value != threshold;
	}
	return false;
}

bool table::check_predicate(vector<predicate> preds, record r)
{
	vector<int> field_values = r.get_value();

	// TODO:
	for (predicate pr : preds)
	{
		int record_value = r.get_value()[pr.field_idx];
		string op = pr.op;
		int threshold = pr.value;
		if (!check_one_field(record_value, op, threshold))
		{
			return false;
		}
	}
	return true;
}

// Public methods called by query_executor
int table::insert_record(record new_record, int record_size)
{
    // Determine where we should insert the record
	auto pr = get_block_id_and_offset(this->record_num++, record_size);
	int block_idx = pr.first;
	int offset = pr.second;

    // In case there is not enough block
	int cur_block_num = this->fm.get_file_block_cnt(this->table_name);
	while (cur_block_num++ < block_idx + 1)
	{
		this->fm.add_block(this->table_name);
	}

    // Read the block
	page p = {BUFFER_SIZE};
	file_block_idx blk_id = {this->table_name, block_idx};
	if (this->fm.read(blk_id, p) < 0)
	{
	    return FAILED_TO_READ_BLOCK;
	}

    // Write the new record
	p.write_record(new_record, offset);

    //
	if (this->fm.write(blk_id, p) < 0)
	{
        return FAILED_TO_WRITE_BLOCK;
	}

	return SUCCESS;
}

int table::update_records(vector<update_record> update_record_info, vector<predicate> preds, int record_field_num)
{
	string table_name = this->table_name;

	// Total number of block in the data file
	int table_block_num = this->fm.get_file_block_cnt(table_name);
	// Current record idx
	int record_idx = 0;
	// Maximum number of records that can be in one block (the remaining byte in the block is abandoned)
	int max_block_record_num = this->block_size / record_field_num;

	// First iterate blocks, in each block check each record
	// For each record, check whether they satisfy the requirement
	// If yes, update it
	for (int block_idx = 0; block_idx < table_block_num; ++block_idx)
	{
		page p = {BUFFER_SIZE};
		int *buf = p.get_buf();
		file_block_idx file_blk_idx = {table_name, block_idx};
		if (this->fm.read(file_blk_idx, p))
		{
		    return FAILED_TO_READ_BLOCK;
		}

		// Record idx in the current block
		int current_block_record_idx = 0;
		while (record_idx < this->record_num && current_block_record_idx < max_block_record_num)
		{
			vector<int> field_values;
			for (int i = record_field_num * current_block_record_idx; i < record_field_num * (current_block_record_idx + 1); ++i)
			{
				field_values.push_back(buf[i]);
			}
			record r = {table_name, field_values};

			// Check predicate
			if (check_predicate(preds, r))
			{
				for (update_record ur : update_record_info)
				{
					buf[current_block_record_idx * record_field_num + ur.field_pos_idx] = ur.new_value;
				}
			}

			file_block_idx file_blk_idx = {table_name, block_idx};
			int ret_val = this->fm.write(file_blk_idx, p);
            if (ret_val < 0) {
                return ret_val;
            }

			++record_idx;
			++current_block_record_idx;
		}
	}
	return 0;
}

vector<record> table::select_records(vector<int> select_fields, vector<predicate> preds, int record_field_num)
{
	vector<record> result;

	string table_name = this->table_name;
	int current_block_num = this->fm.get_file_block_cnt(table_name);
	int record_idx = 0;
	int max_block_record_num = this->block_size / record_field_num;

	for (int block_idx = 0; block_idx < current_block_num; ++block_idx)
	{
		page p = {BUFFER_SIZE};
		int *buf = p.get_buf();
		file_block_idx file_blk_id = {table_name, block_idx};
		if (this->fm.read(file_blk_id, p))
		{
			return vector<record>{};
		}

		int current_block_record_idx = 0;
		while (record_idx < this->record_num && current_block_record_idx < max_block_record_num)
		{
			vector<int> field_values;
			for (int i = record_field_num * current_block_record_idx; i < record_field_num * (current_block_record_idx + 1); ++i)
			{
				field_values.push_back(buf[i]);
			}
			record r = {table_name, field_values};

			// Check predicate
			if (check_predicate(preds, r))
			{
				vector<int> record_selected_fields;
				for (int idx : select_fields)
				{
					record_selected_fields.push_back(field_values[idx]);
				}
				record selected_field_r = {table_name, record_selected_fields};
				result.push_back(selected_field_r);
			}

			++record_idx;
			++current_block_record_idx;
		}
	}

	return result;
}
