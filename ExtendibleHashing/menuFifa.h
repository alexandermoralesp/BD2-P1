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

bool insert(std::string record, lons pos); // Like line in csv
std::string search(std::string id); // Like id in csv
bool remove(std::string id);

bool insert(std::string record, long pos) {
    if (!isBuilded) buildFifa();
    Registros::CartaFifa fifa;
    fifa.readCSVLine(record);
    ExtendibleHashing<std::string, 3, 3> eh("fifa");    
    return eh.insert(fifa.id, pos);
} // Like line in csv
std::string search(std::string id) {
    if (!isBuilded) buildFifa();
    ExtendibleHashing<std::string, 3, 3> eh("fifa"); 
    Record <size_t> record = eh.search(id);
    return readAt(record.pos);
} // Like id in csv

bool remove(std::string id) {
    if (!isBuilded) throw(runtime_error("Fifa not builded"));
    ExtendibleHashing<std::string, 3, 3> eh("fifa"); 
    return eh.remove(id);
}

#endif
