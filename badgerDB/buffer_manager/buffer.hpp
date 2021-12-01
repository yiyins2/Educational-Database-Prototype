#pragma once

#include <memory>

#include "../include/file_manager.hpp"
#include "../include/page.hpp"
#include "../include/file_block_id.hpp"

using namespace std;
class buffer {
    private:
        file_manager *fm;
        //use of unique pointer due to temporal usage of page.
        unique_ptr<page> contents;
        block_id* blk = nullptr;
        int pins = 0;
        int txn_num = -1;

    public:
        buffer(file_manager *fm);
        page *get_page();
        block_id* get_block();
        void setTransaction(int tx_num);
        bool isPinned();
        int currTransaction();
        void link_block(block_id *blk);
        void flush();
        void pin();
        void unpin();
};