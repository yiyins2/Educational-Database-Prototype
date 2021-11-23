#include <cerrno>

#include "table.hpp"
#include "../file_manager/page.hpp"

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
pair<int, int> table::get_block_id_and_offset(int record_idx)
{
	int block_record_num = (this->block_size) / this->record_num;
	int block_idx = record_idx / block_record_num;
	int offset = record_idx % block_record_num;
	return make_pair<>(block_idx, offset);
}

string table::get_table_name()
{
	return this->table_name;
}

bool table::check_predicate(vector<predicate> preds, record r) {
	vector<int> field_values = r.get_value();
	// TODO:
	return true;
}

// Public methods called by query_executor
int table::insert_record(record new_record)
{
	auto pr = get_block_id_and_offset(this->record_num++);
	int block_idx = pr.first;
	int offset = pr.second;

	int cur_block_num = this->fm.get_file_block_cnt(this->table_name);
	while (cur_block_num++ < block_idx + 1)
	{
		this->fm.add_block(this->table_name);
	}

	page p = {BUFFER_SIZE};
	block_id blk_id = {this->table_name, block_idx};
	if (this->fm.read(blk_id, p) < 0)
	{
		string s = "Failed to read block: " + to_string(block_idx);
		perror(s.c_str());
		return -1;
	}

	p.write_record(new_record, offset);

	if (this->fm.write(blk_id, p) < 0)
	{
		string s = "Failed to read block: " + to_string(block_idx);
		perror(s.c_str());
		return -1;
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
		int* buf = p.get_buf();
		block_id blk_id = {table_name, block_idx};
		if (this->fm.read(blk_id, p))
		{
			string s = "Failed to read block: " + to_string(block_idx);
			perror(s.c_str());
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
