#include "../include/buffer.hpp"
#include <memory>
using namespace std;

buffer::buffer(file_manager *fmgr) : fm(fmgr) {
    contents = make_unique<page>(fmgr->get_block_size());
}

page* buffer::get_page() {
    return contents.get();
}

file_block_idx* buffer::get_block() {
    return blk;
}

void buffer::setTransaction(int txn_num) {
    this->txn_num = txn_num;
}

int buffer::currTransaction() {
    return txn_num;
}

void buffer::link_block(file_block_idx *blk) {
    //flush dirty data and reset pins before linking block
    flush();
    pins = 0;
    this->blk = blk;
    fm->read(*(this->blk), *contents);
}

void buffer::flush() {
    if (txn_num > 0) {
        fm->write(*blk, *contents);
        txn_num = -1;
    }
}

//Used for buffer manager
bool buffer::isPinned() {
    return pins > 0;
}

//Used for buffer manager
void buffer::pin() {
    pins++;
}

//Used for buffer manager
void buffer::unpin() {
    pins--;
}