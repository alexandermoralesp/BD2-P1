#ifndef TITANICGENERATOR_H
#define TITANICGENERATOR_H

#include "CSVReader.h"
using namespace std;
template <typename T>

struct Record {
    T id;
    long pos;
    size_t get_size() {
        return sizeof(id) + sizeof(pos);
    }
};

void generate_titanic_dat() {
    ifstream fin("titanic.csv");
    if (!fin.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }
    Registros::Titanic titanic(0);
    std::string line;
    int i = 0;
    Record<int> record;
    ofstream fout("titanic.dat", ios::binary | ios::out | ios::in | ios::app);
    if (!fout.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }
    while (getline(fin, line)) {
        long pos = fin.tellg();
        titanic.readCSVLine(line);
        record.id = titanic.passenger_id;
        record.pos = pos;
        fout.write((char*)&record, record.get_size());
        i++;
    }
    fin.close();
}

#endif // TITANICGENERATOR_H
