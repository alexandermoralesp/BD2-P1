#ifndef MENUSEQUENTIAL_H
#define MENUSEQUENTIAL_H

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

const std::string cereal = "cereal";
const std::string fifa = "FIFA22_PlayerCards_Format";

bool insert_S_Fifa(std::string line);
std::string search_S_Fifa(std::string key);
bool remove_S_Fifa(std::string key);
std::string rangeSearch_S_Fifa(std::string inicio, std::string fin);

bool insert_S_Cereal(std::string line);
std::string search_S_Cereal(std::string key);
bool remove_S_Cereal(std::string key);
std::string rangeSearch_S_Cereal(std::string inicio, std::string fin);



bool insert_S_Fifa(std::string line){
    Registros::CartaFifa traduccion;
    traduccion.readCSVLine(line);
    SequentialFile<Registros::CartaFifa> sf(fifa);
    try{
        sf.add(traduccion);
    }
    catch(...){
        return false;
    }
    return true;
}

std::string search_S_Fifa(std::string key){
    SequentialFile<Registros::CartaFifa> sf(fifa);
    try{
        Registros::CartaFifa objetivo = sf.search(key);
        return objetivo.writeCSVLine();
    }
    catch(...){
        return "";
    }
}

bool remove_S_Fifa(std::string key){
    SequentialFile<Registros::CartaFifa> sf(fifa);
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

std::string rangeSearch_S_Fifa(std::string inicio, std::string fin){
    SequentialFile<Registros::CartaFifa> sf(fifa);
    try
    {
        std::vector<Registros::CartaFifa> listaRegistros = sf.rangeSearch(inicio, fin);
        std::string result = "";
        for(Registros::CartaFifa i: listaRegistros){
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


bool insert_S_Cereal(std::string line){
    Registros::Cereal traduccion;
    traduccion.readCSVLine(line);
    SequentialFile<Registros::Cereal> sf(cereal);
    try{
        sf.add(traduccion);
    }
    catch(...){
        return false;
    }
    return true;
}

std::string search_S_Cereal(std::string key){
    SequentialFile<Registros::Cereal> sf(cereal);
    try{
        Registros::Cereal objetivo = sf.search(key);
        return objetivo.writeCSVLine();
    }
    catch(...){
        return "";
    }
}

bool remove_S_Cereal(std::string key){
    SequentialFile<Registros::Cereal> sf(cereal);
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

std::string rangeSearch_S_Cereal(std::string inicio, std::string fin){
    SequentialFile<Registros::Cereal> sf(cereal);
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