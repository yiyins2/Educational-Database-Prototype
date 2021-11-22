#include <iostream>
#include <string>
#include <vector>
#include "buffer_manager.hpp"
#include "../file_manager/file_manager.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    //Test buffer without buffer manager
    file_manager *fm = new file_manager("fm");
    buffer *buff1 = new buffer(fm);
    page *p = buff1->get_page();
    buff1->setTransaction(1);
    int num = 0;
    p->set_buf(num, 30);
    cout << "The new value for buffer is " << buff1->get_page()->get_buf() << endl;


    //Test buffer manager
    buffer_manager *bm = new buffer_manager(fm, 3);
    vector<buffer *> buffers(5);
    //pin 3 buffers
    buffers[0] = bm->pin(new block_id("testfile", 0));
    buffers[1] = bm->pin(new block_id("testfile", 1));
    buffers[2] = bm->pin(new block_id("testfile", 2));
    //unpin the first block, but repin the second block
    bm->unpin(buffers[0]);
    buffers[0] = nullptr;
    buffers[3] = bm->pin(new block_id("testfile", 1));
    cout << "Available buffers in the buffer manager: " << bm->available() << endl;
    buffers[4] = bm->pin(new block_id("testfile", 3));
    bm->unpin(buffers[1]);
    //Should not print the below command due to the Buffer Manager Abort
    cout << "Available buffers in the buffer manager: " << bm->available() << endl;
}