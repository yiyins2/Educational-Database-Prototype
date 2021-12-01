#include "../include/transaction.hpp"
#include <iostream>
#include <string>
using namespace std;

int transaction::next_tx_num = 0;

transaction::transaction(file_manager* fm_mgr, buffer_manager* bm_mgr) : fm(fm_mgr), bm(bm_mgr){
    //bad implementation using new keyword, will solve in the future
    cm = new concurrency_manager();
    //set transaction id to keep track of them
    curr_tx_num = set_next_txn();
}

void transaction::commit() {
    cm->release();
    bm->unpin_all();
}

void transaction::pin(file_block_idx *blk) {
    bm->pin(blk);
}

void transaction::unpin(file_block_idx *blk) {
    bm->unpin(blk);
}

int transaction::read(file_block_idx *blk) {
    cm->global_lock(blk);
    buffer* bf = bm->find_linked_buffer(blk);
    if (!bf) {
        cout << "The block doesn't exist to read, please try again" << endl;
        return -1;
    }
    return *(bf->get_page()->get_buf());
} 

void transaction::write(file_block_idx *blk, int val, int offset) {
    cm->global_lock(blk);
    //find the corresponding buffer according to block_id, if any
    buffer* bf = bm->find_linked_buffer(blk);
    if (!bf) {
        cout << "The block doesn't exist to write, please try again" << endl;
    } else {
        //set_buf is something I created myself, please refer to isabella's version for modification.
        //bf->get_page()->set_buf(val, offset);
        bf->setTransaction(curr_tx_num);
    }
} 

int transaction::set_next_txn() {
    lock_guard<mutex> lock(m);
    next_tx_num++;
    return next_tx_num;
}