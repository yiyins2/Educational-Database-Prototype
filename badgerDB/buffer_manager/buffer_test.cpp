#include <iostream>
#include <string>
#include "buffer.hpp"
#include "../file_manager/file_manager.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    file_manager *fm = new file_manager("fm");
    buffer *buff1 = new buffer(fm);
    page *p = buff1->get_page();
    buff1->setTransaction(1);
    string temp = "testing";
    char str[temp.length() + 1];
    strcpy(str, temp.c_str());
    p->set_buf(str);
    cout << "The new value is "; 
    cout << buff1->get_page()->get_buf() << endl;
}