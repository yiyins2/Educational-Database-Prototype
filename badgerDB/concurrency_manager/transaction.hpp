#pragma once

#include "../include/file_manager.hpp"
#include "../concurrency_manager/concurrency_manager.hpp"
#include "../buffer_manager/buffer_manager.hpp"

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
        void pin(block_id* blk);
        void unpin(block_id* blk);
        int read(block_id *blk);
        void write(block_id *blk, int val, int offset);
};