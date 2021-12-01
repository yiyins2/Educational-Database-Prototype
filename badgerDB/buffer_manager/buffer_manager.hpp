#pragma once
#include <vector>
#include <condition_variable>
#include <mutex>

#include "buffer.hpp"
#include "../file_manager/file_manager.hpp"

using namespace std;
class buffer_manager {
    private:
        vector<buffer *> buffer_pool;
        int available_num;
        mutex m;
        condition_variable cv;
         int MAX_TIME = 10000;
        buffer *pin_attempt(block_id *blk);
        buffer *find_linked_buffer(block_id *blk);
        buffer *unpinned_buffer();
        bool wait_too_long(chrono::time_point<std::chrono::high_resolution_clock> start);

    public:
        buffer_manager(file_manager *fm, int buff_num);
        int available();
        void flush(int txn_num);
        buffer *pin(block_id *blk);
        void unpin(buffer *bf);
};