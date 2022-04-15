#include "SequentialFile.h"
#include<iostream>

int main(){

    SequentialFile<Registros::Cereal> sf("cereal");

    auto reg = sf.search<string>("Mueslix Crispy Blend");

    auto regs = sf.rangeSearch<string>("Mueslix Crispy Blend", "Smacks");

    return 0;
}