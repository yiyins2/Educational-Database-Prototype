#pragma once

#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>

#include "page.h"
#include "block_id.h"
using namespace std;

class file_manager {
	private:
		string db_dir;
		int block_size;

		fstream get_file_handle(string filename);

	public:
		file_manager(string db_dir, int block_size=512);
		int read(block_id blk, page p);
		int write(block_id blk, page p);
		int add_block(string filename);
		int get_file_block_cnt(string filename);
		int get_block_size();
		string get_complete_file_path(string filename);
};