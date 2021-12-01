#include "concurrency_manager.hpp"

using namespace std;

lock_table concurrency_manager::table;

void concurrency_manager::global_lock(block_id *p_blk) {
    table.global_lock(p_blk);
    locks.push_back(p_blk);
}

void concurrency_manager::release() {
    for (block_id *p : locks) {
        table.global_unlock();
    }
    locks.clear();
}