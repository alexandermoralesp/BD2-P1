#ifndef SEQUENTIALFILE_H
#define SEQUENTIALFILE_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Registros.h"
#include <ctgmath>
#include <cstdio>

const std::string BinSuffix = ".dat";
const std::string AuxSuffix = "_aux" + BinSuffix;
const std::string CSVSuffix = ".csv";

struct NextLabel
{
    int nextRow;
    char nextRowFile;
};

bool operator==(NextLabel a, NextLabel b)
{
    return a.nextRow == b.nextRow && a.nextRowFile == b.nextRowFile;
}
bool operator!=(NextLabel a, NextLabel b)
{
    return !(a == b);
}

std::ostream &operator<<(std::ostream &os, NextLabel n)
{
    os.write((char *)&n, sizeof(NextLabel));
    return os;
}

std::istream &operator>>(std::istream &is, NextLabel &n)
{
    is.read((char *)&n, sizeof(NextLabel));
    return is;
}

template <typename Record>
class SequentialFile
{
private:
    int row_sizeof, eliminados, sizeData, sizeAux, K_max_aux;
    std::string base_path;
    void CSV_Loader(std::string _base_path);

public:
    void reorganize();
    SequentialFile(std::string _base_path);
    void add(Record reg);
    template <typename Key_t>
    std::vector<Record> rangeSearch(Key_t begin_key, Key_t end_key);
    template <typename Key_t>
    void remove(Key_t key);
    template <typename Key_t>
    Record search(Key_t key);
    void loadAll(std::vector<Record> &regs, std::vector<NextLabel> &labs);
};

