#include<iostream>
#include"header/neural_network.h"

void b(int a[]) {
    for(int i = 0; i < 3; i ++){
        std::cout << a[i];
    }
}

int main(){
    NeuNet a;
    for(int i = 0; i < 4; i ++) {
        a.makeStep();
        //a.print();
    }

    std::cout << "Copy of a :";

    NeuNet b;
    b = a;


    for(int i = 0; i < 4; i ++) {
        b.makeStep();
        b.print();
    }
}
