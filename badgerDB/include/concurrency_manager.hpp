#pragma once

#include "file_block_idx.hpp"
#include "lock_table.hpp"
#include "vector"
using namespace std;

class concurrency_manager {
    public:
        void global_lock(file_block_idx *p_blk);
        void release();
    
    private:
        static lock_table table;
        vector<file_block_idx *> locks;
};