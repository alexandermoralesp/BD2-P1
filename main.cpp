#include "SequentialFile.h"
#include<iostream>

int main(){


    SequentialFile<Registros::Cereal> sf("cereal");

    /* sf.add({"100\% Abzzzzz",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999});
    sf.add({"100\% Azzzzzz",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999});
    sf.add({"Chizitos",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999});
    sf.add({"Consorcio",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999});
    sf.add({"Chisitos",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999});
    sf.reorganize(); */
    /* Registros::Cereal radd{"100\% Azzzzzz",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999};
    Registros::Cereal radd1{"Chizitos",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999};
    Registros::Cereal radd2{"Chisitos",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999};
    Registros::Cereal radd3{"Consorcio",'G','C',110,6,2,290,2,17,1,105,25,1,1,1.25,50.764999};
    sf.add(radd);
    sf.add(radd1);
    sf.add(radd2);
    sf.add(radd3); */


    // auto reg = sf.search<string>("Mueslix Crispy Blend");
    // auto regs = sf.rangeSearch<string>("Bran Chex", "Froot Loops");
    vector<Registros::Cereal> v1;
    vector<NextLabel> v2;
    sf.loadAll(v1,v2);
    // auto regs = sf.rangeSearch<string>("100\% Abzzzzz", "Froot Loops");

    try{
        // sf.remove("Cap'n'Crunch");
        // sf.search("Cap'n'Crunch");
        // auto regs = sf.rangeSearch<string>("Cap'n'Crunch", "Froot Loops");
        // auto regs = sf.rangeSearch<string>("Bran Chex", "Cap'n'Crunch");
    }
    catch(char const* a){
        cout<<a;
    }

    return 0;
}