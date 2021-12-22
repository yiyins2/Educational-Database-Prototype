#include "../include/concurrency_manager.hpp"
#include <algorithm>
using namespace std;

lock_table concurrency_manager::table;

void concurrency_manager::global_lock() {
    table.global_lock();
}

void concurrency_manager::shared_lock(string table_name) {
    if (find(locks.begin(), locks.end(), table_name) == locks.end()) {
        table.shared_lock(table_name);
        locks.push_back(table_name);
    }
}

void concurrency_manager::exclusive_lock(string table_name) {
    if (find(locks.begin(), locks.end(), table_name) == locks.end()) {
        table.exclusive_lock(table_name);
        locks.push_back(table_name);
    }
}

void concurrency_manager::release() {
    table.global_unlock();
    for (string name : locks) {
        table.unlock(name);
    }
    locks.clear();
}