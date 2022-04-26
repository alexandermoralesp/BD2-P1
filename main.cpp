#include <iostream>

#include "ExtendibleHashing.h"

using namespace std;
void testing_write() {
    Record<std::string> r0(0, "0");
    Record<std::string> r1(1, "1");
    Record<std::string> r2(2, "2");
    Record<std::string> r3(3, "3");
    ExtendibleHashing<std::string, 3> eh("records", 3);
    eh.insert("0", r0);
    eh.insert("1", r1);
    eh.insert("2", r2);
    eh.insert("3", r3);
}
void testing_read_indexes() {
    ifstream fileRead("records.index.dat", std::ios::binary);
    if (!fileRead.is_open()) throw("errro");
    BucketIndex index(0,0);
    fileRead.seekg(sizeof(BucketIndex)*2, std::ios::beg);
    fileRead.read((char*)&index, sizeof(BucketIndex));
    fileRead.close();
    index.show();
}

void testing_read_bucketrecords() {
    ifstream fileRead("records.index.dat", std::ios::binary);
    if (!fileRead.is_open()) throw("errro");
    BucketRecord<std::string,3> index;
//    fileRead.seekg(sizeof(index.get_size())*2, std::ios::beg);
    fileRead.read((char*)&index, sizeof(index.get_size()));
    fileRead.close();
    index.show();
}
int main() {
    try {
//        testing_write();
//        testing_read_indexes();
        testing_read_bucketrecords();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}