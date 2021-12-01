#pragma once

#include "file_block_idx.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

class lock_table {
    private:
        const int lockTime = 5000;
        queue<file_block_idx *> wait_list;
        mutex m;
        condition_variable cv;
        const int wait_time = 3000;
    
    public:
        lock_table();
        void global_lock(file_block_idx *p_blk);
        void global_unlock();
};