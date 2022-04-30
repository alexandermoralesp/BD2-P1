#ifndef MENUFIFA_H
#define MENUFIFA_H
#include <iostream>
#include "./ExtendibleHashing/ExtendibleHashing.h"
#include "./ExtendibleHashing/CSVReader.h"

bool insert(std::string line, long pos) {
    Registros::CartaFifa fifa;
    fifa.readCSVLine(line);
    ExtendibleHashing<size_t,3,3> eh("./ExtendibleHashing/fifa");
    std::hash<std::string> hash_fifa;
    size_t pre_hash = hash_fifa(fifa.id);
    return eh.insert(pre_hash, pos);
}

void read_all_indexes() {
    ExtendibleHashing<size_t,3,3> eh("./ExtendibleHashing/fifa");
    eh.readAllIndexes();
}

bool remove(std::string line) {
    std::hash<std::string> hash_fifa;
    ExtendibleHashing<size_t,3,3> eh("./ExtendibleHashing/fifa");
    size_t pre_hash = hash_fifa(line);
    return eh.remove(pre_hash);
}

std::string search(std::string line) {
    Registros::CartaFifa fifa;;
    ExtendibleHashing<size_t,3,3> eh("./ExtendibleHashing/fifa");
    std::hash<std::string> hash_fifa;
    size_t pre_hash = hash_fifa(line);
    Record<size_t> output = eh.search(pre_hash);
    std::ifstream fin("./ExtendibleHashing/fifa.dat", std::ios::binary);
    if (!fin.is_open()) std::cout << "No se pudo abrir fifa.dat";
    fin.seekg(output.pos, std::ios::beg);
    fin >> fifa;
    return fifa.writeCSVLine();
}

#endif