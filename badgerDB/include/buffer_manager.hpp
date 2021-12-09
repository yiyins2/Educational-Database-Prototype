#pragma once
#include <vector>
#include <condition_variable>
#include <mutex>

#include "buffer.hpp"
#include "file_manager.hpp"

using namespace std;
class buffer_manager {
    private:
        vector<buffer *> buffer_pool;
        int available_num;
        mutex m;
        condition_variable cv;
        const int MAX_TIME = 10000;
        buffer *pin_attempt(file_block_idx *blk);
        buffer *unpinned_buffer();
        bool wait_too_long(chrono::time_point<std::chrono::high_resolution_clock> start);

    public:
        buffer_manager(file_manager fm, int buff_num);
        int available();
        void flush(int txn_num);
        buffer *find_linked_buffer(file_block_idx *blk);
        buffer *pin(file_block_idx *blk);
        void unpin(buffer *bf);
        void unpin(file_block_idx *blk);
        void unpin_all();
};