#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#include "file_manager.h"
using namespace std;

void test_block_id()
{
	string filename = "test_block.txt";
	int blk_id = 10;
	block_id bd = block_id(filename, blk_id);
	assert(strcmp(bd.get_filename().c_str(), filename.c_str()) == 0);
	assert(bd.get_blk_id() == blk_id);
}

void test_file_manager()
{
	string db_dir = "../db";
	struct stat info;
	if (stat(db_dir.c_str(), &info) == 0) {
		system(("rm -r " + db_dir).c_str());
	}

	// Assign a new file manager
	file_manager fm = file_manager(db_dir, 3);

	// Check whether there exists db directory;
	
	assert(stat(db_dir.c_str(), &info) == 0);

	string filename1 = "1.txt";
	assert(fm.get_file_block_cnt(filename1) == 0);
	assert(fm.get_block_size() == 3);

	fm.add_block(filename1);
	assert(fm.get_file_block_cnt(filename1) == 1);
	fm.add_block(filename1);
	assert(fm.get_file_block_cnt(filename1) == 2);

	// Test file manager write
	page p = page(3);
	strcpy(p.get_buf(), "123");
	block_id blk_id1 = block_id(filename1, 0);
	fm.write(blk_id1, p);

	// Test file manager read
	page read_p1 = page(3);
	block_id read_blk_id1 = block_id(filename1, 0);
	fm.read(read_blk_id1, read_p1);

	char *buf1 = read_p1.get_buf();
	assert(buf1[0] == '1');
	assert(buf1[1] == '2');

	// Test file manager write
	page p2 = page(3);
	strcpy(p2.get_buf(), "34");
	block_id blk_id2 = block_id(filename1, 0);
	fm.write(blk_id2, p2);

	// Test file manager read
	page read_p2 = page(3);
	block_id read_blk_id2 = block_id(filename1, 0);
	fm.read(read_blk_id2, read_p2);

	char *buf2 = read_p2.get_buf();
	assert(buf2[0] == '3');
	assert(buf2[1] == '4');
}

int main(int argc, char *argv[])
{
	test_block_id();
	test_file_manager();
}