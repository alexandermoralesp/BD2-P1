#ifndef MENUSEQUENTIAL_CPP
#define MENUSEQUENTIAL_CPP

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

#include<stdio.h>
#include<cstring>


extern "C"
bool insert_S_Fifa(char* line){
    Registros::CartaFifa traduccion;
    std::string str(line);
    std::cout<<str;
    traduccion.readCSVLine(str);
    SequentialFile<Registros::CartaFifa> sf(fifa);
    try{
        sf.add(traduccion);
    }
    catch(...){
        return false;
    }
    return true;
}
extern "C"
char* search_S_Fifa(char* key,char* aux){
    SequentialFile<Registros::CartaFifa> sf(fifa);
    try{
        std::string str(key);
        Registros::CartaFifa objetivo = sf.search(key);
        
        char* retorno = objetivo.writeCSVLine(aux);
    
        
        return aux;
        
    }
    catch(...){
        throw "error";
    }
}
extern "C"
bool remove_S_Fifa(char* key){
    SequentialFile<Registros::CartaFifa> sf(fifa);
    std::string str(key);
    try
    {
        sf.remove(str);
    }
    catch(...)
    {
        return false;
    }
    return true;
}
extern "C"
char* rangeSearch_S_Fifa(char* inicio, char* fin, char* result){
    SequentialFile<Registros::CartaFifa> sf(fifa);
    try
    {
        std::string start(inicio);
        std::string end(fin);
        std::vector<Registros::CartaFifa> listaRegistros = sf.rangeSearch(start, end);
        
        for(Registros::CartaFifa i: listaRegistros){
            i.writeCSVLine(result);
        }
        return result;
    }
    catch(...)
    {
        throw "error";
    }
}

extern "C"
bool insert_S_Cereal(char* line){
    Registros::Cereal traduccion;
    std::string str(line);
    traduccion.readCSVLine(str);
    SequentialFile<Registros::Cereal> sf(cereal);
    try{
        sf.add(traduccion);
    }
    catch(...){
        return false;
    }
    return true;
}
extern "C"
char* search_S_Cereal(char* key, char* result){
    SequentialFile<Registros::Cereal> sf(cereal);
    try{
        std::string str(key);
        Registros::Cereal objetivo = sf.search(key);
        char* retorno = objetivo.writeCSVLine(result);
        return result;
    }
    catch(...){
        throw"error";
    }
}
extern "C"
bool remove_S_Cereal(char* key){
    SequentialFile<Registros::Cereal> sf(cereal);
    std::string str(key);
    try
    {
        sf.remove(str);
    }
    catch(...)
    {
        return false;
    }
    return true;
}
extern "C"
char* rangeSearch_S_Cereal(char* inicio, char* fin, char* result,char*aux){
    SequentialFile<Registros::Cereal> sf(cereal);
    try
    {

        std::vector<Registros::Cereal> listaRegistros = sf.rangeSearch(inicio, fin);
        int temp=0 ;
        for(Registros::Cereal i: listaRegistros){
            i.writeCSVLine2(aux);
            
            if (temp ==0){
                temp++;
                strcpy(result,aux);
            }
            else{
                strcat(result,aux);
            }
            
            
            
        }
        
        return result;
    }
    catch(...)
    {
        return "";
    }
}
int main(){
    char aux[150];
    char result [10000];
    rangeSearch_S_Cereal("Apple Cinnamon Cheerios", "Grape Nuts Flakes",result,aux);
    std::cout<<result<<std::endl;
}
#endif