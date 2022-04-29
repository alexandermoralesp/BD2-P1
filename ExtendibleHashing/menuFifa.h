#ifndef MENUFIFA_H
#define MENUFIFA_H

#include "CSVReader.h"
#include "FifaGenerator.h"
#include "ExtendibleHashing.h"

#include <iostream>
bool isBuilded = 1;

bool buildFifa() {
    generate_fifa_dat();
    isBuilded = 1;
}
std::hash<std::string> hash_fn_str;

bool insert(std::string record); // Like line in csv
std::string search(std::string id); // Like id in csv
bool remove(std::string id);

bool insert(std::string record, long pos) {
    if (!isBuilded) buildFifa();
    Registros::CartaFifa fifa;
    fifa.readCSVLine(record);
    ExtendibleHashing<size_t, 3, 3> eh("fifa");
    size_t value = hash_fn_str(fifa.id);    
    return eh.insert(value, pos);
} // Like line in csv
std::string search(std::string id) {
    if (!isBuilded) buildFifa();
    ExtendibleHashing<size_t, 3, 3> eh("fifa");
    size_t key = hash_fn_str(id);
    Record <size_t> record = eh.search(key);
    return readAt(record.pos);
} // Like id in csv

bool remove(std::string id) {
    if (!isBuilded) throw(runtime_error("Fifa not builded"));
    ExtendibleHashing<int, 3, 3> eh("fifa");
    size_t key = hash_fn_str(id);
    return eh.remove(key);
}

#endif