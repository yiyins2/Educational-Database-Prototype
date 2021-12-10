#include "../include/file_manager.hpp"

#include <cstdio>
#include <cerrno>
#include <cstdlib>

#include "../include/page.hpp"
#include "../include/file_block_idx.hpp"

using namespace std;

// Constructor
file_manager::file_manager(string db_dir, int block_size) {
	this->db_dir = db_dir;
	this->block_size = block_size;
	if (block_size < 0) {
		perror("Block size given to file manager is smaller than 0!");
	}

	struct stat info;
	if (stat(db_dir.c_str(), &info) != 0) {
		system(("mkdir " + db_dir).c_str());
	}
}

// Private utility function
string file_manager::get_complete_file_path(string filename) {
	string complete_file_path = this->db_dir + "/" + filename;
	return complete_file_path;
}

// Public methods called by table
int file_manager::read(file_block_idx blk, page p) {
	string filename = blk.get_filename();
	string dir = get_complete_file_path(filename);

	// Open the file
	ifstream f;
	f.open(get_complete_file_path(filename));

	int blk_id = blk.get_blk_id();
	f.seekg(blk_id * block_size, ios::beg);
	f.read((char*)p.get_buf(), block_size * sizeof(int));

	if (!f) {
		return -1;  
	}

	f.close();
	return 0;
}

int file_manager::write(file_block_idx blk, page p) {
	string filename = blk.get_filename();
	int cur_block_num = get_file_block_cnt(filename);
	while (cur_block_num < blk.get_blk_id() + 1) {
		add_block(filename);
		++cur_block_num;
	}

	// Open the file
	ofstream f;
	f.open(get_complete_file_path(filename));

	int blk_id = blk.get_blk_id();
	f.seekp(blk_id * block_size, ios::beg);
	f.write((char*)p.get_buf(), block_size * sizeof(int));
	f.close();

	return 0;
}

int file_manager::add_block(string filename) {
	fstream f;
	f.open(get_complete_file_path(filename));

	// New free block
	int new_block[block_size];
	memset(new_block, 0, block_size * sizeof(int));

	int blk_id = get_file_block_cnt(filename);
	f.seekg(blk_id * block_size, ios::beg);
	f.write((char*)new_block, block_size*sizeof(int));
	f.close();
	return 0;
}

int file_manager::get_file_block_cnt(string filename) {
	ifstream f;
	f.open(get_complete_file_path(filename));
	
	int begin = f.tellg();
	f.seekg(0, ios::end);
	int end = f.tellg();
	int fsize = (end - begin);

	return fsize / (block_size * sizeof(int));
}

int file_manager::get_block_size() {
	return block_size;
}

void file_manager::delete_file(string filename) {
	system(("rm " + get_complete_file_path(filename)).c_str());
}

void file_manager::create_data_file(string filename) {
	ofstream new_data_file(get_complete_file_path(filename));
	new_data_file.close();
}