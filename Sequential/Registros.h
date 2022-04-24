#ifndef REGISTROS_H
#define REGISTROS_H

#include <string>
#include <cstdio>

namespace Registros
{
    struct Cereal;
}

const int max_name_len = 50;

struct Registros::Cereal
{
    Cereal() = default;
    Cereal(std::string key);
    Cereal(std::string _id, char _attr1, int _attr2, int _attr3);
    Cereal(std::string _id, char _mfr, char _type, int _calories, int _protein, int _fat, int _sodium, int _fiber, int _carbo, int _sugars, int _potass, int _vitamins, int _shelf, float _weight, float _cups, float _rating);
    char id[max_name_len]; // name
    char mfr, type;
    int calories, protein, fat, sodium, fiber, carbo, sugars, potass, vitamins, shelf;
    float weight, cups, rating;
    void readCSVLine(std::string st);
    bool operator==(Registros::Cereal c);
    bool operator!=(Registros::Cereal c);
    bool operator<(Registros::Cereal c);
    bool operator>(Registros::Cereal c);
};

Registros::Cereal::Cereal(std::string _id, char _attr1, int _attr2, int _attr3)
    :mfr(_attr1), type('f'),calories(_attr2), protein(_attr3), fat(3), sodium(2), fiber(12), carbo(32), sugars(1), potass(4), vitamins(7), shelf(0), weight(34.5), cups(89.3), rating(3.1){
        int length = _id.copy(id, max_name_len);
    id[length] = '\0';
}

Registros::Cereal::Cereal(std::string _id, char _mfr, char _type, int _calories, int _protein, int _fat, int _sodium, int _fiber, int _carbo, int _sugars, int _potass, int _vitamins, int _shelf, float _weight, float _cups, float _rating)
    : mfr(_mfr), type(_type), calories(_calories), protein(_protein), fat(_fat), sodium(_sodium), fiber(_fiber), carbo(_carbo), sugars(_sugars), potass(_potass), vitamins(_vitamins), shelf(_shelf), weight(_weight), cups(_cups), rating(_rating)
{
    int length = _id.copy(id, max_name_len);
    id[length] = '\0';
}

Registros::Cereal::Cereal(std::string key)
{
    int length = key.copy(id, max_name_len);
    id[length] = '\0';
}

std::istream &operator>>(std::istream &is, Registros::Cereal &c)
{
    is.read((char *)&c, sizeof(Registros::Cereal));
    return is;
}

std::ostream &operator<<(std::ostream &os, Registros::Cereal c)
{
    os.write((char *)&c, sizeof(Registros::Cereal));
    return os;
}

bool Registros::Cereal::operator>(Registros::Cereal c)
{
    return !(std::string(id) == std::string(c.id) || std::string(id) < std::string(c.id));
}

bool Registros::Cereal::operator==(Registros::Cereal c)
{
    return std::string(id) == std::string(c.id);
}

bool Registros::Cereal::operator!=(Registros::Cereal c)
{
    return !(std::string(id) == std::string(c.id));
}

bool Registros::Cereal::operator<(Registros::Cereal c)
{
    int thislen = std::string(id).size(), clen = std::string(c.id).size();
    int minlen = (thislen < clen ? thislen : clen);
    for (int i = 0; i < minlen; i++)
    {
        if (id[i] < c.id[i])
            return true;
        else if (id[i] > c.id[i])
            return false;
    }

    return thislen < clen;
}

void Registros::Cereal::readCSVLine(std::string st)
{
    sscanf(st.c_str(), "%[^,],%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f", id, &mfr, &type, &calories, &protein, &fat, &sodium, &fiber, &carbo, &sugars, &potass, &vitamins, &shelf, &weight, &cups, &rating);
}

#endif