#ifndef EXTENDIBLEHASHING_H
#define EXTENDIBLEHASHING_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <string>
#include <exception>
#include <vector>

template<typename KeyType>
struct Record;

template<typename KeyType>
struct Record {
    long position;
    KeyType key;
    Record(long pos, KeyType k) : position(pos), key(k) {}
};

template<typename KeyType, int fb>
class ExtendibleHashing;

struct BucketIndex {
    bool isLeaf{};
    // child0 when BucketIndex is leaf correspond the position of the key in the bucket
    long child0;
    long child1;
    int depth;
    int bit;

    BucketIndex(int bit, int depth) : bit(bit) {
        child0 = -1;
        child1 = -1;
        this->depth = depth;
    };
    // show BucketIndex
    void show() {
        std::cout << "isLeaf: " << isLeaf << " child0: " << child0 << " child1: " << child1 << " depth: " << depth << " bit: " << bit << std::endl;
    }
};


template<typename KeyType, int fb>
struct BucketRecord {
    bool disable;
    int size;
    long next_bucket;
    KeyType records[fb];
    long positions[fb];

    BucketRecord() : size(0), next_bucket(-1), disable(0) {};
    ~BucketRecord() {
    }
    void insert(KeyType key, long value);

    void remove(KeyType key);

    long find(KeyType key);
    int get_size() {
        return sizeof(disable) + sizeof(size) + sizeof(next_bucket) + sizeof(KeyType)*fb + sizeof(long)*fb;
    }
    void show() {
        std::cout << "disable: " << disable << " size: " << size << " next_bucket: " << next_bucket << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "key: " << records[i] << " position: " << positions[i] << std::endl;
        }
    }
};

template<typename KeyType, int fb>
void BucketRecord<KeyType, fb>::insert(KeyType key, long value) {
    if (find(key) == -1) {
        records[size] = key;
        positions[size] = value;
        size++;
    }
}

template<typename KeyType, int fb>
long BucketRecord<KeyType, fb>::find(KeyType key) {
    for (int i = 0; i < size; ++i) {
        if (records[i] == key) return positions[i];
    }
    return -1;
}

template<typename KeyType, int fb>
class ExtendibleHashing {
private:
    std::string fileName;
    std::string indexFileName;
    std::string bucketFileName;
    int depth{};
    std::hash<std::string> hash_fn;
public:
    ExtendibleHashing(std::string fileName, int depth);

    ~ExtendibleHashing();

    void insert(const KeyType &key, const Record<KeyType> &record);

    void remove(const KeyType &key);

    Record<KeyType> *find(const KeyType &key);
    
};

template<typename KeyType, int fb>
ExtendibleHashing<KeyType, fb>::ExtendibleHashing(std::string fileName, int depth) {
    this->fileName = fileName;
    this->indexFileName = fileName + ".index.dat";
    this->bucketFileName = fileName + ".bucket.dat";
    this->depth = depth;
}

template<typename KeyType, int fb>
ExtendibleHashing<KeyType, fb>::~ExtendibleHashing() {
}

