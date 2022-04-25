#ifndef EXTENDIBLEHASHING_H
#define EXTENDIBLEHASHING_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <exception>
struct Bucket;

template <typename KeyType>
struct Record;

template <typename KeyType>
struct Record {
    long position;
    KeyType key;
    Record(long pos, KeyType k) : position(pos), key(k) {}
    long get_position() const { return position; }
};

template <typename KeyType>
class ExtendibleHashing;

struct BucketInterface;

struct BucketInterface {

};

struct BucketIndex : public BucketInterface {
    bool isLeaf{};
    // Cuando el BucketIndex es una hoja, la posicion del BucketRecords es child0 por defecto. (Implementación
    // basda en un árbol binario de búsqueda
    long child0;
    long child1;
    int depth;
    int bit;
    BucketIndex(int bit, int depth) : bit(bit){
        child0 = -1;
        child1 = -1;
        this->depth = depth;
    };
};

template <typename KeyType>
struct BucketRecord : public BucketInterface {
    bool disable;
    int size;
    long next_bucket;
    std::map<KeyType, long> records;
    BucketRecord() : size(0), next_bucket(-1), disable(0)  {};
    void insert(KeyType key, long value);
    void remove(KeyType key);
    long find(KeyType key);
};

template <typename KeyType>
void BucketRecord<KeyType>::insert(KeyType key, long value) {
    if (records.find(key) == records.end()) {
        records.insert(std::make_pair(key, value));
        size++;
    }
}

template <typename KeyType>
class ExtendibleHashing {
private:
    std::string fileName;
    std::string indexFileName;
    std::string bucketFileName;
    int depth;
    int factor_block;
    std::hash<std::string> hash_fn;
public:
    ExtendibleHashing(std::string fileName, int depth, int factor_block);
    ~ExtendibleHashing();
    void insert(const KeyType& key, const Record<KeyType>& record);
    void remove(const KeyType& key);
    Record<KeyType>* find(const KeyType& key);
};

template <typename KeyType>
ExtendibleHashing<KeyType>::ExtendibleHashing(std::string fileName, int depth, int factor_block) {
    this->fileName = fileName;
    this->indexFileName = fileName + ".index.dat";
    this->bucketFileName = fileName + ".bucket.dat";
    this->depth = depth;
    this->factor_block = factor_block;
}

template <typename KeyType>
ExtendibleHashing<KeyType>::~ExtendibleHashing() {
    std::ofstream indexFile(indexFileName);
    indexFile.close();
}

