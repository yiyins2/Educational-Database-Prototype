#include "buffer.hpp"
#include <memory>
using namespace std;

buffer::buffer(file_manager *fmgr) : fm(fmgr) {
    contents = make_unique<page>(fmgr->get_block_size());
}

page* buffer::get_page() {
    return contents.get();
}

block_id* buffer::get_block() {
    return blk;
}

void buffer::setTransaction(int txn_num) {
    this->txn_num = txn_num;
}

bool buffer::isPinned() {
    return pins > 0;
}

int buffer::currTransaction() {
    return txn_num;
}

void buffer::link_block(block_id *blk) {
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

void buffer::pin() {
    pins++;
}

void buffer::unpin() {
    pins--;
}