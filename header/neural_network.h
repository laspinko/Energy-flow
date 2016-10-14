#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include<iostream>
#include<vector>

struct Connection;
class Neuron;
class NeuNet;

struct Connection {
public:
    Connection(double w, Neuron &rec);

    Connection();

    Connection(const Connection &other);

    Connection operator=(const Connection &other);

    ~Connection();

    void print() const;


    double weight;
    Neuron *recipient;
protected:
private:
};

class Neuron {
public:
    Neuron();

    Neuron(const Neuron &other);

    Neuron operator=(const Neuron &other);

    ~Neuron();

    void setSynapses(Connection syn[]);

    void print() const;
protected:
private:
    double value;
    Connection *synapses;
    int numSynapses;
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
