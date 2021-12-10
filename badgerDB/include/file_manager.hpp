#pragma once

#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <filesystem>

#include "page.hpp"
#include "file_block_idx.hpp"
#include "record.hpp"
#include "messages.hpp"

using namespace std;

class file_manager {
	private:
		string db_dir;
		int block_size;

		string get_complete_file_path(string filename);

	public:
		file_manager(string db_dir = "./db", int block_size = 512);
		int read(file_block_idx blk, page p);
		int write(file_block_idx blk, page p);
		int add_block(string filename);
		int get_file_block_cnt(string filename);
		int get_block_size();
		void delete_file(string filename);
		void create_data_file(string filename);
};