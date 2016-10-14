#include<iostream>
#include"header/neural_network.h"

void b(int a[]) {
    for(int i = 0; i < 3; i ++){
        std::cout << a[i];
    }
}

int main(){
    Neuron a,b;
    Connection c[2];
    c[0] = Connection(1.0,a);
    b.setSynapses(c);
    b.print();
}
