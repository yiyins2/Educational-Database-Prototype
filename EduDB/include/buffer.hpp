#pragma once
#include <memory>

#include "file_manager.hpp"
#include "page.hpp"
#include "file_block_idx.hpp"

using namespace std;
class buffer {
    private:
        file_manager *fm;
        //use of unique pointer due to temporal usage of page.
        unique_ptr<page> contents;
        file_block_idx* blk = nullptr;
        int pins = 0;
        int txn_num = -1;

    public:
        buffer(file_manager *fm);
        page *get_page();
        file_block_idx* get_block();
        void setTransaction(int tx_num);
        bool isPinned();
        int currTransaction();
        void link_block(file_block_idx *blk);
        void flush();
        void pin();
        void unpin();
};