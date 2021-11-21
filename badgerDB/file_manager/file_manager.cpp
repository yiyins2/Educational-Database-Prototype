#include <cstdio>
#include <cerrno>
#include <cstdlib>

#include "block_id.hpp"
#include "page.hpp"
#include "file_manager.hpp"

using namespace std;

fstream* file_manager::get_file_handle(string filename)
{
	fstream *f = new(fstream);
	string file_dir = get_complete_file_path(filename);

	f->open(file_dir);

	if (!f) {
		system(("touch " + file_dir).c_str());
		// Create the file
		f->open(file_dir);
	}
	return f;
}

file_manager::file_manager(string db_dir, int block_size)
{
	this->db_dir = db_dir;
	this->block_size = block_size;
	if (block_size < 0)
	{
		perror("Block size given to file manager is smaller than 0!");
	}

	struct stat info;
	if (stat(db_dir.c_str(), &info) != 0)
	{
		system(("mkdir " + db_dir).c_str());
	}
}

int file_manager::read(block_id blk, page p)
{
	string filename = blk.get_filename();

	// Open the file
	fstream *f = get_file_handle(filename);

	int blk_id = blk.get_blk_id();
	f->seekg(blk_id * block_size, ios::beg);
	f->read((char*)p.get_buf(), block_size * sizeof(int));

	if (!f)
	{
		return -1;  
	}

	f->close();
	return 0;
}

int file_manager::write(block_id blk, page p)
{
	string filename = blk.get_filename();
	int cur_block_num = get_file_block_cnt(filename);
	while (cur_block_num < blk.get_blk_id() + 1)
	{
		add_block(filename);
		++cur_block_num;
	}

	// Open the file
	fstream *f = get_file_handle(filename);

	int blk_id = blk.get_blk_id();
	f->seekg(blk_id * block_size, ios::beg);
	f->write((char*)p.get_buf(), block_size * sizeof(int));
	f->close();

	return 0;
}

int file_manager::add_block(string filename)
{
	fstream *f = get_file_handle(filename);

	// New free block
	char new_block[block_size];
	memset(new_block, 0, block_size);

	int blk_id = get_file_block_cnt(filename);
	f->seekg(blk_id * block_size, ios::beg);
	f->write(new_block, block_size);
	f->close();
	return 0;
}

int file_manager::get_file_block_cnt(string filename)
{
	fstream *f = get_file_handle(filename);

	int begin = f->tellg();
	f->seekg(0, ios::end);
	int end = f->tellg();
	int fsize = (end - begin);

	return fsize / block_size;
}

int file_manager::get_block_size()
{
	return block_size;
}

string file_manager::get_complete_file_path(string filename)
{
	string complete_file_path = this->db_dir + "/" + filename;
	return complete_file_path;
}

int file_manager::delete_file(string filename) {
	fstream f;
	string file_dir = get_complete_file_path(filename);

	f.open(file_dir);

	if (!f)
	{
		return -1;
	}

	system(("rm " + file_dir).c_str());
	return 0;
}