#ifndef BUCKET_H
#define BUCKET_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>

template <typename KeyType, int FactorBlock>
struct BucketRecord {
    // TODO: Cambiar por map para tener acceso O(1)
  KeyType keys[FactorBlock];
  long positions[FactorBlock];
  int size;
  long next;
  BucketRecord() {
    this->size = 0;
    this->next = -1;
  };
  void insert(KeyType key, long position) {
    if (size == FactorBlock) throw("Bucket Record is full\n");
    for (size_t i = 0; i < FactorBlock; i++)
    {
      if (keys[i] == key) return;
    }
    keys[size] = key;
    positions[size] = position;
    size++;
  }

  void remove(KeyType key) {
    for (size_t i = 0; i < FactorBlock; i++)
    {
      if (keys[i] == key) {
        keys[i] = keys[size-1];
        positions[i] = positions[size-1];
        size--;
        return;
      }
    }
  }

  // Show Bucket Record
  void show() {
    std::cout << "Bucket Record ->";
    std::cout << "Size: " << size << std::endl;
    for (size_t i = 0; i < size; i++)
    {
      std::cout << "Key: " << keys[i] << " Position: " << positions[i] << std::endl;
    }
  }
  int get_size() {
    return sizeof(int) + sizeof(long) +  sizeof(KeyType)*FactorBlock + sizeof(long)*FactorBlock;
  }
  void readFromFile(long pos, std::string filename) {
    BucketRecord<KeyType, FactorBlock> br;
    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    if (!fin.is_open()) throw ("File not open");
    fin.seekg(pos*this->get_size(), std::ios::beg);
    fin.read((char*)&this->size, sizeof(int));
    fin.read((char*)&this->next, sizeof(long));
    for (size_t i = 0; i < FactorBlock; i++) {
      fin.read((char*)&this->keys[i], sizeof(KeyType));
      fin.read((char*)&this->positions[i], sizeof(long));
    }
    fin.close();
    return;
  }
  void writeToFile(long pos, std::string filename){
    std::ofstream fout(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!fout.is_open()) throw ("File not open");
    fout.seekp(pos*this->get_size(), std::ios::beg);
    fout.write((char*)&size, sizeof(int));
    fout.write((char*)&next, sizeof(long));
    for (size_t i = 0; i < FactorBlock; i++)
    {
      fout.write((char*)&this->keys[i], sizeof(KeyType));
      fout.write((char*)&this->positions[i], sizeof(long));
    }
    fout.close();
  }
};

struct BucketIndex {
  int bit;
  long zero;
  long one;
  bool isLeaf;
  BucketIndex() {
    this->bit = -1;
    this->isLeaf = false;
    this->zero = -1;
    this->one = -1;
  }
  BucketIndex(int bit, bool isLeaf) {
    this->bit = bit;
    this->isLeaf = isLeaf;
    this->zero = -1;
    this->one = -1;
  }
  ~BucketIndex() = default;
  void show() {
    std::cout << "Bucket Index ->";
    std::cout << "Bit: " << bit << " IsLeaf: " << isLeaf << std::endl;
    std::cout << "Zero: " << zero << " One: " << one << std::endl;
  }
  size_t get_size() {
    return sizeof(bit) + sizeof(zero) + sizeof(one) + sizeof(isLeaf);
  }
  void readFromFile(long pos, std::string filename) {
    BucketIndex bi(-1, false);
    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    if (!fin.is_open()) throw ("File not open");
    fin.seekg(pos*this->get_size(), std::ios::beg);
    fin.read((char*)&this->bit, sizeof(int));
    fin.read((char*)&this->zero, sizeof(long));
    fin.read((char*)&this->one, sizeof(long));
    fin.read((char*)&this->isLeaf, sizeof(bool));
    fin.close();
    return;
  }
  void writeToFile(long pos, std::string filename) {
    std::ofstream fout(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!fout.is_open()) throw ("File not open");
    fout.seekp(pos*this->get_size(), std::ios::beg);
    fout.write((char*)&bit, sizeof(int));
    fout.write((char*)&zero, sizeof(long));
    fout.write((char*)&one, sizeof(long));
    fout.write((char*)&isLeaf, sizeof(bool));
    fout.close();
  }
};

#endif