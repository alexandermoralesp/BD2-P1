#ifndef PAGE_H
#define PAGE_H

/* Include dependencies */
#include <fstream>
#include <iostream>
#include <string>
/* Include external headers */

/* Declarations */

/**
 * @brief Index Page
 *
 * @tparam KeyType - type of key
 * @tparam degree - number of childreen of Page
 */

template <typename KeyType, int degree>
struct Page;

template <typename KeyType, int degree>
struct Page {
    /* Attributes */
    bool isLeaf{};
    int size{};
    KeyType* keys;
    long* pages{};

    /* Methods */
    explicit Page(bool isLeaf);
    ~Page();
    bool isEmpty();
    bool isFull();
    bool insertKey(KeyType key);
    std::string showPage();
};

template <typename KeyType, int degree>
Page<KeyType, degree>::Page(bool isLeaf) {
    this->isLeaf = isLeaf;
    this->size = 0;

    this->keys = new KeyType[degree - 1];
    this->pages = new long[degree];
}

template <typename KeyType, int degree>
Page<KeyType, degree>::~Page() {
    delete[] keys;
    delete[] pages;
}

template <typename KeyType, int degree>
bool Page<KeyType, degree>::isEmpty() {
    return (size == 0);
}

template <typename KeyType, int degree>
bool Page<KeyType, degree>::isFull() {
    return (size == degree - 1);
}

template <typename KeyType, int degree>
bool Page<KeyType, degree>::insertKey(KeyType key) {
    if (size == degree - 1) return false;
    int i = size - 1;
    while (i >= 0 && key < keys[i]) {
        keys[i + 1] = keys[i];
        i--;
    }
    keys[i + 1] = key;
    size++;
    return true;
}

template <typename KeyType, int degree>
std::string Page<KeyType, degree>::showPage() {
    std::string result;
    result += "Page\n";
    result += "isLeaf:\t" + std::to_string(isLeaf) + "\n";
    result += "size:\t" + std::to_string(size) + "\n";
    result += "keys:\t";
    for (int i = 0; i < size; i++) {
        result += std::to_string(keys[i]) + " ";
    }
    result += "\n";
    result += "pages:\t";
    for (size_t i = 0; i <= size; i++) {
        result += std::to_string(pages[i]) + " ";
    }
    result += "\n";
    result += "isEmpty: " + std::to_string(isEmpty()) + "\n";
    result += "isFull:\t" + std::to_string(isFull()) + "\n";
    return result;
}

/* Auxiliar Functions */
template <typename KeyType, int degree>
Page<KeyType, degree>* readPageFromFile(long pos, const std::string& index_filename, int PAGE_SIZE) {
    std::ifstream index_file(index_filename, std::ios::binary);
    if (!index_file.is_open()) throw("Error opening file");

    auto* page = new Page<KeyType, degree>(false);
    index_file.seekg(pos * PAGE_SIZE + sizeof(long), std::ios::beg);
    bool isLeaf;
    index_file.read((char*)&isLeaf, sizeof(bool));
    int size;
    index_file.read((char*)&size, sizeof(int));

    auto* keys = new KeyType[degree - 1];
    index_file.read((char*)keys, sizeof(KeyType) * (degree - 1));
    long* pages = new long[degree];
    index_file.read((char*)pages, sizeof(long) * (degree));

    page->isLeaf = isLeaf;
    page->size = size;
    page->keys = keys;
    page->pages = pages;
    index_file.close();
    return page;
}

template <typename KeyType, int degree>
bool setPageToFile(long pos, const std::string& index_filename,
                   Page<KeyType, degree>& page, int PAGE_SIZE) {
    std::ofstream index_file(index_filename, std::ios::binary);
    if (!index_file.is_open()) return false;
    index_file.seekp(pos * PAGE_SIZE + sizeof(long ), std::ios::beg);
    index_file.write((char*)&page.isLeaf, sizeof(bool));
    index_file.write((char*)&page.size, sizeof(int));
    index_file.write((char*)page.keys, sizeof(KeyType) * (degree - 1));
    index_file.write((char*)&*(page.pages), sizeof(long) * (degree));
    index_file.close();
    return true;
}

#endif  // PAGE_H
