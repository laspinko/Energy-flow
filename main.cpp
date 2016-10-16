#include<iostream>
#include<random>
#include<ctime>
#include"header/neural_network.h"

void b(int a[]) {
    for(int i = 0; i < 3; i ++){
        std::cout << a[i];
    }
}

double inp() {
    return (rand() % 100) / 100.0;
}
void outp(double d) {
    std::cout << "NeuNet returned: " << d << std::endl;
}

int main(){
    srand(time(0));

    NeuNet a;
    a.setInputFunction(0, inp);
    a.setOutputFunction(1, outp);
    a.setOutputFunction(2, outp);
    for(int i = 0; i < 10; i ++) {
        a.makeStep();
        std::cout << std::endl;
    }
}