template<typename KeyType, int fb>
void ExtendibleHashing<KeyType, fb>::insert(const KeyType &key, const Record<KeyType> &record) {
    auto hash_code = hash_fn(key) % (1 << depth);
    std::ofstream indexFileWrite(indexFileName, std::ios::in | std::ios::out | std::ios::binary);

    if (!indexFileWrite.is_open()) throw std::runtime_error("Cannot open index file");
    indexFileWrite.seekp(0, std::ios::end);
    size_t size_file = indexFileWrite.tellp();
    indexFileWrite.close();
    if (size_file == 0) {
        BucketIndex root(-1, 0);
        root.child0 = 1;
        root.child1 = 2;
        BucketIndex child0(0, 1);
        child0.isLeaf = true;
        BucketIndex child1(1, 1);
        child1.isLeaf = true;

        child0.child0 = 1;
        child1.child0 = 2;

        indexFileWrite.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
        indexFileWrite.write((char *) &root, sizeof(BucketIndex));
        indexFileWrite.write((char *) &child0, sizeof(BucketIndex));
        indexFileWrite.write((char *) &child1, sizeof(BucketIndex));
        indexFileWrite.close();

        std::ofstream bucketFileRecord(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
        if (!bucketFileRecord.is_open()) throw std::runtime_error("Cannot open bucket file1");
        BucketRecord<KeyType, fb> bucketRecord0;
        BucketRecord<KeyType, fb> bucketRecord1;
        bucketFileRecord.write((char *) &bucketRecord0, sizeof(bucketRecord0.get_size()));
        bucketFileRecord.write((char *) &bucketRecord1, sizeof(bucketRecord1.get_size()));
        bucketFileRecord.close();
    }

    std::ifstream indexFileRead(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
    BucketIndex current(-1, depth);
    indexFileRead.read((char *) &current, sizeof(BucketIndex));
    indexFileRead.close();

    int i = 0;
    long current_position = 0;
    while (!current.isLeaf && i < depth) {
        if (hash_code & (1 << i)) {
            current_position = current.child1;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child1 * sizeof(BucketIndex), std::ios::beg);
            indexFileRead.read((char *) &current, sizeof(BucketIndex));
            indexFileRead.close();
        } else {
            current_position = current.child0;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child0 * sizeof(BucketIndex), std::ios::beg);
            indexFileRead.read((char *) &current, sizeof(BucketIndex));
            indexFileRead.close();
        }
        i++;
    }
    // When current is leaf, the position of the bucket record is child0
    size_t bucket_position = current.child0;

    std::ifstream bucketFileRead(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!bucketFileRead.is_open()) throw std::runtime_error("Cannot open bucket file");
    BucketRecord<KeyType, fb> bucket;
    bucketFileRead.seekg(bucket_position * sizeof(bucket.get_size()), std::ios::beg);
    bucketFileRead.read((char *) &bucket, sizeof(bucket.get_size()));
    bucketFileRead.close();

    std::ofstream bucketFileWrite(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!bucketFileWrite.is_open()) throw std::runtime_error("Cannot open bucket file");

    if (bucket.size < fb) {
        bucket.insert(key, record.position);
        bucketFileWrite.seekp(bucket_position * sizeof(bucket.get_size()), std::ios::beg);
        bucketFileWrite.write((char *) &bucket, sizeof(bucket.get_size()));
        bucketFileWrite.close();
        return;
    } else {
        // split bucket
        BucketIndex new_child0(0, i + 1);
        BucketIndex new_child1(1, i + 1);

        BucketRecord<KeyType, fb> new_bucket0;
        BucketRecord<KeyType, fb> new_bucket1;

        new_child0.isLeaf = true;
        new_child1.isLeaf = true;

        for (auto &pair_bucket: bucket.records) {
            if (pair_bucket[i] == '0') {
                new_bucket0.insert(&pair_bucket[i], bucket.positions[i]);
            } else {
                new_bucket1.insert(&pair_bucket[i], bucket.positions[i]);
            }
        }
        // Remove bucket from index
        long number_of_buckets;
        bucket.disable = true;
        bucket.size = 0;
        bucket.next_bucket = -1;
        bucketFileWrite.seekp(bucket_position * sizeof(bucket.get_size()), std::ios::beg);
        bucketFileWrite.write((char *) &bucket, sizeof(bucket.get_size()));
        // Add new buckets to index
        bucketFileWrite.seekp(0, std::ios::end);
        number_of_buckets = (bucketFileWrite.tellp()) / sizeof(bucket.get_size());
        new_child0.child0 = number_of_buckets;
        new_child1.child1 = number_of_buckets + 1;
        bucketFileWrite.write((char *) &new_bucket0, sizeof(BucketIndex));
        bucketFileWrite.write((char *) &new_bucket1, sizeof(BucketIndex));
        bucketFileWrite.close();

        // Update current bucket
        std::ofstream indexFileWrite(indexFileName, std::ios::out | std::ios::in | std::ios::binary);
        if (!indexFileWrite.is_open()) throw std::runtime_error("Cannot open index file");
        indexFileWrite.seekp(0, std::ios::end);
        size_t number_of_indexes = indexFileWrite.tellp() / sizeof(BucketIndex);
        current.child0 = number_of_indexes;
        current.child1 = number_of_indexes + 1;

        indexFileWrite.seekp(current_position * sizeof(BucketIndex), std::ios::beg);
        indexFileWrite.write((char *) &current, sizeof(BucketIndex));
        indexFileWrite.write((char *) &new_child0, sizeof(BucketIndex));
        indexFileWrite.write((char *) &new_child1, sizeof(BucketIndex));
        indexFileWrite.close();
    }
}

