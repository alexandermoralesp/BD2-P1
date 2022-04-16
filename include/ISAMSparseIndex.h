/**
 * @file ISAM.h
 * @author Alexander (@moralespanitz)
 * @brief ISAM-Sparse Index implementation for File Organization
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ISAM_SPARSE_INDEX_H
#define ISAM_SPARSE_INDEX_H

/* Dependencies */
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

/* Definiciones */
#define MAX_SIZE_ENTRIES 90000

struct Record {
    int key;
    std::string name;
    int age;
};

struct Index {
    int key;
    std::pair<long, long> limits;
};

struct Entry {
    long key_entry;
    long int page;
};

/**
 * @brief ISAM-SPARSE INDEX Class
 *
 */
class ISAM_SPARSE_INDEX {
   private:
    std::string file_name_;

   public:
    ISAM_SPARSE_INDEX(std::string file_name);
    ~ISAM_SPARSE_INDEX();
    std::vector<Record> search(int key);
    std::vector<Record> rangeSeach(int begin_key, int end_key);
    void add(Record record);
    void remove(int key);
};

ISAM_SPARSE_INDEX::ISAM_SPARSE_INDEX(std::string file_name) {
    file_name_ = file_name;
}

ISAM_SPARSE_INDEX::~ISAM_SPARSE_INDEX() {
    // Destructor
}

std::vector<Record> ISAM_SPARSE_INDEX::search(int key) {}

std::vector<Record> ISAM_SPARSE_INDEX::rangeSeach(int begin_key, int end_key) {}

void ISAM_SPARSE_INDEX::add(Record record) {
    long int number_of_indexes = MAX_SIZE_ENTRIES;
    int index_n = 0;
    do {
        file_name_ = file_name_ + std::to_string(index_n);
        std::ofstream fileWrite(file_name_, ios::binary | ios::out | ios::app);
        if (!fileWrite.is_open())
            throw std::invalid_argument(
                "[ERROR]: The file_name is not correct. Try to set a correct "
                "path");
        fileWrite.seekp(0, ios::end);
        number_of_indexes = fileWrite.tellp();
        if (number_of_indexes >= MAX_SIZE_ENTRIES) {
            fileWrite.close();
            index_n++;
            continue;
        } else {
            Entry entry;
            fileWrite.write((char*)&entry, sizeof(Entry));
            fileWrite.close();
            break;
        }
    } while (number_of_indexes >= MAX_SIZE_ENTRIES);
}

void ISAM_SPARSE_INDEX::remove(int key) {}

#endif  // ISAM_SPARSE_INDEX_H
