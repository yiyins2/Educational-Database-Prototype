#pragma once

#include "file_block_idx.hpp"
#include "lock_table.hpp"
#include "vector"
#include "string"

using namespace std;

class concurrency_manager {
    public:
        void global_lock();
        void shared_lock(string table_name);
        void exclusive_lock(string table_name);
        void release();
    
    private:
        static lock_table table;
        vector<string> locks;
};