template<typename KeyType, int fb>
Record<KeyType> *ExtendibleHashing<KeyType, fb>::find(const KeyType &key) {
    long hash_code = hash_fn(key) % (1 << depth);
    std::ifstream indexFileRead(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!indexFileRead.is_open()) throw std::runtime_error("Cannot open index file");
    BucketIndex current(-1, depth);
    indexFileRead.read((char *) &current, sizeof(BucketIndex));
    indexFileRead.close();

    int i = 0;
    long current_position = 0;
    while (!current.isLeaf && i < depth) {
        if (hash_code & (1 << i)) {
            current_position = current.child1;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child1 * sizeof(BucketIndex), std::ios::beg);
            indexFileRead.read((char *) &current, sizeof(BucketIndex));
            indexFileRead.close();
        } else {
            current_position = current.child0;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child0 * sizeof(BucketIndex), std::ios::beg);
            indexFileRead.read((char *) &current, sizeof(BucketIndex));
            indexFileRead.close();
        }
        i++;
    }

    // When current is leaf, the position of the bucket record is child0
    size_t bucket_position = current.child0;

    std::ifstream bucketFileRead(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!bucketFileRead.is_open()) throw std::runtime_error("Cannot open bucket file");
    BucketRecord<KeyType, fb> bucket;
    bucketFileRead.seekg(bucket_position * sizeof(bucket.get_size()), std::ios::beg);
    bucketFileRead.read((char *) &bucket, sizeof(bucket.get_size()));
    bucketFileRead.close();

    if (bucket.size == 0) {
        return nullptr;
    } else {
        for (auto &pair_bucket: bucket.records) {
            if (pair_bucket.first == key) {
                Record<KeyType> *record = new Record<KeyType>(pair_bucket.second, pair_bucket.first);
                return record;
            }
        }
        return nullptr;
    }
}

template<typename KeyType, int fb>
void ExtendibleHashing<KeyType, fb>::remove(const KeyType &key) {
    long hash_code = hash(key) % (1 << depth);
    std::ifstream indexFileRead(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!indexFileRead.is_open()) throw std::runtime_error("Cannot open index file");
    BucketIndex current(-1, depth);
    indexFileRead.read((char *) &current, sizeof(BucketIndex));
    indexFileRead.close();

    int i = 0;
    long current_position = 0;
    while (!current.isLeaf && i < depth) {
        if (hash_code & (1 << i)) {
            current_position = current.child1;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child1 * sizeof(BucketIndex), std::ios::beg);
            indexFileRead.read((char *) &current, sizeof(BucketIndex));
            indexFileRead.close();
        } else {
            current_position = current.child0;
            indexFileRead.open(indexFileName, std::ios::in | std::ios::out | std::ios::binary);
            indexFileRead.seekg(current.child0 * sizeof(BucketIndex), std::ios::beg);
            indexFileRead.read((char *) &current, sizeof(BucketIndex));
            indexFileRead.close();
        }
        i++;
    }

    // When current is leaf, the position of the bucket record is child0
    size_t bucket_position = current.child0;

    std::ifstream bucketFileRead(bucketFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!bucketFileRead.is_open()) throw std::runtime_error("Cannot open bucket file");
    BucketRecord<KeyType, fb> bucket;
    bucketFileRead.seekg(bucket_position * sizeof(bucket.get_size()), std::ios::beg);
    bucketFileRead.read((char *) &bucket, sizeof(bucket.get_size()));
    bucketFileRead.close();
    if (bucket.size == 0) {
        return;
    } else {
        for (std::pair<KeyType, long> &pair_bucket: bucket.records) {
            if (pair_bucket.first == key) {
                pair_bucket.first = -1;
                return;
            }
        }
        return;
    }
}

#endif