#ifndef RECORD_H
#define RECORD_H

template <typename T>
struct Record {
  T key;
  long position;
  Record(T key, long position) : key(key), position(position) {}
};

#endif  // RECORD_H
