#include<iostream>
#include"header/neural_network.h"

void b(int a[]) {
    for(int i = 0; i < 3; i ++){
        std::cout << a[i];
    }
}

int main(){
    NeuNet a;
    a.print();
    for(int i = 0; i < 4; i ++) {
        a.makeStep();
        a.print();
    }
}
