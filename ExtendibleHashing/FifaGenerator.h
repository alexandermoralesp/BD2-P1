#ifndef TITANICGENERATOR_H
#define TITANICGENERATOR_H

#include "CSVReader.h"
#include "ExtendibleHashing.h"
using namespace std;

std::string Registros::CartaFifa::writeCSVLine(){
    char result[100];
    sprintf(result, "%s,%c,%s,%c,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", id, foot, position, awr, dwr, ovr, pac, sho, pas, dri, def, phy, sm, div, pos, han, ref, kic, spd);
    return std::string(result);
}

std::string readAt(long pos) {
  Registros::CartaFifa fifa;
  ifstream fin("fifa.dat", ios::binary);
  if (!fin.is_open()) throw ("File not open");
  fin.seekg(pos, ios::beg);
  fin >> fifa;
  fifa.show();
  return fifa.writeCSVLine();
}

void read_all_from_dat() {
  ifstream fin("fifa.dat", ios::binary | ios::in);
  if (!fin.is_open()) {
    throw runtime_error("Could not open file");
  }
  // fin.seekg(88, ios::beg);
  Registros::CartaFifa r;
  fin >> r;
  int i = 0;
  while (i < 10) {
    fin >> r;
    r.show();
    i++;
  }
  fin.close();
}

void generate_fifa_dat() {
  ifstream fin("fifa.csv");
  if (!fin.is_open()) {
    cout << "Error al abrir el archivo" << endl;
    return;
  }
  Registros::CartaFifa fifa;
  std::string line;
  ofstream fout("fifa.dat", ios::binary | ios::out | ios::in | ios::app);
  if (!fout.is_open()) {
    cout << "Error al abrir el archivo" << endl;
    return;
  }
  getline(fin, line);
  while (getline(fin, line)) {
    fifa.readCSVLine(line);
    //fifa.show();
    fout << fifa;
  }
  fin.close();
}

#endif  // fifaGENERATOR_H