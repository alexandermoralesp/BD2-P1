#include "SequentialFile.h"
#include<iostream>

int main(){

    SequentialFile<Registros::Cereal> sf("cereal");

    vector<Registros::Cereal> regs;

    ifstream file("cereal.dat", ios::in|ios::binary);
    /* for(int i = 0; i<1; i++){
        Registros::Cereal temp;
        int itemp;
        file>>temp;
        file.read((char*) &itemp , sizeof(int));
        regs.push_back(temp);
    }     */
    Registros::Cereal temp;
    while (file>>temp)
    {
        int itemp;
        file.read((char*) &itemp , sizeof(int));
        regs.push_back(temp);
    }
    
    file.close();
    return 0;
}