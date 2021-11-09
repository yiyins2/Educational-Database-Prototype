#include "block_id.h"

block_id::block_id(string filename, int blk_id)
{
	this->filename = filename;
	this->blk_id = blk_id;
}

string block_id::get_filename()
{
	return filename;
}

int block_id::get_blk_id()
{
	return blk_id;
}