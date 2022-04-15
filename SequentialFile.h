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

struct NextLabel
{
    int nextRow;
    char nextRowFile;
};

bool operator==(NextLabel a, NextLabel b)
{
    return a.nextRow == b.nextRow && a.nextRowFile == b.nextRowFile;
}

ostream &operator<<(ostream &os, NextLabel n)
{
    os.write((char *)&n, sizeof(NextLabel));
    return os;
}

istream &operator>>(istream &is, NextLabel &n)
{
    is.read((char *)&n, sizeof(NextLabel));
    return is;
}

template <typename T>
class SequentialFile
{
private:
    int row_sizeof;
    string base_path;
    void CSV_Loader(string _base_path);

public:
    SequentialFile(string _base_path);
    void add(T reg);
    template <typename Key_t>
    vector<T> rangeSearch(Key_t begin_key, Key_t end_key);
    template <typename Key_t>
    void remove(Key_t key);
    template <typename Key_t>
    T search(Key_t key);
};

template <typename T>
template <typename Key_t>
vector<T> SequentialFile<T>::rangeSearch(Key_t begin_key, Key_t end_key)
{
    T key_group[2] = {T(begin_key), T(end_key)};

    if (key_group[0] > key_group[1])
        throw("La llave de inicio es mayor a la final");
    else if (key_group[0] == key_group[1])
        return vector<T>{search<Key_t>(begin_key)};

    T row_group[2];
    NextLabel label_group[2];

    ifstream fileData(base_path + BinSuffix, ios::in | ios::binary);
    ifstream fileAux(base_path + AuxSuffix, ios::in | ios::binary);
    for (int i = 0; i < 2; i++)
    {
        int l = 0;
        fileData.seekg(0, ios::end);
        int r = (fileData.tellg() - row_sizeof - sizeof(NextLabel)) / row_sizeof;
        while (l <= r)
        {
            int m = (l + r) / 2;
            fileData.seekg(sizeof(NextLabel) + m * row_sizeof, ios::beg);
            fileData >> row_group[i];
            if (key_group[i] > row_group[i])
                l = m + 1;
            else if (key_group[i] < row_group[i])
                r = m - 1;
            else
            {
                fileData >> label_group[i];
                break;
            }
        }
        if (key_group[i] != row_group[i])
        {
            fileAux.seekg(0, ios::beg);

            while (fileAux >> row_group[i])
            {
                if (row_group[i] == key_group[i])
                {
                    fileAux >> label_group[i];
                }
            }

            if (row_group[i] != key_group[i])
                i ? throw("Llave de cierre no encontrada") : throw("Llave de inicio no encontrada");
        }
    }

    vector<T> result{row_group[0]};

    while (!(label_group[0] == label_group[1]))
    {
        if (label_group[0].nextRowFile == 'd')
        {
            fileData.seekg((label_group[0].nextRow - 1) * row_sizeof + sizeof(NextLabel), ios::beg);
            fileData >> row_group[0] >> label_group[0];
        }
        else
        {
            fileAux.seekg((label_group[0].nextRow - 1) * row_sizeof, ios::beg);
            fileAux >> row_group[0] >> label_group[0];
        }
        result.push_back(row_group[0]);
    }

    fileAux.close();
    fileData.close();

    return result;
}

template <typename T>
template <typename Key_t>
T SequentialFile<T>::search(Key_t key)
{
    ifstream file(base_path + BinSuffix, ios::in | ios::binary);

    file.seekg(0, ios::end);
    int l = 0;
    int r = (file.tellg() - row_sizeof - sizeof(NextLabel)) / row_sizeof;

    T result, objective(key);

    while (l <= r)
    {
        int m = (l + r) / 2;
        file.seekg(sizeof(NextLabel) + m * row_sizeof, ios::beg);
        file >> result;
        if (objective > result)
            l = m + 1;
        else if (objective < result)
            r = m - 1;
        else
        {
            file.close();
            return result;
        }
    }
    file.close();

    file.open(base_path + AuxSuffix, ios::in | ios::binary);

    while (file >> result)
    {
        if (result == objective)
            return result;
        file.ignore(sizeof(NextLabel));
    }

    file.close();
    throw("No encontrado");
    return T();
}

template <typename T>
void SequentialFile<T>::add(T reg)
{
    ifstream fileData(base_path + BinSuffix, ios::in | ios::binary);
    ifstream fileAux(base_path + AuxSuffix, ios::in | ios::binary);

    

    fileData.close();
    fileAux.close();
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
    NextLabel siguiente;
    for (siguiente = {1, 'd'}; siguiente.nextRow - 1 < registros.size(); siguiente.nextRow++)
    {
        ogData << siguiente;
        ogData << registros[siguiente.nextRow - 1];
    }
    siguiente.nextRow = -1;
    ogData << siguiente;

    ogData.close();
}

template <typename T>
SequentialFile<T>::SequentialFile(string _base_path)
    : base_path(_base_path), row_sizeof(sizeof(T) + sizeof(NextLabel))
{
    const string binaryDB = base_path + BinSuffix, auxDB = base_path + AuxSuffix;
    fstream fCreate(auxDB, ios::in | ios::out | ios::app);
    fCreate.close();
    fCreate.open(binaryDB, ios::in | ios::out | ios::app);
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