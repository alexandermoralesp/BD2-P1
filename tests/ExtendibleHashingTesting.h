#ifndef EXTENDIBLEHASHINGTESTING_H
#define EXTENDIBLEHASHINGTESTING_H
#include "../include/ExtendibleHashing.h"
using namespace std;
void filesize_testing() {
  BucketRecord<char, 3> bucket0;
  bucket0.insert('1',0);
  bucket0.insert('2',2);
  bucket0.writeToFile(0, "data.dat");
  size_t size_file = get_size_of_file("data.dat");
  cout << "Size of file: "  << size_file << endl;

  BucketRecord<char, 3> bucket3;
  bucket3.insert('3', 0);
  bucket3.writeToFile(1, "data.dat");
  size_file = get_size_of_file("data.dat");
  cout << "Size of file: "  << size_file << endl;

  BucketRecord<char, 3> bucket2;
  bucket2.insert('3', 0);
  bucket2.writeToFile(2, "data.dat");
  size_file = get_size_of_file("data.dat");
  cout << "Size of file: "  << size_file << endl;
}
void extendiblehashing_insert_testing() {
  ExtendibleHashing<char,3, 3> eh("insert_file");
  eh.insert('A', 0);
  eh.readAllIndexes();
  // eh.readAllBuckets();
}

#endif
