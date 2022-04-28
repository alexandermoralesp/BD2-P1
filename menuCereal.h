#ifndef MENUCEREAL_H
#define MENUCEREAL_H

#include "Sequential/SequentialFile.h"

namespace menuCereal
{
    bool insert(std::string);
    std::string search(std::string);
    bool remove(std::string);
    std::string rangeSearch(std::string, std::string);
};

bool menuCereal::insert(std::string line){
    Registros::Cereal traduccion;
    traduccion.readCSVLine(line);
    std::string direccion_base = "cereal";
    SequentialFile<Registros::Cereal> sf(direccion_base);
    try{
        sf.add(traduccion);
    }
    catch(...){
        return false;
    }
    return true;
}

std::string menuCereal::search(std::string key){
    std::string direccion_base = "cereal";
    SequentialFile<Registros::Cereal> sf(direccion_base);
    try{
        Registros::Cereal objetivo = sf.search(key);
        return objetivo.writeCSVLine();
    }
    catch(...){
        return "";
    }
}

bool menuCereal::remove(std::string key){
    std::string direccion_base = "cereal";
    SequentialFile<Registros::Cereal> sf(direccion_base);
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

std::string menuCereal::rangeSearch(std::string inicio, std::string fin){
    std::string direccion_base = "cereal";
    SequentialFile<Registros::Cereal> sf(direccion_base);
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