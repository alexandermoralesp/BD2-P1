#ifndef REGISTROS_H
#define REGISTROS_H

#include <string>
#include <cstdio>

using namespace std;

namespace Registros
{
    struct Cereal;
}

struct Registros::Cereal
{
    string id; // name
    char mfr, type;
    int calories, protein, fat, sodium, fiber, carbo, sugars, potass, vitamins, shelf;
    float weight, cups, rating;
    void readCSVLine(string st);
    bool operator<(Registros::Cereal c);
};

istream& operator>>(istream& is, Registros::Cereal &c){
    int len;
    is.read((char*) &len, sizeof(int));
    char* buffer = new char[len];
    is.read(buffer, len);
    c.id = buffer;
    is.read((char *)&c.mfr, sizeof(char));
    is.read((char *)&c.type, sizeof(char));
    is.read((char *)&c.calories, sizeof(int));
    is.read((char *)&c.protein, sizeof(int));
    is.read((char *)&c.fat, sizeof(int));
    is.read((char *)&c.sodium, sizeof(int));
    is.read((char *)&c.fiber, sizeof(int));
    is.read((char *)&c.carbo, sizeof(int));
    is.read((char *)&c.sugars, sizeof(int));
    is.read((char *)&c.potass, sizeof(int));
    is.read((char *)&c.vitamins, sizeof(int));
    is.read((char *)&c.shelf, sizeof(int));
    is.read((char *)&c.weight, sizeof(float));
    is.read((char *)&c.cups, sizeof(float));
    is.read((char *)&c.rating, sizeof(float));

    delete[] buffer;
    return is;
}

ostream &operator<<(ostream &os, Registros::Cereal c)
{
    int len = c.id.size();
    os.write((char *)&len, sizeof(int));
    os.write(c.id.c_str(), c.id.size());
    os.write((char *)&c.mfr, sizeof(char));
    os.write((char *)&c.type, sizeof(char));
    os.write((char *)&c.calories, sizeof(int));
    os.write((char *)&c.protein, sizeof(int));
    os.write((char *)&c.fat, sizeof(int));
    os.write((char *)&c.sodium, sizeof(int));
    os.write((char *)&c.fiber, sizeof(int));
    os.write((char *)&c.carbo, sizeof(int));
    os.write((char *)&c.sugars, sizeof(int));
    os.write((char *)&c.potass, sizeof(int));
    os.write((char *)&c.vitamins, sizeof(int));
    os.write((char *)&c.shelf, sizeof(int));
    os.write((char *)&c.weight, sizeof(float));
    os.write((char *)&c.cups, sizeof(float));
    os.write((char *)&c.rating, sizeof(float));

    return os;
}

bool Registros::Cereal::operator<(Registros::Cereal c)
{
    int minlen = (id.size() < c.id.size() ? id.size() : c.id.size());
    for (int i = 0; i < minlen; i++)
    {
        if (id[i] < c.id[i])
            return true;
        else if (id[i] > c.id[i])
            return false;
    }

    return id.size() < c.id.size();
}

void Registros::Cereal::readCSVLine(string st)
{
    char *stName = new char[st.size()];
    sscanf(st.c_str(), "%[^,],%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f", stName, &mfr, &type, &calories, &protein, &fat, &sodium, &fiber, &carbo, &sugars, &potass, &vitamins, &shelf, &weight, &cups, &rating);
    id = stName;
    delete[] stName;
}

#endif