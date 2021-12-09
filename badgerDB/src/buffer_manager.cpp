#include "../include/buffer_manager.hpp"
#include <chrono>
#include <iostream>

using namespace std;

buffer_manager::buffer_manager(file_manager fm, int buff_num) {
    available_num = buff_num;
    for (int i = 0; i < buff_num; i++) {
        buffer_pool.emplace_back(buffer(fm));
    }
}

int buffer_manager::available() {
    //lock the process to prevent inconsistant result
    lock_guard<mutex> lock(m);
    return available_num;
}

void buffer_manager::flush(int txn_num) {
    //lock the process to prevent inconsistant result
    lock_guard<mutex> lock(m);
    for (auto buffer : buffer_pool) {
        if (buffer->curr_transaction() == txn_num) {
            buffer->flush();
        }
    }
}

void buffer_manager::unpin(buffer *bf) {
    //lock the process to prevent inconsistant result
    lock_guard<mutex> lock(m);
    bf->unpin();
    if (!bf->isPinned()) {
        available_num++;
        cv.notify_all();
    }
}

void buffer_manager::unpin(file_block_idx *blk) {
    buffer *bf = find_linked_buffer(blk);
    if (bf) {
        unpin(bf);
    }
}

void buffer_manager::unpin_all() {
    for (auto buffer : buffer_pool) {
        buffer->unpin();
    }
}

buffer *buffer_manager::pin(file_block_idx *blk) {
    //lock the process to prevent inconsistant result
    unique_lock<mutex> lock(m);
    auto start = chrono::high_resolution_clock::now();
    try {
        buffer *bf = pin_attempt(blk);
        while (!bf && !wait_too_long(start)) {
            cout << "No buffer space, waiting for other transactions if any." << endl;
            cv.wait_for(lock, chrono::milliseconds(1000));
            bf = pin_attempt(blk);
        }
        //if buffer is still not assigned after long time period, throws exception.
        if (!bf) {
            throw runtime_error("Buffer Manager Abort");
        }
        return bf;
    } catch (exception e) {
        cout << "Buffer Maganger Abort: not enough space" << endl;
        throw runtime_error("Buffer Manager Abort");
    }
}

buffer *buffer_manager::pin_attempt(file_block_idx *blk) {
    buffer *bf = find_linked_buffer(blk);
    //if no linked buffer not found, choose an unpinned buffer and link it to block
    if (!bf) {
        bf = unpinned_buffer();
        if (!bf) {
            return nullptr;
        }
        bf->link_block(blk);
    }
    if (!bf->isPinned()) {
        available_num--;
    }
    bf->pin();
    return bf;
}

buffer *buffer_manager::find_linked_buffer(file_block_idx *blk) {
    for (auto buffer : buffer_pool) {
        file_block_idx *b = buffer->get_block();
        if (!b && b == blk) {
            return buffer;
        }
    }
    return nullptr;
}

buffer *buffer_manager::unpinned_buffer() {
    for (auto buffer : buffer_pool) {
        if (!buffer->isPinned()) {
            return buffer;
        }
    }
    return nullptr;
}

bool buffer_manager::wait_too_long(chrono::time_point<std::chrono::high_resolution_clock> start) {
    auto end = std::chrono::high_resolution_clock::now();
    return chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > MAX_TIME;
}