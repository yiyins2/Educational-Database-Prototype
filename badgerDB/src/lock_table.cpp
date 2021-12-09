#include "../include/lock_table.hpp"
#include <iostream>
#include <chrono>
using namespace std;

lock_table::lock_table() {}

void lock_table::global_lock(file_block_idx* blk_id) {
    unique_lock<std::mutex> lock(m);
    wait_list.push(blk_id);
    cv.wait(lock, [this, blk_id]{return wait_list.front() == blk_id;});
}

void lock_table::global_unlock() {
    if (!wait_list.empty()) {
        wait_list.pop();
        cv.notify_all();
    }
}
