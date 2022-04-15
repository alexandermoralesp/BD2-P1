#ifndef SEQUENTIALFILE_H
#define SEQUENTIALFILE_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Registros.h"

using namespace std;

const string BinSuffix = ".dat";
const string AuxSuffix = "_aux" + BinSuffix;
const string CSVSuffix = ".csv";
const int K_max_aux = 5;

template <typename T>
class SequentialFile
{
private:
    string base_path;
    void CSV_Loader(string _base_path);

public:
    SequentialFile(string _base_path);
    void add(T reg);
};

template<typename T, typename Key_t>
T search(Key_t key){
    
    return ;
}

template <typename T>
void SequentialFile<T>::add(T reg)
{
    
}

template <typename T>
void SequentialFile<T>::CSV_Loader(string csv)
{
    ifstream csv_file(csv, ios::in);
    string temp;
    vector<T> registros;
    while (getline(csv_file, temp))
    {
        T registro;
        registro.readCSVLine(temp);
        registros.push_back(registro);
    }
    sort(registros.begin(), registros.end());

    csv_file.close();

    ofstream ogData(base_path + BinSuffix, ios::out | ios::binary | ios::app);
    int ptr = 2;
    for (T i : registros)
    {
        ogData<<i;
        ogData.write((char *) &(ptr), sizeof(int));
        ptr++;
    }

    ogData.close();
}

template <typename T>
SequentialFile<T>::SequentialFile(string _base_path)
    : base_path(_base_path)
{
    const string binaryDB = base_path + BinSuffix, auxDB = base_path + AuxSuffix;
    fstream fCreate(auxDB, ios::in|ios::out|ios::app);
    fCreate.close();
    fCreate.open(binaryDB, ios::in|ios::out|ios::app);
    fCreate.seekp(0, ios::end);
    if (fCreate.tellp() == 0)
    {
        fCreate.close();
        const string csvDB = base_path + CSVSuffix;
        CSV_Loader(csvDB);
    }
    fCreate.close();
}

#endif