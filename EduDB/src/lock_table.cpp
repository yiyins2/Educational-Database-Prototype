#include "../include/lock_table.hpp"
#include <iostream>
#include <chrono>
using namespace std;

lock_table::lock_table() {
    has_global = false;
}

//WARNING: Don't use global lock with shared or exclusive lock, they are supposed to be in different modes. 
void lock_table::global_lock() {
    unique_lock<std::mutex> lock(m);
    has_global = true;
}

void lock_table::shared_lock(string table_name) {
    unique_lock<std::mutex> lock(m);
    auto start = chrono::high_resolution_clock::now();
    cv.wait(lock, [this, table_name, start]{return (!has_global && 
                                                    !has_exclusive_lock(table_name)) ||
                                                    (wait_too_long(start));});
    if (has_global || has_exclusive_lock(table_name)) {
        throw runtime_error("Lock Confliction Abort");
    }
    locks[table_name] = get_lock_val(table_name) + 1;
}

void lock_table::exclusive_lock(string table_name) {
    unique_lock<std::mutex> lock(m);
    auto start = chrono::high_resolution_clock::now();
    cv.wait(lock, [this, table_name, start]{return (!has_global && 
                                                    !has_shared_lock(table_name) &&
                                                    !has_exclusive_lock(table_name)) ||
                                                    (wait_too_long(start));});
    if (has_global || has_shared_lock(table_name) || has_exclusive_lock(table_name)) {
        throw runtime_error("Lock Confliction Abort");
    }
    locks[table_name] = -1;
}

void lock_table::global_unlock() {
    unique_lock<std::mutex> lock(m);
    if (has_global) {
        has_global = false;
        cv.notify_all();
    }
}

void lock_table::unlock(string table_name) {
    unique_lock<std::mutex> lock(m);
    int val = get_lock_val(table_name);
    if (val > 1) {
        locks[table_name]--;
    } else {
        locks.erase(table_name);
        cv.notify_all();
    }
}

bool lock_table::has_shared_lock(string table_name) {
    return get_lock_val(table_name) > 0;
}

bool lock_table::has_exclusive_lock(string table_name) {
    return get_lock_val(table_name) < 0;
}

int lock_table::get_lock_val(string table_name) {
  auto iter = locks.find(table_name);
  if (iter != locks.end()) {
      return iter->second;
  } else {
      return 0; 
  }
}

bool lock_table::wait_too_long(chrono::time_point<std::chrono::high_resolution_clock> start) {
    auto end = std::chrono::high_resolution_clock::now();
    return chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > 10000;
}
