#pragma once

#include "file_block_idx.hpp"
#include <map>
#include <mutex>
#include <condition_variable>
#include <string>
#include <chrono>
using namespace std;

class lock_table {
    private:
        //For simplicity, the size of wait list is one
        map<string, int> locks;
        //WARNING: Don't use global lock with shared or exclusive lock, they are supposed to be in different modes. 
        bool has_global;
        mutex m;
        condition_variable cv;
        bool has_shared_lock(string table_name);
        bool has_exclusive_lock(string table_name);
        int get_lock_val(string table_name);
        bool wait_too_long(chrono::time_point<std::chrono::high_resolution_clock> start);
    
    public:
        lock_table();
        void global_lock();
        void global_unlock();
        void shared_lock(string table_name);
        void shared_unlock(string table_name);
        void exclusive_lock(string table_name);
        void exclusive_unlock(string table_name);
        void unlock(string table_name);
};