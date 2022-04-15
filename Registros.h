#ifndef REGISTROS_H
#define REGISTROS_H

#include <string>
#include <cstdio>

using namespace std;

namespace Registros
{
    struct Cereal;
}

const int max_name_len = 50;

struct Registros::Cereal
{
    Cereal() = default;
    Cereal(string key);
    char id[max_name_len]; // name
    char mfr, type;
    int calories, protein, fat, sodium, fiber, carbo, sugars, potass, vitamins, shelf;
    float weight, cups, rating;
    void readCSVLine(string st);
    bool operator==(Registros::Cereal c);
    bool operator<(Registros::Cereal c);
    bool operator>(Registros::Cereal c);
};



Registros::Cereal::Cereal(string key)
{
    int length = key.copy(id, max_name_len);
    id[length] = '\0';
}

istream& operator>>(istream& is, Registros::Cereal &c){
    is.read((char*) &c, sizeof(Registros::Cereal));
    return is;
}

ostream& operator<<(ostream& os, Registros::Cereal c){
    os.write((char*) &c, sizeof(Registros::Cereal));
    return os;
}

bool Registros::Cereal::operator>(Registros::Cereal c){
    return !(string(id)==string(c.id) || string(id)<string(c.id));
}

bool Registros::Cereal::operator==(Registros::Cereal c){
    return string(id)==string(c.id);
}

bool Registros::Cereal::operator<(Registros::Cereal c)
{
    int thislen = string(id).size(), clen = string(c.id).size();
    int minlen = (thislen <  clen? thislen : clen);
    for (int i = 0; i < minlen; i++)
    {
        if (id[i] < c.id[i])
            return true;
        else if (id[i] > c.id[i])
            return false;
    }

    return thislen < clen;
}

void Registros::Cereal::readCSVLine(string st)
{
    sscanf(st.c_str(), "%[^,],%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f", id, &mfr, &type, &calories, &protein, &fat, &sodium, &fiber, &carbo, &sugars, &potass, &vitamins, &shelf, &weight, &cups, &rating);
}

#endif