template <typename KeyType>
void ExtendibleHashing<KeyType>::insert(const KeyType& key, const Record<KeyType>& record) {
    auto hash_code = hash_fn(key) % (1 << depth);
    std::ofstream indexFileWrite(indexFileName, std::ios::in | std::ios::out | std::ios::binary);

    if(!indexFileWrite.is_open()) throw std::runtime_error("Cannot open index file");
    size_t size_file = indexFileWrite.tellp();
    indexFileWrite.close();
    if (size_file == 0) {
        BucketIndex root(-1,0);
        root.child0 = 1;
        root.child1 = 2;
        BucketIndex child0(0,1);
        child0.isLeaf = true;
        BucketIndex child1(1,1);
        child1.isLeaf = true;

        child0.child0 = 0;
        child1.child0 = 1;
 
        indexFileWrite.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
        indexFileWrite.write((char*)&root, sizeof(BucketIndex));
        indexFileWrite.write((char*)&child0, sizeof(BucketIndex));
        indexFileWrite.write((char*)&child1, sizeof(BucketIndex));
        indexFileWrite.close();

        std::ofstream bucketFileRecord(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
        if (!bucketFileRecord.is_open()) throw std::runtime_error("Cannot open bucket file");
        BucketRecord<KeyType> bucketRecord0;
        BucketRecord<KeyType> bucketRecord1;
        bucketFileRecord.write((char*)&bucketRecord0, sizeof(BucketRecord<KeyType>));
        bucketFileRecord.write((char*)&bucketRecord1, sizeof(BucketRecord<KeyType>));
        bucketFileRecord.close();
    }

    std::ifstream indexFileRead(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
    BucketIndex current(-1);
    indexFileRead.read((char*)&current, sizeof(BucketIndex));
    indexFileRead.close();

    int i = 0;
    long current_position = 0;
    while (!current.isLeaf && i < depth) {
        if (hash_code & (1 << i)) {
            current_position = current.child1;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child1 * sizeof(BucketIndex));
            indexFileRead.read((char*)&current, sizeof(BucketIndex));
            indexFileRead.close();
        } else {
            current_position = current.child0;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child0 * sizeof(BucketIndex));
            indexFileRead.read((char*)&current, sizeof(BucketIndex));
            indexFileRead.close();
        }
        i++;
    }
    // When current is leaf, the position of the bucket record is child0
    size_t bucket_position = current.child0;

    std::ifstream bucketFileRead(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
    if(!bucketFileRead.is_open()) throw std::runtime_error("Cannot open bucket file");
    BucketRecord<KeyType> bucket;
    bucketFileRead.seekg(bucket_position * sizeof(BucketRecord<KeyType>));
    bucketFileRead.read((char*)&bucket, sizeof(BucketRecord<KeyType>));
    bucketFileRead.close();
    
    std::ofstream bucketFileWrite(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!bucketFileWrite.is_open()) throw std::runtime_error("Cannot open bucket file");

    if (bucket.size < factor_block) {
        bucket.insert(key, record.get_position());
        bucketFileWrite.seekp(bucket_position * sizeof(BucketRecord<KeyType>));
        bucketFileWrite.write((char*)&bucket, sizeof(BucketRecord<KeyType>));
        bucketFileWrite.close();
        return;
    } else {
        // split bucket
        BucketIndex new_child0(0, i+1);
        BucketIndex new_child1(1, i+1);
        
        BucketRecord<KeyType> new_bucket0;
        BucketRecord<KeyType> new_bucket1;
        
        new_child0.isLeaf = true;
        new_child1.isLeaf = true;
        
        for (std::pair<KeyType, long> &pair_bucket :  bucket.records)
        {
            if (pair_bucket.first[i] == '0') {
                new_bucket0.insert(pair_bucket.first, pair_bucket.second);
            } else {
                new_bucket1.insert(pair_bucket.first, pair_bucket.second);
            }
        }
        // Remove bucket from index
        long number_of_buckets;
        bucket.disable = true;
        bucket.size = 0;
        bucket.records.clear();
        bucket.next_bucket = -1;
        bucketFileWrite.seekp(bucket_position * sizeof(BucketRecord<KeyType>));
        bucketFileWrite.write((char*)&bucket, sizeof(BucketRecord<KeyType>));
        // Add new buckets to index
        bucketFileWrite.seekp(0, std::ios::end);
        number_of_buckets = (bucketFileWrite.tellp())/sizeof(BucketRecord<KeyType>);
        new_child0.child0 = number_of_buckets;
        new_child1.child1 = number_of_buckets+1;
        bucketFileWrite.write((char*)&new_bucket0, sizeof(BucketIndex));
        bucketFileWrite.write((char*)&new_bucket1, sizeof(BucketIndex));
        bucketFileWrite.close();

        // Update current bucket
        std::ofstream indexFileWrite(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
        if (!indexFileWrite.is_open()) throw std::runtime_error("Cannot open index file");
        indexFileWrite.seekp(0, std::ios::end);
        size_t number_of_indexes = indexFileWrite.tellp() / sizeof(BucketIndex);
        current.child0 = number_of_indexes;
        current.child1 = number_of_indexes+1;

        indexFileWrite.seekp(current_position * sizeof(BucketIndex));
        indexFileWrite.write((char*)&current, sizeof(BucketIndex));
        indexFileWrite.write((char*)&new_child0, sizeof(BucketIndex));
        indexFileWrite.write((char*)&new_child1, sizeof(BucketIndex));
        indexFileWrite.close();
    }
}

template <typename KeyType>
Record<KeyType>* ExtendibleHashing<KeyType>::find(const KeyType &key) {
    long hash_code = hash(key) % (1 << depth);
    std::ifstream indexFileRead(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!indexFileRead.is_open()) throw std::runtime_error("Cannot open index file");
    BucketIndex current(-1);
    indexFileRead.read((char*)&current, sizeof(BucketIndex));
    indexFileRead.close();

    int i = 0;
    long current_position = 0;
    while (!current.isLeaf && i < depth) {
        if (hash_code & (1 << i)) {
            current_position = current.child1;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child1 * sizeof(BucketIndex));
            indexFileRead.read((char*)&current, sizeof(BucketIndex));
            indexFileRead.close();
        } else {
            current_position = current.child0;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child0 * sizeof(BucketIndex));
            indexFileRead.read((char*)&current, sizeof(BucketIndex));
            indexFileRead.close();
        }
        i++;
    }

    // When current is leaf, the position of the bucket record is child0
    size_t bucket_position = current.child0;

    std::ifstream bucketFileRead(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
    if(!bucketFileRead.is_open()) throw std::runtime_error("Cannot open bucket file");
    BucketRecord<KeyType> bucket;
    bucketFileRead.seekg(bucket_position * sizeof(BucketRecord<KeyType>));
    bucketFileRead.read((char*)&bucket, sizeof(BucketRecord<KeyType>));
    bucketFileRead.close();
    
    if (bucket.size == 0) {
        return nullptr;
    } else {
        for (std::pair<KeyType, long> &pair_bucket :  bucket.records)
        {
            if (pair_bucket.first == key) {
                Record<KeyType> *record = new Record<KeyType>(pair_bucket.second);
                return record;
            }
        }
        return nullptr;
    }
}

template <typename KeyType>
void ExtendibleHashing<KeyType>::remove(const KeyType &key) {
    long hash_code = hash(key) % (1 << depth);
    std::ifstream indexFileRead(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!indexFileRead.is_open()) throw std::runtime_error("Cannot open index file");
    BucketIndex current(-1);
    indexFileRead.read((char*)&current, sizeof(BucketIndex));
    indexFileRead.close();

    int i = 0;
    long current_position = 0;
    while (!current.isLeaf && i < depth) {
        if (hash_code & (1 << i)) {
            current_position = current.child1;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child1 * sizeof(BucketIndex));
            indexFileRead.read((char*)&current, sizeof(BucketIndex));
            indexFileRead.close();
        } else {
            current_position = current.child0;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child0 * sizeof(BucketIndex));
            indexFileRead.read((char*)&current, sizeof(BucketIndex));
            indexFileRead.close();
        }
        i++;
    }

    // When current is leaf, the position of the bucket record is child0
    size_t bucket_position = current.child0;

    std::ifstream bucketFileRead(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
    if(!bucketFileRead.is_open()) throw std::runtime_error("Cannot open bucket file");
    BucketRecord<KeyType> bucket;
    bucketFileRead.seekg(bucket_position * sizeof(BucketRecord<KeyType>));
    bucketFileRead.read((char*)&bucket, sizeof(BucketRecord<KeyType>));
    bucketFileRead.close();
    if (bucket.size == 0) {
        return;
    } else {
        for (std::pair<KeyType, long> &pair_bucket :  bucket.records)
        {
            if (pair_bucket.first == key) {
                Record<KeyType> *record = new Record<KeyType>(pair_bucket.second);
                return record;
            }
        }
        return nullptr;
    }
}

#endif
