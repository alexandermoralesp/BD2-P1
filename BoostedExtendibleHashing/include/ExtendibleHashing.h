#ifndef EXTENDIBLE_HASHING_H
#define EXTENDIBLE_HASHING_H

#include <bitset>
#include <exception>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "./BucketLeaf.h"
#include "./BucketNotLeaf.h"
#include "./Record.h"

const int depth = 3;

template <typename T>
class ExtendibleHashing {
 private:
  std::string bucketleaf_filename;
  std::string bucketnotleaf_filename;
  std::hash<T> hash_function;

 public:
  ExtendibleHashing(std::string filename);
  ~ExtendibleHashing();
  void insert(T key, long position);
  void remove(T key);
  bool find(T key);
  void show();
  Record<T> search(T key);
  void readAllNotLeafsBuckets();
  void readAllLeafsBuckets();

 private:
  size_t get_size_of_file(std::string filename);
  void initialize_bucket_files();
};

template <typename T>
ExtendibleHashing<T>::ExtendibleHashing(std::string filename) {
  this->bucketleaf_filename = "./bin/" + filename + ".bucketleaf.dat";
  this->bucketnotleaf_filename = "./bin/" + filename + ".bucketnotleaf.dat";
}

template <typename T>
ExtendibleHashing<T>::~ExtendibleHashing() {
}


template <typename T>
void ExtendibleHashing<T>::insert(T key, long position) {
  // Get hash code
  size_t hash_number = hash_function(key) % (1 << depth);
  std::string hash_code = std::bitset<depth>(hash_number).to_string();
  

  // Get size of not leaf bucket file
  size_t size_index_notleaf_file =
      get_size_of_file(this->bucketnotleaf_filename);
  if (size_index_notleaf_file == 0) {
    // Create new bucket leaf and not leaf
    initialize_bucket_files();
  }

  // Update sizes
  size_index_notleaf_file = get_size_of_file(this->bucketnotleaf_filename);
  size_t size_index_leaf_file = get_size_of_file(this->bucketleaf_filename);

  // Temporal Bucket Not Leaf
  BucketNotLeaf current;
  current.read_from_file(this->bucketnotleaf_filename, 0);
  // Iterate through the buckets not leaf
  int i = 0;
  long current_pos = 0;
  while (!current.isLeaf && i < depth) {
    if ('1' == hash_code[i]) {
      current_pos = current.one;
      current.read_from_file(this->bucketnotleaf_filename, current.one);
    } else {
      current_pos = current.zero;
      current.read_from_file(this->bucketnotleaf_filename, current.zero);
    }
    i++;
  }

  // When current is leaf, the position of the bucket record is zero
  size_t bucket_position = current.zero;
  BucketLeaf<T> bucket_leaf;
  bucket_leaf.read_from_file(this->bucketleaf_filename, bucket_position);
  // Number of records in the bucket
  size_t number_of_notleaf = size_index_notleaf_file / current.get_sizeof();
  size_t number_of_leaf = size_index_leaf_file / bucket_leaf.get_sizeof();

  if (bucket_leaf.size_ < FACTOR_BLOCK) {
    bucket_leaf.add_element(key, position);
    bucket_leaf.write_to_file(this->bucketleaf_filename, bucket_position);
    return;
  } else if (bucket_leaf.size_ == FACTOR_BLOCK && i == depth) {
    while (bucket_leaf.next_ != -1) {
      bucket_position = bucket_leaf.next_;
      bucket_leaf.read_from_file(this->bucketleaf_filename, bucket_position);
    }
    if (bucket_leaf.size_ < FACTOR_BLOCK) {
      bucket_leaf.add_element(key, position);
      bucket_leaf.read_from_file(this->bucketleaf_filename, bucket_position);
    } else {
      BucketLeaf<T> new_bucket_leaf;
      new_bucket_leaf.add_element(key, position);
      bucket_leaf.read_from_file(this->bucketleaf_filename, number_of_leaf);
      bucket_leaf.next_ = bucket_position;
      bucket_leaf.read_from_file(this->bucketleaf_filename, bucket_position);
    }
  } else {
    BucketNotLeaf new_zero;
    BucketNotLeaf new_one;
    new_zero.bit = 0;
    new_one.bit = 1;
    new_zero.isLeaf = true;
    new_one.isLeaf = true;

    BucketLeaf<T> new_bucket_leaf_zero;
    BucketLeaf<T> new_bucket_leaf_one;
    if (hash_code[i] == '1')
      new_bucket_leaf_one.add_element(key, position);
    else
      new_bucket_leaf_zero.add_element(key, position);

    for (auto it = bucket_leaf.elements_->begin();
         it != bucket_leaf.elements_->end(); it++) {
      size_t hash_number = hash_function(it->first) % (1 << depth);
      std::string hash_code_key = std::bitset<depth>(hash_number).to_string();
      if (hash_code_key[i] == '1') {
        new_bucket_leaf_one.add_element(it->first, it->second);
      } else {
        new_bucket_leaf_zero.add_element(it->first, it->second);
      }
    }

    new_bucket_leaf_zero.write_to_file(this->bucketleaf_filename,
                                       bucket_position);
    new_bucket_leaf_one.write_to_file(this->bucketleaf_filename,
                                      number_of_leaf);

    current.zero = number_of_notleaf;
    current.one = number_of_notleaf + 1;
    current.isLeaf = false;

    BucketNotLeaf zero_child(0, true);
    zero_child.bit = 0;
    BucketNotLeaf one_child(1, true);
    one_child.bit = 1;
    zero_child.zero = bucket_position;
    one_child.zero = number_of_leaf;

    current.write_to_file(this->bucketnotleaf_filename, current_pos);
    zero_child.write_to_file(this->bucketnotleaf_filename, number_of_notleaf);
    one_child.write_to_file(this->bucketnotleaf_filename,
                            number_of_notleaf + 1);
  }
}

