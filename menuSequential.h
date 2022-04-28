#ifndef MENUCEREAL_H
#define MENUCEREAL_H

#include "Sequential/SequentialFile.h"

// nombre_csv_sin_ext : Por ejemplo, si el CSV se llama: alfredo.csv, ingresar solo alfredo
// Nombres de los archivos: 
//      cereal.csv -> cereal
//      FIFA22_PlayerCards_Format.csv -> FIFA22_PlayerCards_Format

// insert: (line) Introducir los parametros del registro en una linea csv
    // Se es exitoso, se retorna un 1, de lo contrario un 0
// search:  (key) una cadena de la llave de un regsitro a hallar
    // Se retorna una cadena en formato csv
// remove: ('') ''
    // Se es exitoso, se retorna un 1, de lo contrario un 0
// rangeSearch (inicio) llave con la que se comienza la busqueda, (fin) llave con la que termina la busqueda
    // Se retorna una cadena con los registros en formato csv, de tal manera que entre cada registro hay un \n
namespace menuSequential
{
    bool insert(std::string line, std::string nombre_csv_sin_ext);
    std::string search(std::string key, std::string nombre_csv_sin_ext);
    bool remove(std::string key, std::string nombre_csv_sin_ext);
    std::string rangeSearch(std::string inicio, std::string fin, std::string nombre_csv_sin_ext);
};

bool menuSequential::insert(std::string line, std::string nombre_csv_sin_ext){
    Registros::Cereal traduccion;
    traduccion.readCSVLine(line);
    SequentialFile<Registros::Cereal> sf(nombre_csv_sin_ext);
    try{
        sf.add(traduccion);
    }
    catch(...){
        return false;
    }
    return true;
}

std::string menuSequential::search(std::string key, std::string nombre_csv_sin_ext){
    SequentialFile<Registros::Cereal> sf(nombre_csv_sin_ext);
    try{
        Registros::Cereal objetivo = sf.search(key);
        return objetivo.writeCSVLine();
    }
    catch(...){
        return "";
    }
}

bool menuSequential::remove(std::string key, std::string nombre_csv_sin_ext){
    SequentialFile<Registros::Cereal> sf(nombre_csv_sin_ext);
    try
    {
        sf.remove(key);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

std::string menuSequential::rangeSearch(std::string inicio, std::string fin, std::string nombre_csv_sin_ext){
    SequentialFile<Registros::Cereal> sf(nombre_csv_sin_ext);
    try
    {
        std::vector<Registros::Cereal> listaRegistros = sf.rangeSearch(inicio, fin);
        std::string result = "";
        for(Registros::Cereal i: listaRegistros){
            result += i.writeCSVLine();
            result += "\n";
        }
        return result;
    }
    catch(...)
    {
        return "";
    }
}
#endif