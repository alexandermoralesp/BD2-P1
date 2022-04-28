#ifndef REGISTROS_H
#define REGISTROS_H

#include <string>
#include <cstdio>
#include <iostream>

namespace Registros
{
    struct Cereal;
    struct CartaFifa;
}

const int max_name_len = 50;
const int max_player_name = 40;

struct Registros::CartaFifa
{
    CartaFifa() = default;
    CartaFifa(std::string key);
    CartaFifa(std::string _id, char _attr1, int _attr2, int _attr3);
    CartaFifa(std::string _id, char _foot, std::string _position, char _awr, char _dwr, int ovr, int pac, int sho, int pas, int dri, int def, int phy, int sm, int div, int pos, int han, int ref, int kic, int spd);
    char id[max_player_name]; // PlayerName,
    char foot;
    char position[4];
    char awr, dwr;
    int ovr, pac, sho, pas, dri, def, phy, sm, div, pos, han, ref, kic, spd;
    void readCSVLine(std::string st);
    bool operator==(Registros::CartaFifa c);
    bool operator!=(Registros::CartaFifa c);
    bool operator<(Registros::CartaFifa c);
    bool operator>(Registros::CartaFifa c);
    std::string writeCSVLine();
};

std::string Registros::CartaFifa::writeCSVLine(){
    char result[100];
    sprintf(result, "%s,%c,%s,%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", id, foot, position, awr, dwr, ovr, pac, sho, pas, dri, def, phy, sm, div, pos, han, ref, kic, spd);
    return std::string(result);
}

Registros::CartaFifa::CartaFifa(std::string _id, char _attr1, int _attr2, int _attr3)
    : foot(_attr1), ovr(_attr2), sm(_attr3)
{
    int length = _id.copy(id, max_player_name);
    id[length] = '\0';
}

Registros::CartaFifa::CartaFifa(std::string _id, char _foot, std::string _position, char _awr, char _dwr, int _ovr, int _pac, int _sho, int _pas, int _dri, int _def, int _phy, int _sm, int _div, int _pos, int _han, int _ref, int _kic, int _spd)
    :  foot(_foot),  awr(_awr), dwr(_dwr), ovr(_ovr), pac(_pac), sho(_sho), pas(_pas), dri(_dri), def(_def), phy(_phy),  sm(_sm), div(_div), pos(_pos),  han(_han),  ref(_ref), kic(_kic), spd(_spd)
{
    int length = _id.copy(id, max_player_name);
    id[length] = '\0';
    length = _position.copy(position, 4);
    id[length] = '\0';
}

Registros::CartaFifa::CartaFifa(std::string key)
{
    int length = key.copy(id, max_player_name);
    id[length] = '\0';
}

std::istream &operator>>(std::istream &is, Registros::CartaFifa &c)
{
    is.read((char *)&c, sizeof(Registros::CartaFifa));
    return is;
}

std::ostream &operator<<(std::ostream &os, Registros::CartaFifa c)
{
    os.write((char *)&c, sizeof(Registros::CartaFifa));
    return os;
}

bool Registros::CartaFifa::operator>(Registros::CartaFifa c)
{
    return !(std::string(id) == std::string(c.id) || std::string(id) < std::string(c.id));
}

bool Registros::CartaFifa::operator==(Registros::CartaFifa c)
{
    return std::string(id) == std::string(c.id);
}

bool Registros::CartaFifa::operator!=(Registros::CartaFifa c)
{
    return !(std::string(id) == std::string(c.id));
}

bool Registros::CartaFifa::operator<(Registros::CartaFifa c)
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

void Registros::CartaFifa::readCSVLine(std::string st)
{
    sscanf(st.c_str(), "%[^,],%c,%[^,],%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", id, &foot, position, &awr, &dwr, &ovr, &pac, &sho, &pas, &dri, &def, &phy, &sm, &div, &pos, &han, &ref, &kic, &spd);
}

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
    std::string writeCSVLine();
    bool operator==(Registros::Cereal c);
    bool operator!=(Registros::Cereal c);
    bool operator<(Registros::Cereal c);
    bool operator>(Registros::Cereal c);
};

std::string Registros::Cereal::writeCSVLine(){
    char result[150];
    sprintf(result, "%s,%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f", id, mfr, type, calories, protein, fat, sodium, fiber, carbo, sugars, potass, vitamins, shelf, weight, cups, rating);
    return std::string(result);
}

Registros::Cereal::Cereal(std::string _id, char _attr1, int _attr2, int _attr3)
    : mfr(_attr1), type('f'), calories(_attr2), protein(_attr3), fat(3), sodium(2), fiber(12), carbo(32), sugars(1), potass(4), vitamins(7), shelf(0), weight(34.5), cups(89.3), rating(3.1)
{
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