template <typename Record>
template <typename Key_t>
void SequentialFile<Record>::remove(Key_t key)
{
    if (eliminados >= K_max_aux)
        reorganize();

    std::fstream dataFile(base_path + BinSuffix, std::ios::out | std::ios::in | std::ios::binary), auxFile(base_path + AuxSuffix, std::ios::in | std::ios::binary);

    // Binary Search to find key in dataFile
    dataFile.seekg(0, std::ios::end);
    int l = 0, r = (dataFile.tellg() - row_sizeof - sizeof(NextLabel)) / row_sizeof;

    Record RowMatch, key_to_row(key);
    NextLabel RowPtr, PreviousRowPtr{0, 'd'}, PreviousRowPtrReader;

    while (l <= r)
    {
        int m = (l + r) / 2;
        dataFile.seekg(sizeof(NextLabel) + m * row_sizeof, std::ios::beg);
        dataFile >> RowMatch;
        if (RowMatch < key_to_row)
        {
            l = m + 1;
        }
        else if (RowMatch > key_to_row)
        {
            r = m - 1;
        }
        else
        {
            dataFile >> RowPtr;
            PreviousRowPtr.nextRow = m + 1;
            break;
        }
    }
    // Linear search to find key in AuxFile in case key not found in dataFile
    if (!(l <= r) || RowPtr.nextRow == 0)
    {
        PreviousRowPtr.nextRow = 1;
        PreviousRowPtr.nextRowFile = 'a';
        auxFile.seekg(0, std::ios::beg);
        while (auxFile >> RowMatch)
        {
            if (RowMatch != key_to_row)
            {
                auxFile.ignore(sizeof(NextLabel));
            }
            else
            {
                auxFile >> RowPtr;
                if (RowPtr.nextRow != 0)
                    break;
            }
            PreviousRowPtr.nextRow++;
        }
    }

    // Error if key not found
    if (key_to_row != RowMatch || RowPtr.nextRow == 0)
        throw("Llave no hallada");

    // Find row which ptr points to the key row

    // Check if first pointer in dataFile points to row
    dataFile.seekg(0, std::ios::beg);
    dataFile >> PreviousRowPtrReader;
    if (PreviousRowPtrReader == PreviousRowPtr)
    {
        dataFile.seekp(0, std::ios::beg);
        dataFile << RowPtr;
    }
    else
    {
        // Binary Search to find ptr in dataFile
        l = 0;
        dataFile.seekg(0, std::ios::end);
        r = (dataFile.tellg() - row_sizeof - sizeof(NextLabel)) / row_sizeof;

        while (l <= r)
        {
            int m = (l + r) / 2;
            dataFile.seekg(m * row_sizeof, std::ios::beg);
            dataFile >> PreviousRowPtrReader;
            if (PreviousRowPtrReader == PreviousRowPtr)
            {
                dataFile.seekp(m * row_sizeof, std::ios::beg);
                dataFile << RowPtr;
                break;
            }
            else if (PreviousRowPtrReader.nextRow < PreviousRowPtr.nextRow)
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        // Linear search in auxFile

        auxFile.seekg(0, std::ios::end);
        r = auxFile.tellg() / row_sizeof;
        for (l = 0; l < r, PreviousRowPtrReader != PreviousRowPtr; r++)
        {
            auxFile.seekg(row_sizeof * l - sizeof(Record), std::ios::beg);
            auxFile >> PreviousRowPtrReader;
            if (PreviousRowPtrReader == PreviousRowPtr)
            {
                auxFile.seekp(row_sizeof * l - sizeof(Record), std::ios::beg);
                auxFile << RowPtr;
                break;
            }
        }
    }

    if (PreviousRowPtr.nextRowFile == 'd')
    {
        dataFile.seekp(row_sizeof * PreviousRowPtr.nextRow, std::ios::beg);
        PreviousRowPtr.nextRow = 0;
        dataFile << PreviousRowPtr;
        sizeData--;
    }
    else
    {
        auxFile.seekp((PreviousRowPtr.nextRow - 1) * row_sizeof + sizeof(Record), std::ios::beg);
        PreviousRowPtr.nextRow = 0;
        auxFile << PreviousRowPtr;
        sizeAux--;
    }
    eliminados++;

    dataFile.close();
    auxFile.close();
}

template <typename Record>
void SequentialFile<Record>::reorganize()
{
    sizeData += sizeAux;
    sizeAux = 0;
    K_max_aux = static_cast<int>(log2(sizeData)) + 1;

    std::fstream fileData(base_path + BinSuffix, std::ios::in | std::ios::binary);
    std::fstream fileAux(base_path + AuxSuffix, std::ios::in | std::ios::binary);

    std::string copyFileName = "tCopy.dat";
    std::fstream tempCopyWrite(copyFileName, std::ios::out | std::ios::app | std::ios::binary);

    NextLabel printPtr;
    Record printRecord;
    fileData >> printPtr;
    while (printPtr.nextRow != -1)
    {
        tempCopyWrite << printPtr;
        if (printPtr.nextRowFile == 'd')
            fileData >> printRecord >> printPtr;
        else
            fileAux >> printRecord >> printPtr;
        tempCopyWrite << printRecord;
    }
    tempCopyWrite << printPtr;

    tempCopyWrite.close();
    fileData.close();
    fileAux.close();

    fileData.open(base_path + BinSuffix, std::ios::trunc | std::ios::out);
    fileData.close();

    tempCopyWrite.open(copyFileName, std::ios::in | std::ios::binary);
    fileData.open(base_path + BinSuffix, std::ios::out | std::ios::binary | std::ios::app);

    tempCopyWrite >> printPtr;
    while (printPtr.nextRow != -1)
    {
        fileData << printPtr;
        tempCopyWrite >> printRecord >> printPtr;
        fileData << printRecord;
    }
    fileData << printPtr;

    tempCopyWrite.close();
    fileData.close();

    std::remove(copyFileName.c_str());
    fileAux.open(base_path + AuxSuffix, std::ios::trunc | std::ios::out);
    fileAux.close();
}

template <typename Record>
void SequentialFile<Record>::loadAll(std::vector<Record> &regs, std::vector<NextLabel> &labs)
{
    std::ifstream fileData(base_path + BinSuffix, std::ios::in | std::ios::binary);

    NextLabel l;
    Record r;
    fileData >> l;
    labs.push_back(l);
    while (fileData >> r >> l)
    {
        regs.push_back(r);
        labs.push_back(l);
    }
    fileData.close();
    fileData.open(base_path + AuxSuffix, std::ios::in | std::ios::binary);
    while (fileData >> r >> l)
    {
        regs.push_back(r);
        labs.push_back(l);
    }
    fileData.close();
}

template <typename Record>
template <typename Key_t>
std::vector<Record> SequentialFile<Record>::rangeSearch(Key_t begin_key, Key_t end_key)
{
    if (begin_key == end_key)
    {
        std::vector<Record> result;
        result.push_back(search(begin_key));
        return result;
    }
    Record key_group[2] = {Record(begin_key), Record(end_key)};

    if (key_group[0] > key_group[1])
        throw("La llave de inicio es mayor a la final");
    else if (key_group[0] == key_group[1])
        return std::vector<Record>{search<Key_t>(begin_key)};

    Record row_group[2];
    NextLabel label_group[2];

    std::ifstream fileData(base_path + BinSuffix, std::ios::in | std::ios::binary);
    std::ifstream fileAux(base_path + AuxSuffix, std::ios::in | std::ios::binary);
    for (int i = 0; i < 2; i++)
    {
        int l = 0;
        fileData.seekg(0, std::ios::end);
        int r = (fileData.tellg() - row_sizeof - sizeof(NextLabel)) / row_sizeof;
        while (l <= r)
        {
            int m = (l + r) / 2;
            fileData.seekg(sizeof(NextLabel) + m * row_sizeof, std::ios::beg);
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
        if (key_group[i] != row_group[i] || label_group[i].nextRow == 0)
        {
            fileAux.seekg(0, std::ios::beg);

            while (fileAux >> row_group[i])
            {
                if (row_group[i] == key_group[i])
                {
                    fileAux >> label_group[i];
                    if (label_group[i].nextRow != 0)
                        break;
                }
                else
                    fileAux.ignore(sizeof(NextLabel));
            }

            if (row_group[i] != key_group[i] || label_group[i].nextRow == 0)
                i ? throw("Llave de cierre no encontrada") : throw("Llave de inicio no encontrada");
        }
    }

    std::vector<Record> result{row_group[0]};

    while (!(label_group[0] == label_group[1]))
    {
        if (label_group[0].nextRowFile == 'd')
        {
            fileData.seekg((label_group[0].nextRow - 1) * row_sizeof + sizeof(NextLabel), std::ios::beg);
            fileData >> row_group[0] >> label_group[0];
        }
        else
        {
            fileAux.seekg((label_group[0].nextRow - 1) * row_sizeof, std::ios::beg);
            fileAux >> row_group[0] >> label_group[0];
        }
        result.push_back(row_group[0]);
    }

    fileAux.close();
    fileData.close();

    return result;
}

template <typename Record>
template <typename Key_t>
Record SequentialFile<Record>::search(Key_t key)
{
    std::ifstream file(base_path + BinSuffix, std::ios::in | std::ios::binary);

    file.seekg(0, std::ios::end);
    int l = 0;
    int r = (file.tellg() - row_sizeof - sizeof(NextLabel)) / row_sizeof;

    Record result, objective(key);
    NextLabel removeChecker;

    while (l <= r)
    {
        int m = (l + r) / 2;
        file.seekg(sizeof(NextLabel) + m * row_sizeof, std::ios::beg);
        file >> result;
        if (objective > result)
            l = m + 1;
        else if (objective < result)
            r = m - 1;
        else
        {
            file >> removeChecker;
            break;
        }
    }
    file.close();

    if (l <= r && removeChecker.nextRow != 0)
        return result;

    file.open(base_path + AuxSuffix, std::ios::in | std::ios::binary);

    while (file >> result)
    {
        if (result == objective)
        {
            file.close();
            return result;
        }
        file.ignore(sizeof(NextLabel));
    }

    file.close();
    throw("No encontrado");
    return Record();
}

template <typename Record>
void SequentialFile<Record>::add(Record reg)
{
    if (sizeAux >= K_max_aux)
        reorganize();

    std::fstream fileAux(base_path + AuxSuffix, std::ios::in | std::ios::out | std::ios::binary);
    std::fstream fileData(base_path + BinSuffix, std::ios::in | std::ios::out | std::ios::binary);

    fileData.seekg(0, std::ios::end);
    int l = 0, r = (fileData.tellg() - row_sizeof - sizeof(NextLabel)) / row_sizeof;
    int n_regs = r + 1;
    Record prev;
    int prev_ptr_offset;
    bool prev_in_aux = false;
    while (l <= r)
    {
        int m = (l + r) / 2;
        fileData.seekg(sizeof(NextLabel) + m * row_sizeof, std::ios::beg);
        fileData >> prev;
        if (reg > prev)
            l = m + 1;
        else if (reg < prev)
            r = m - 1;
        else
            break;
    }

    if (l <= r)
        throw("La llave debe ser diferente");

    NextLabel prev_ptr;
    if (r == -1)
    {
        fileData.seekg(0, std::ios::beg);
        fileData >> prev_ptr;
    }
    else
    {
        fileData.seekg(l * row_sizeof - sizeof(Record), std::ios::beg);
        fileData >> prev >> prev_ptr;
        prev_ptr_offset = fileData.tellg() - sizeof(NextLabel);
    }

    Record aux_prev;
    fileAux.seekg(0, std::ios::beg);
    while (fileAux >> aux_prev)
    {
        if (reg == aux_prev)
            throw("La llave debe ser diferente");
        else if ((r == -1 || aux_prev > prev) && aux_prev < reg)
        {
            if (r == -1)
                r--;
            prev = aux_prev;
            fileAux >> prev_ptr;
            prev_ptr_offset = fileAux.tellg() - sizeof(NextLabel);
            if (!prev_in_aux)
                prev_in_aux = true;
        }
        else
            fileAux.ignore(sizeof(NextLabel));
    }

    fileAux.close();
    fileAux.open(base_path + AuxSuffix, std::ios::out | std::ios::binary | std::ios::app);
    fileAux.seekp(0, std::ios::end);
    fileAux << reg << prev_ptr;
    fileAux.close();

    fileAux.open(base_path + AuxSuffix, std::ios::in | std::ios::out | std::ios::binary);
    fileAux.seekg(0, std::ios::end);
    prev_ptr = {((int)fileAux.tellp()) / row_sizeof, 'a'};

    if (!prev_in_aux)
    {
        if (r == -1)
            fileData.seekp(0, std::ios::beg);
        else
            fileData.seekp(prev_ptr_offset, std::ios::beg);
        fileData << prev_ptr;
    }
    else
    {
        fileAux.seekp(prev_ptr_offset, std::ios::beg);
        fileAux << prev_ptr;
    }

    fileData.close();
    fileAux.close();

    sizeAux++;
}

template <typename Record>
void SequentialFile<Record>::CSV_Loader(std::string csv)
{
    std::ifstream csv_file(csv, std::ios::in);
    std::string temp;
    std::vector<Record> registros;
    while (getline(csv_file, temp))
    {
        Record registro;
        registro.readCSVLine(temp);
        registros.push_back(registro);
    }
    std::sort(registros.begin(), registros.end());

    sizeData = registros.size();

    csv_file.close();

    std::ofstream ogData(base_path + BinSuffix, std::ios::out | std::ios::binary | std::ios::app);
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

template <typename Record>
SequentialFile<Record>::SequentialFile(std::string _base_path)
    : base_path(_base_path), row_sizeof(sizeof(Record) + sizeof(NextLabel))
{
    const std::string binaryDB = base_path + BinSuffix, auxDB = base_path + AuxSuffix;
    std::fstream fCreate(auxDB, std::ios::in | std::ios::out | std::ios::app);
    fCreate.seekg(0, std::ios::end);
    sizeAux = fCreate.tellg() / row_sizeof;
    fCreate.close();
    fCreate.open(binaryDB, std::ios::in | std::ios::out | std::ios::app);
    fCreate.seekp(0, std::ios::end);
    if (fCreate.tellp() == 0)
    {
        fCreate.close();
        const std::string csvDB = base_path + CSVSuffix;
        CSV_Loader(csvDB);
    }
    fCreate.close();

    fCreate.open(binaryDB, std::ios::in | std::ios::binary);
    fCreate.seekg(0, std::ios::end);
    sizeData = (fCreate.tellg() - sizeof(NextLabel)) / row_sizeof;
    K_max_aux = static_cast<int>(log2(sizeData)) + 1;
    fCreate.close();
}

#endif
