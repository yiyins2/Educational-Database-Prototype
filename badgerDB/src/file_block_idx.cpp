#include "../include/file_block_idx.hpp"

file_block_idx::file_block_idx(string filename, int blk_id)
{
	this->filename = filename;
	this->blk_id = blk_id;
}

string file_block_idx::get_filename()
{
	return filename;
}

int file_block_idx::get_blk_id()
{
	return blk_id;
}