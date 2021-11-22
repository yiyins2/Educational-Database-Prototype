#include "lock_table.hpp"
#include <iostream>
#include <chrono>
using namespace std;

lock_table::lock_table() {}

void lock_table::global_lock(block_id * p_blk) {
    unique_lock<std::mutex> lock(m);
    wait_list.push(p_blk);
    cv.wait(lock, [this, p_blk]{return wait_list.front() == p_blk;});
}

void lock_table::global_unlock() {
    if (!wait_list.empty()) {
        wait_list.pop();
        cv.notify_all();
    }
}
