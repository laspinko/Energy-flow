#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include<iostream>
#include<vector>

class Connection;
class Neuron;
class NeuNet;

class Connection {
public:
    Connection(double w, Neuron &rec);

    Connection();

    Connection(const Connection &other);

    Connection operator=(const Connection &other);

    ~Connection();

    double getWeight();

    void setWeight(double w);

    void hold(double c);

    void transfer();

    void print() const;

protected:
private:
    double weight;
    Neuron *recipient;

    double value;
};

class Neuron {
public:
    Neuron(int d = 0);

    Neuron(const Neuron &other);

    Neuron operator=(const Neuron &other);

    ~Neuron();

    void addValue(double v);

    void setValue(double v);

    int getId();

    void distributeCharge();

    void transferCharge();

    void setId(int d);

    void setSynapses(Connection syn[]);

    void print() const;
protected:
private:
    double value;
    Connection *synapses;
    int numSynapses;
    int id;
};

class NeuNet {
public:
    NeuNet();

    NeuNet(const NeuNet &other);

    NeuNet operator=(const NeuNet &other);

    ~NeuNet();

    void makeStep();

    void print() const;
protected:
private:
    Neuron *neurons;
    int numNeurons;
};

#endif
