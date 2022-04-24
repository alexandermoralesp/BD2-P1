#ifndef BPLUS_H
#define BPLUS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Page.h"

using namespace std;

template <typename KeyType>
struct Record;

template <typename KeyType, int degree>
class BPlus;

template <typename KeyType>
struct Record {
    KeyType key;
};

template <typename KeyType, int degree>
class BPlus {
private:
    std::string index_filename;
    std::string data_filename;
    long root_page_id;
    int PAGE_SIZE = sizeof(bool) + sizeof(int) + sizeof(int)*(degree-1) + sizeof(long)*degree;
public:
    BPlus(const std::string& index_filename, const std::string& data_filename);
    ~BPlus();
    Record<KeyType> search(KeyType key);
    std::vector<Record<KeyType>> rangeSearch(KeyType begin_key, KeyType end_key);
    bool insert(KeyType key);
    bool remove(KeyType key);
private:
    void insertInternal();
    void updateHead(long pos);
};

template<typename KeyType, int degree>
inline Record<KeyType> BPlus<KeyType, degree>::search(KeyType key)
{
	std::ifstream reader_index_filename(index_filename, std::ios::binary);
	if (!reader_index_filename.is_open()) throw ("error while openning file");
	reader_index_filename.seekg(0, std::ios::end);
	long size_file = reader_index_filename.tellg();
	if (size_file <= 1) { throw ("No data exists"); }
	else {
		// Read root page
		long header_pos = -1;
		reader_index_filename.seekg(0, std::ios::beg);
		reader_index_filename.read((char*)&header_pos, sizeof(long));
		Page<KeyType, degree>* current = readPageFromFile(header_pos, index_filename);

		while (!current->isLeaf) {
			for (int i = 0; i < current->size; i++)
			{
				if (key < current->keys[i]) {
					auto temp = readPageFromFile(current->pages[i], index_filename);
					delete current;
					current = temp;
					break;
				}
				if (i == current->size - 1) {
					auto temp = readPageFromFile(current->pages[i + 1], index_filename);
					delete current;
					current = temp;
					break;
				}
			}
		}
		for (size_t i = 0; i < current->size; i++)
		{
			if (current->keys[i] == key) {
				return readDataRecordFromFile(current->pages[i], data_filename);
			}
		}
		throw("Record doesn't exist");
	}
}
