#pragma once

#include "../file_manager/block_id.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

class lock_table {
    private:
        const int lockTime = 5000;
        queue<block_id *> wait_list;
        mutex m;
        condition_variable cv;
        const int wait_time = 3000;
    
    public:
        lock_table();
        void global_lock(block_id *p_blk);
        void global_unlock();
};