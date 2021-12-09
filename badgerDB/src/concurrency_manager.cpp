#include "../include/concurrency_manager.hpp"
using namespace std;

lock_table concurrency_manager::table;

void concurrency_manager::global_lock(file_block_idx *blk_id) {
    table.global_lock(blk_id);
    locks.push_back(blk_id);
}

void concurrency_manager::release() {
    for (file_block_idx *p : locks) {
        table.global_unlock();
    }
    locks.clear();
}