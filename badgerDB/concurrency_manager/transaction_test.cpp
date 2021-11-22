#include <iostream>
#include <string>
#include <vector>
#include "transaction.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    file_manager *fm = new file_manager("transaction_test");
    buffer_manager *bm = new buffer_manager(fm, 8);

    transaction *tx1 = new transaction(fm, bm);
    block_id *blk = new block_id("test_block", 1);
    tx1->pin(blk);
    tx1->write(blk, 10, 40);
    tx1->commit();

    transaction *tx2 = new transaction(fm, bm);
    tx2->pin(blk);
    int val = tx2->read(blk);
    cout << "The created value from offset 40 is: " << val << endl;
    tx2->commit();
}