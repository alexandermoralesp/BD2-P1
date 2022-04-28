#ifndef REGISTROS_H
#define REGISTROS_H

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

namespace Registros
{
    struct Cereal;
    struct Titanic;
}

const int max_name_len = 50;

struct Registros::Titanic {
    int passenger_id;
    int pclass;
    char name[max_name_len];
    char sex[8];
    int age;
    int sibsp;
    int parch;
    char ticket[max_name_len];
    int fare;
    char cabin[max_name_len];
    char embarked;
    Titanic(int passenger_id, int pclass, std::string name, std::string sex, int age, int sibsp, int parch, std::string ticket, int fare, std::string cabin, char embarke);
    Titanic(int passenger_id);
    void readCSVLine(std::string st);
};

Registros::Titanic::Titanic(int passenger_id, int pclass, std::string name, std::string sex, int age, int sibsp, int parch, std::string ticket, int fare, std::string cabin, char embarked) {
    this->passenger_id = passenger_id;
    this->pclass = pclass;
    int l1 = name.copy(this->name, max_name_len);
    this->name[l1] = '\0';
    int l2 = sex.copy(this->sex, 5);
    this->sex[l2] = '\0';
    this->age = age;
    this->sibsp = sibsp;
    this->parch = parch;
    int l3 =ticket.copy(this->ticket, max_name_len);
    this->fare = fare;
    int l4 =cabin.copy(this->cabin, max_name_len);
    this->embarked = embarked;
}

Registros::Titanic::Titanic(int passenger_id) {
    this->passenger_id = passenger_id;
}

std::ifstream &operator>>(std::ifstream &is, Registros::Titanic &t) {
    is.read((char*)&t, sizeof(Registros::Titanic));
    return is;
}

std::ostream &operator<<(std::ostream &os, Registros::Titanic c)
{
    os.write((char *)&c, sizeof(Registros::Titanic));
    return os;
}

void Registros::Titanic::readCSVLine(std::string st)
{
    sscanf(st.c_str(), "%d,%d,%[^,],%[^,],%d,%d,%d,%[^,],%d,%[^,],%c", &this->passenger_id, &this->pclass, &this->name, &this->sex, &this->age, &this->sibsp, &this->parch, &this->ticket, &this->fare, &this->cabin, &this->embarked);
}

/* Cereal */

struct Registros::Cereal
{
    Cereal() = default;
    Cereal(std::string key);
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
