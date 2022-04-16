#include "SequentialFile.h"
#include<iostream>

int main(){


    SequentialFile<Registros::Cereal> sf("cereal");

    /* Registros::Cereal radd{"Consorcio",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999};
    sf.add(radd);

    vector<Registros::Cereal> v1;
    vector<NextLabel> v2;
    sf.loadAll(v1,v2); */

    // auto reg = sf.search<string>("Mueslix Crispy Blend");

    auto regs = sf.rangeSearch<string>("Bran Chex", "Froot Loops");

    return 0;
}