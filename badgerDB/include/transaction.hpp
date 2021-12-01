#pragma once

#include "file_manager.hpp"
#include "concurrency_manager.hpp"
#include "buffer_manager.hpp"

class transaction {
    private:
        int curr_tx_num;
        static int next_tx_num;
        concurrency_manager * cm;
        buffer_manager * bm;
        file_manager * fm;
        mutex m;
        int set_next_txn();

    public:
        transaction(file_manager* fm, buffer_manager * bm);
        void commit();
        void pin(file_block_idx* blk);
        void unpin(file_block_idx* blk);
        int read(file_block_idx *blk);
        void write(file_block_idx *blk, int val, int offset);
};