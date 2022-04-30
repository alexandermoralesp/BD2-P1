#ifndef TEST_H
#define TEST_H
#include "./CSVReader.h"
#include "./ExtendibleHashing.h"
#include <iostream>
using namespace std;
bool insert_internal(std::string line, long pos) {
    ExtendibleHashing<size_t,3,3> eh("./ExtendibleHashing/fifa");
    std::hash<std::string> hash_fifa;
    size_t pre_hash = hash_fifa(line);
    return eh.insert(pre_hash, pos);
}

void read_line() {
    Registros::CartaFifa fifa;
    fifa.readCSVLine("Pele,R,CAM,H,M,98,95,96,93,96,60,76,5,-1,-1,-1,-1,-1,-1");
    fifa.show();
}
void generate_index_dat() {
    Registros::CartaFifa fifa;
    ifstream fout("./ExtendibleHashing/fifa.dat", std::ios::in | std::ios::out | std::ios::binary);
    int i = 0;
    while (!fout.eof()) {
        long pos = fout.tellg();
        fout >> fifa;
        //fifa.show();
        cout << fifa.id << " pos:" << pos << endl;
        insert_internal(fifa.id, pos);
        i++;
    }
    fout.close();
}

void generate_fifa_dat() {
    Registros::CartaFifa fifa;
    ofstream fout("./ExtendibleHashing/fifa.dat", std::ios::in | std::ios::out | std::ios::binary);
    ifstream fin("./ExtendibleHashing/fifa.csv");
    if (!fin.is_open()) cout << "fifa.csv is not open";
    std::string line;
    getline(fin, line);
    while (getline(fin, line)) {
        fifa.readCSVLine(line);
        //cout << line << endl;
        // fifa.show();
        fout << fifa;
    }
    cout << "done";
}
void read_from_fifa_dat() {
    Registros::CartaFifa fifa;
    ifstream fout("./ExtendibleHashing/fifa.dat", std::ios::in | std::ios::out | std::ios::binary);
    int i = 0;
    while (!fout.eof() && i < 10) {
        fout >> fifa;
        fifa.show();
        i++;
    }
    fout.close();
}
#endif 