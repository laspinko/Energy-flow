#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include<iostream>

class Neuron {
public:
    Neuron();

    Neuron(const Neuron &other);

    Neuron operator=(const Neuron &other);

    ~Neuron();

    void draw() const;
protected:
private:

};

class NeuNet {
public:
    NeuNet();

    NeuNet(const NeuNet &other);

    NeuNet operator=(const NeuNet &other);

    ~NeuNet();

protected:
private:

};

#endif
