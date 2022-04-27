#ifndef EXTENDIBLEHASHING_H
#define EXTENDIBLEHASHING_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <math.h>

#include "./Bucket.h"

size_t get_size_of_file(std::string filename);

void initialize_index_and_records_binary_files(std::string indexFileName, std::string bucketFileName);

template <typename KeyType>
struct Record
{
  KeyType key;
  int age;
};

size_t get_size_of_file(std::string filename)
{
  std::ifstream file(filename, std::ios::binary);
  if (!file.is_open())
    throw std::runtime_error("Cannot open index file");
  file.seekg(0, std::ios::end);
  size_t size_file = file.tellg();
  file.close();
  return size_file;
}

template <typename KeyType, int FactorBlock, int depth>
class ExtendibleHashing
{
private:
  std::string index_filename;
  std::string records_filename;
  std::hash<KeyType> hash_fn;

public:
  ExtendibleHashing(std::string filename)
  {
    this->index_filename = filename + ".index.dat";
    this->records_filename = filename + ".records.dat";

   std::ifstream file0(index_filename, std::ios::app);
    if (!file0.is_open())
      throw("eror");
    file0.close();

    std::ifstream file(records_filename, std::ios::app);
    if (!file.is_open())
      throw("eror");
    file.close();
  }
  bool insert(KeyType key, long pos);
  void readAllIndexes() {
    std::cout << "INDEXES:\n\n";
    size_t size_index_file = get_size_of_file(index_filename);
    BucketIndex bi;
    size_t numbers_of_indexes = std::ceil(size_index_file/bi.get_size());
    for (size_t i = 0; i < numbers_of_indexes; i++)
    {
      bi.readFromFile(i, index_filename);
      std::cout << "\nIndex " << i << ": \n";
      bi.show();
    }
  }

  void readAllBuckets() {
    std::cout << "BUCKETS\n\n";
    size_t size_buckets_file = get_size_of_file(records_filename);
    BucketRecord<KeyType, FactorBlock> br;
    size_t number_of_buckets = std::ceil(size_buckets_file / br.get_size());
    std::cout << "Number of buckets is: " << number_of_buckets << "\n";
    for (size_t i = 0; i < number_of_buckets; i++)
    {
      br.readFromFile(i, records_filename);
      std::cout << "Bucket " << i << ": \n";
      br.show();
    }
  }
private:
  std::string get_hash_code(const KeyType &key)
  {
    size_t hash_number = hash_fn(key) % (1 << depth);
    std::string hash_code = std::bitset<depth>(hash_number).to_string();
    return hash_code;
  }
  void initialize_index_and_records_binary_files(std::string indexFileName, std::string bucketFileName);
};

template <typename KeyType, int FactorBlock, int depth>
bool ExtendibleHashing<KeyType, FactorBlock, depth>::insert(KeyType key, long pos)
{
  // TODO: Resolver problema de string keytype para la escritura
  // Get hash code
  std::string hash_code = get_hash_code(key);
  // std::cout << "Hash code: " << hash_code << std::endl;

  // Get size of index file
  size_t size_index_file = get_size_of_file(index_filename);
  if (size_index_file == 0)
  {
    initialize_index_and_records_binary_files(index_filename, records_filename);
  }

  size_index_file = get_size_of_file(index_filename);
  size_t size_records_file = get_size_of_file(records_filename);
  std::cout << "Size index: " << size_index_file << "\n";
  // std::cout << "Size buckets: " << size_records_file << "\n";
  BucketIndex current;
  current.readFromFile(0, index_filename);
  int i = 0;
  long current_position = 0;
  while (!current.isLeaf && i < depth)
  {
    if (hash_code[i] == '1')
    {
      current_position = current.one;
      current.readFromFile(current_position, index_filename);
    }
    else
    {
      current_position = current.zero;
      current.readFromFile(current_position, index_filename);
    }
    i++;
  }

  // When current is leaf, the position of the bucket record is zero
  size_t bucket_position = current.zero;
  BucketRecord<KeyType, FactorBlock> bucket_record;
  bucket_record.readFromFile(bucket_position, records_filename);

  // Number of records
  size_t number_of_indexes = size_index_file / sizeof(BucketIndex);
  size_t number_of_buckets = size_records_file/ sizeof(bucket_record.get_size());

  if (bucket_record.size < FactorBlock)
  {
    bucket_record.insert(key, pos);
    bucket_record.writeToFile(bucket_position, records_filename);
  } else if (bucket_record.size == FactorBlock && i == depth)
  {
    // Add new bucket to bucket record
    bucket_record.next = number_of_buckets;
    bucket_record.writeToFile(bucket_position, records_filename);

    BucketRecord<KeyType, FactorBlock> new_bucket_record;
    new_bucket_record.insert(key, pos);
    new_bucket_record.writeToFile(number_of_buckets + 1, records_filename);
  } else {
    BucketIndex new_zero;
    BucketIndex new_one;

    new_zero.isLeaf = true;
    new_one.isLeaf = true;

    BucketRecord<KeyType, FactorBlock> new_zero_record;
    BucketRecord<KeyType, FactorBlock> new_one_record;

    for (int i = 0; i < bucket_record.size; i++)
    {
      std::string hash_code_key = get_hash_code(bucket_record.keys[i]);
      if (hash_code_key[i] == '1')
      {
        new_one_record.insert(bucket_record.keys[i], bucket_record.positions[i]);
      }
      else
      {
        new_zero_record.insert(bucket_record.keys[i], bucket_record.positions[i]);
      }
    }
    // TODO: Remove flag for bucket record
    // Add new buckets to records file
    new_zero_record.writeToFile(number_of_buckets + 1, records_filename);
    new_one_record.writeToFile(number_of_buckets + 2, records_filename);

    // Updated current index
    current.zero = number_of_indexes;
    current.one = number_of_indexes + 1;

    BucketIndex zero_child(0, true);
    BucketIndex one_child(1, true);
    zero_child.zero = number_of_buckets;
    zero_child.one = number_of_buckets + 1;

    current.writeToFile(current_position, index_filename);
    zero_child.writeToFile(number_of_indexes + 1, index_filename);
    one_child.writeToFile(number_of_indexes + 2, index_filename);
  }
  return true;
}

template <typename KeyType, int FactorBlock, int depth>
void ExtendibleHashing<KeyType, FactorBlock, depth>::initialize_index_and_records_binary_files(std::string indexFileName, std::string bucketFileName)
{
  BucketIndex root;
  root.zero = 1;
  root.one = 2;

  BucketIndex child0(0, 1);
  child0.isLeaf = true;
  BucketIndex child1(1, 1);
  child1.isLeaf = true;
  
  child0.zero = 1;
  child1.zero = 2;

  root.writeToFile(0, index_filename);
  child0.writeToFile(1, index_filename);
  child1.writeToFile(2, index_filename);

  BucketRecord<KeyType, FactorBlock> bucketRecord0;
  bucketRecord0.writeToFile(0, bucketFileName);
  BucketRecord<KeyType, FactorBlock> bucketRecord1;
  bucketRecord1.writeToFile(1, bucketFileName);
}
#endif
