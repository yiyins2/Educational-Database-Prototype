#pragma once

#include <vector>

#include "../include/file_block_id.hpp"
#include "lock_table.hpp"


using namespace std;

class concurrency_manager {
    public:
        void global_lock(block_id *p_blk);
        void release();
    
    private:
        static lock_table table;
        vector<block_id *> locks;
};