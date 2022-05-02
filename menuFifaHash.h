#ifndef MENUFIFA_H
#define MENUFIFA_H
#include <iostream>
#include "./ExtendibleHashing/ExtendibleHashing.h"
#include "./ExtendibleHashing/CSVReader.h"

bool insert(std::string line, long pos) {
    Registros::CartaFifa fifa;
    fifa.readCSVLine(line);
    ExtendibleHashing<std::string, 3, 3> eh("./ExtendibleHashing/fifa"); 
    return eh.insert(fifa.id, pos);
}

void read_all_indexes() {
    ExtendibleHashing<std::string, 3, 3> eh("./ExtendibleHashing/fifa"); 
    eh.readAllIndexes();
}

bool remove(std::string line) {
    ExtendibleHashing<std::string, 3, 3> eh("./ExtendibleHashing/fifa"); 
    return eh.remove(line);
}

std::string search(std::string line) {
    Registros::CartaFifa fifa;;
    ExtendibleHashing<std::string, 3, 3> eh("./ExtendibleHashing/fifa"); 
    Record<std::string> output = eh.search(line);
    std::ifstream fin("./ExtendibleHashing/fifa.dat", std::ios::binary);
    if (!fin.is_open()) std::cout << "No se pudo abrir fifa.dat";
    fin.seekg(output.pos, std::ios::beg);
    fin >> fifa;
    return fifa.writeCSVLine();
}

#endif
