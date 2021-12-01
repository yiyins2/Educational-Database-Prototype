#include "../include/concurrency_manager.hpp"
using namespace std;

lock_table concurrency_manager::table;

void concurrency_manager::global_lock(file_block_idx *p_blk) {
    table.global_lock(p_blk);
    locks.push_back(p_blk);
}

void concurrency_manager::release() {
    for (file_block_idx *p : locks) {
        table.global_unlock();
    }
    locks.clear();
}