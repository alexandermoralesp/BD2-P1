#ifndef REGISTROS_H
#define REGISTROS_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

namespace Registros {
struct Cereal;
struct CartaFifa;
}  // namespace Registros

const int max_name_len = 50;
const int max_player_name = 40;

struct Registros::CartaFifa {
  CartaFifa() = default;
  CartaFifa(std::string key) { int i = key.copy(this->id, max_player_name); };
  // CartaFifa(std::string _id, char _attr1, int _attr2, int _attr3);
  // CartaFifa(std::string _id, char _foot, std::string _position, char _awr,
  // char _dwr, int ovr, int pac, int sho, int pas, int dri, int def, int phy,
  // int sm, int div, int pos, int han, int ref, int kic, int spd);
  char id[max_player_name];  // PlayerName,
  char foot;
  char position[4];
  char awr, dwr;
  int ovr, pac, sho, pas, dri, def, phy, sm, div, pos, han, ref, kic, spd;
  void readCSVLine(std::string st);
  std::string writeCSVLine(){
    char result[100];
    sprintf(result, "%s,%c,%s,%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", id, foot, position, awr, dwr, ovr, pac, sho, pas, dri, def, phy, sm, div, pos, han, ref, kic, spd);
    return std::string(result);
}
  size_t get_size() {
    return sizeof(id) + sizeof(foot) + sizeof(position) + sizeof(awr) +
           sizeof(dwr) + sizeof(ovr) + sizeof(pac) + sizeof(sho) + sizeof(pas) +
           sizeof(dri) + sizeof(def) + sizeof(phy) + sizeof(sm) + sizeof(div) +
           sizeof(pos) + sizeof(han) + sizeof(ref) + sizeof(kic) + sizeof(spd);
  }
  void show() {
    std::cout << "id: " << id << std::endl;
    std::cout << "foot: " << foot << std::endl;
    std::cout << "position: " << position << std::endl;
    std::cout << "awr: " << awr << std::endl;
    std::cout << "dwr: " << dwr << std::endl;
    std::cout << "ovr: " << ovr << std::endl;
    std::cout << "pac: " << pac << std::endl;
    std::cout << "sho: " << sho << std::endl;
    std::cout << "pas: " << pas << std::endl;
    std::cout << "dri: " << dri << std::endl;
    std::cout << "def: " << def << std::endl;
    std::cout << "phy: " << phy << std::endl;
    std::cout << "sm: " << sm << std::endl;
    std::cout << "div: " << div << std::endl;
    std::cout << "pos: " << pos << std::endl;
    std::cout << "han: " << han << std::endl;
    std::cout << "ref: " << ref << std::endl;
    std::cout << "kic: " << kic << std::endl;
    std::cout << "spd: " << spd << std::endl;
  }
};

std::ifstream &operator>>(std::ifstream &is, Registros::CartaFifa &t) {
  is.read((char *)&t, sizeof(t));
  return is;
}

std::ostream &operator<<(std::ostream &os, Registros::CartaFifa c) {
  os.write((char *)&c, sizeof(c));
  return os;
}

void Registros::CartaFifa::readCSVLine(std::string st) {
  sscanf(st.c_str(),
         "%[^,],%c,%[^,],%[^,],%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
         &id, &foot, &position, &awr, &dwr, &ovr, &pac, &sho, &pas, &dri, &def,
         &phy, &sm, &div, &pos, &han, &ref, &kic, &spd);
}

/* Cereal */

struct Registros::Cereal {
  Cereal() = default;
  Cereal(std::string key);
  Cereal(std::string _id, char _mfr, char _type, int _calories, int _protein,
         int _fat, int _sodium, int _fiber, int _carbo, int _sugars,
         int _potass, int _vitamins, int _shelf, float _weight, float _cups,
         float _rating);
  char id[max_name_len];  // name
  char mfr, type;
  int calories, protein, fat, sodium, fiber, carbo, sugars, potass, vitamins,
      shelf;
  float weight, cups, rating;
  void readCSVLine(std::string st);
  bool operator==(Registros::Cereal c);
  bool operator!=(Registros::Cereal c);
  bool operator<(Registros::Cereal c);
  bool operator>(Registros::Cereal c);
  std::string writeCSVLine() {
    char result[150];
    sprintf(result, "%s,%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f", id, mfr,
            type, calories, protein, fat, sodium, fiber, carbo, sugars, potass,
            vitamins, shelf, weight, cups, rating);
    return std::string(result);
  }
  void show() {
    std::cout << "id: " << id << std::endl;
    std::cout << "mfr: " << mfr << std::endl;
    std::cout << "type: " << type << std::endl;
    std::cout << "calories: " << calories << std::endl;
    std::cout << "protein: " << protein << std::endl;
    std::cout << "fat: " << fat << std::endl;
    std::cout << "sodium: " << sodium << std::endl;
    std::cout << "fiber: " << fiber << std::endl;
    std::cout << "carbo: " << carbo << std::endl;
    std::cout << "sugars: " << sugars << std::endl;
    std::cout << "potass: " << potass << std::endl;
    std::cout << "vitamins: " << vitamins << std::endl;
    std::cout << "shelf: " << shelf << std::endl;
    std::cout << "weight: " << weight << std::endl;
    std::cout << "cups: " << cups << std::endl;
    std::cout << "rating: " << rating << std::endl;
  }
};

Registros::Cereal::Cereal(std::string _id, char _mfr, char _type, int _calories,
                          int _protein, int _fat, int _sodium, int _fiber,
                          int _carbo, int _sugars, int _potass, int _vitamins,
                          int _shelf, float _weight, float _cups, float _rating)
    : mfr(_mfr),
      type(_type),
      calories(_calories),
      protein(_protein),
      fat(_fat),
      sodium(_sodium),
      fiber(_fiber),
      carbo(_carbo),
      sugars(_sugars),
      potass(_potass),
      vitamins(_vitamins),
      shelf(_shelf),
      weight(_weight),
      cups(_cups),
      rating(_rating) {
  int length = _id.copy(id, max_name_len);
  id[length] = '\0';
}

Registros::Cereal::Cereal(std::string key) {
  int length = key.copy(id, max_name_len);
  id[length] = '\0';
}

std::istream &operator>>(std::istream &is, Registros::Cereal &c) {
  is.read((char *)&c, sizeof(Registros::Cereal));
  return is;
}

std::ostream &operator<<(std::ostream &os, Registros::Cereal c) {
  os.write((char *)&c, sizeof(Registros::Cereal));
  return os;
}

bool Registros::Cereal::operator>(Registros::Cereal c) {
  return !(std::string(id) == std::string(c.id) ||
           std::string(id) < std::string(c.id));
}

bool Registros::Cereal::operator==(Registros::Cereal c) {
  return std::string(id) == std::string(c.id);
}

bool Registros::Cereal::operator!=(Registros::Cereal c) {
  return !(std::string(id) == std::string(c.id));
}

bool Registros::Cereal::operator<(Registros::Cereal c) {
  int thislen = std::string(id).size(), clen = std::string(c.id).size();
  int minlen = (thislen < clen ? thislen : clen);
  for (int i = 0; i < minlen; i++) {
    if (id[i] < c.id[i])
      return true;
    else if (id[i] > c.id[i])
      return false;
  }

  return thislen < clen;
}

void Registros::Cereal::readCSVLine(std::string st) {
  sscanf(st.c_str(), "%[^,],%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f", id,
         &mfr, &type, &calories, &protein, &fat, &sodium, &fiber, &carbo,
         &sugars, &potass, &vitamins, &shelf, &weight, &cups, &rating);
}

#endif