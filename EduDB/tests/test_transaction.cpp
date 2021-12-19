#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "../include/transaction.hpp"

using namespace std;

void task_one(transaction *tx, file_block_idx *blk) {
    tx->pin(blk);
    cout << "first time reading from block " << blk->get_filename() << endl;
    int val = tx->read(blk);
    cout << "second time reading from block " << blk->get_filename() << endl;
    val = tx->read(blk);
    tx->commit();
    cout << "finished reading" << endl;
}

void task_two(transaction *tx, file_block_idx *blk) {
    tx->pin(blk);
    cout << "first time writing from block " << blk->get_filename() << endl;
    tx->write(blk, 10, 0);
    cout << "second time writing from block " << blk->get_filename() << endl;
    tx->write(blk, 10, 0);
    tx->commit();
    cout << "finished writing" << endl;
}

int main(int argc, char *argv[]) {
    //Transaction test
    file_manager fm = file_manager("transaction_test");
    buffer_manager bm = buffer_manager(fm, 8);

    transaction *tx1 = new transaction(fm, bm);
    file_block_idx *blk = new file_block_idx("test_block", 1);
    tx1->pin(blk);
    tx1->write(blk, 10, 40);
    tx1->commit();

    transaction *tx2 = new transaction(fm, bm);
    tx2->pin(blk);
    int val = tx2->read(blk);
    cout << "The created value from offset 40 is: " << val << endl;
    tx2->commit();

    //Concurrency tests
    thread t1(task_one, tx1, blk);
    thread t2(task_two, tx2, blk);
    t1.join();
    t2.join();
}