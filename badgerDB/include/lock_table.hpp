#pragma once

#include "file_block_idx.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

class lock_table {
    private:
        queue<file_block_idx *> wait_list;
        mutex m;
        condition_variable cv;
        // const int wait_time = 3000;
        // const int lock_time = 5000;
    
    public:
        lock_table();
        void global_lock(file_block_idx *blk_id);
        void global_unlock();
};