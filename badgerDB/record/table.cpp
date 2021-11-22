#include <cerrno>

#include "table.hpp"
#include "../file_manager/page.hpp"

const int BUFFER_SIZE = 512;

table::table(string table_name, file_manager fm) {
	this->record_num = 0;
	this->block_size = fm.get_block_size();
	this->table_name = table_name;
	this->fm = fm;
	fm.add_block(table_name);
}

pair<int, int> table::get_block_id_and_offset(int record_idx) {
	int block_record_num = (this->block_size) / this->record_num;
	int block_idx = record_idx / block_record_num;
	int offset = record_idx % block_record_num;
	return make_pair<>(block_idx, offset);
}

int table::insert_record(record new_record) {
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
	if (fm.read(blk_id, p) < 0) {
		string s = "Failed to read block: " + to_string(block_idx);
		perror(s.c_str());
		return -1;
	}

	p.write_record(new_record, offset);

	if (fm.write(blk_id, p) < 0) {
		string s = "Failed to read block: " + to_string(block_idx);
		perror(s.c_str());
		return -1;
	}

	return 0;
}

vector<record> table::select() {
	return vector<record>();
}

string table::get_table_name() {
	return this->table_name;
}