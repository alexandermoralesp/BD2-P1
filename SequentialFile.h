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
    template<typename Key_t>
    T search(Key_t key);
};

template<typename T>
template<typename Key_t>
T SequentialFile<T>::search(Key_t key){
    ifstream file(base_path+BinSuffix, ios::in|ios::binary);

    file.seekg(0,ios::end);
    int l = 0;
    int r = (file.tellg()-sizeof(T)-sizeof(int))/(sizeof(T)+sizeof(int));

    T result, objective(key);

    while(l<r){
        int m = (l+r)/2;
        file.seekg(m*(sizeof(T)+sizeof(int)), ios::beg);
        file>>result;
        if(objective>result)
            l = m;
        else if(objective<result)
            r = m;
        else 
            return result;
    }
    file.close();

    file.open(base_path+AuxSuffix, ios::in|ios::binary);

    while (file>>result)
    {
        if(result == objective) return result;
        file.ignore(sizeof(int));
    }

    file.close();
    return T();
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