#include <iostream>
#include "../include/Bucket.h"
using namespace std;

void testing_bucket_indexes() {
  BucketIndex b0;
  b0.zero = 1;
  b0.one = 2;
  b0.writeToFile(0, "index.dat");

  BucketIndex b2;
  b2.zero = 3;
  b2.one = 4;
  b2.writeToFile(1, "index.dat");


  BucketIndex b1;
  b1.readFromFile(0, "index.dat");
  b1.show();

  BucketIndex b3;
  b3.readFromFile(1, "index.dat");
  cout << "#############\n";
  b3.show();
}

void testing_bucket_records() {
  BucketRecord<char, 3> br0;
  BucketRecord<char, 3> br2;

  br0.insert('1', 0);
  br0.writeToFile(0, "test.dat");
  br2.insert('8',1);
  br2.writeToFile(1, "test.dat");

  BucketRecord<char, 3> br1;
  BucketRecord<char, 3> br3;

  br1.readFromFile(0, "test.dat");
  br3.readFromFile(1, "test.dat");
  br1.show();
  br3.show();
}

