#pragma once

#include <string>

using namespace std;

class file_block_idx {
	private:
		string filename;
		int blk_id;

	public:
		file_block_idx(string filename, int blk_id);
		string get_filename();
		int get_blk_id();
};