template <typename T>
Record<T> ExtendibleHashing<T>::search(T key) {
  // Get hash code
  size_t hash_number = hash_function(key) % (1 << depth);
  std::string hash_code = std::bitset<depth>(hash_number).to_string();

  // Get size of not leaf bucket file
  size_t size_index_notleaf_file =
      get_size_of_file(this->bucketnotleaf_filename);
  if (size_index_notleaf_file == 0) {
    // Create new bucket leaf and not leaf
    throw std::runtime_error("File not found at " +
                            this->bucketnotleaf_filename + "in search");
  }

  // Update sizes
  size_index_notleaf_file = get_size_of_file(this->bucketnotleaf_filename);
  size_t size_index_leaf_file = get_size_of_file(this->bucketleaf_filename);

  // Temporal Bucket Not Leaf
  BucketNotLeaf current;
  current.read_from_file(this->bucketnotleaf_filename, 0);

  // Iterate through the buckets not leaf
  int i = 0;
  long current_pos = 0;
  while (!current.isLeaf && i < depth) {
    if (current.bit == hash_code[i]) {
      current_pos = current.one;
      current.read_from_file(this->bucketnotleaf_filename, current.one);
    } else {
      current_pos = current.zero;
      current.read_from_file(this->bucketnotleaf_filename, current.zero);
    }
    i++;
  }

  // When current is leaf, the position of the bucket record is zero
  size_t bucket_position = current.zero;

  BucketLeaf<T> bucket_leaf;
  bucket_leaf.read_from_file(this->bucketleaf_filename, bucket_position);

  if (bucket_leaf.next_ == 0) {
    throw std::runtime_error("Key not found at  " + this->bucketleaf_filename +
                             " in search" + " key: " + std::to_string(key));
  }
  do {
    if (bucket_leaf.elements_->find(key) != bucket_leaf.elements_->end()) {
      return Record<T>(key, bucket_leaf.elements_->at(key));
    }
    bucket_position = bucket_leaf.next_;
    bucket_leaf.read_from_file(this->bucketleaf_filename, bucket_position);
  } while (bucket_leaf.next_ != 0);

}
/* Auxiliar functions */

template <typename T>
size_t ExtendibleHashing<T>::get_size_of_file(std::string filename) {
  std::ifstream fin(filename, std::ios::in | std::ios::binary);
  if (!fin.is_open())
    throw std::runtime_error("[ERROR]: File not open" + filename);

  fin.seekg(0, std::ios::end);
  size_t size = fin.tellg();
  fin.close();
  return size;
}

template <typename T>
void ExtendibleHashing<T>::initialize_bucket_files() {
  BucketNotLeaf root;
  root.zero = 1;
  root.one = 2;

  BucketNotLeaf child0(0, 1);
  child0.isLeaf = true;
  child0.bit = 0;
  BucketNotLeaf child1(1, 1);
  child1.bit = 1;

  child0.zero = 0;
  child1.zero = 1;

  root.write_to_file(this->bucketnotleaf_filename, 0);
  child0.write_to_file(this->bucketnotleaf_filename, 1);
  child1.write_to_file(this->bucketnotleaf_filename, 2);

  BucketLeaf<T> bucketRecord0;
  bucketRecord0.write_to_file(this->bucketleaf_filename, 0);
  BucketLeaf<T> bucketRecord1;
  bucketRecord1.write_to_file(this->bucketleaf_filename, 1);
}

template <typename T>
void ExtendibleHashing<T>::readAllLeafsBuckets() {
  std::cout << "Leafs\n\n";
  size_t size_index_leaf_file = get_size_of_file(this->bucketleaf_filename);
  BucketLeaf<T> br0;
  size_t number_of_leafs = size_index_leaf_file / br0.get_sizeof();
  
  for (size_t i = 0; i < number_of_leafs; i++) {
    BucketLeaf<T> br;
    br.read_from_file(this->bucketleaf_filename, i);
    std::cout << "Bucket " << i << ": ";
    br.show();
  }
}

template <typename T>
void ExtendibleHashing<T>::readAllNotLeafsBuckets() {
  std::cout << "\nNot leafs\n\n";
  size_t size_index_notleaf_file =
      get_size_of_file(this->bucketnotleaf_filename);
      BucketNotLeaf br;
  size_t number_of_notleafs = size_index_notleaf_file / br.get_sizeof();
  
  for (size_t i = 0; i < number_of_notleafs; i++) {
    br.read_from_file(this->bucketnotleaf_filename, i);
    br.show();
  }
}
#endif