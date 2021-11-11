#pragma once

#include <string>
using namespace std;

class block_id {
	private:
		string filename;
		int blk_id;

	public:
		block_id(string filename, int blk_id);
		string get_filename();
		int get_blk_id();
};