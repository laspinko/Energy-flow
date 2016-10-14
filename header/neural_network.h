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

    double getWeight() const;

    void setWeight(double w);

    void hold(double c);

    void transfer();

    void print() const;

protected:
private:
    void copy(const Connection &other);

    double weight;
    Neuron *recipient;

    double value;

    friend class Neuron;
    friend class NeuNet;
};

class Neuron {
public:
    Neuron(int d = 0);

    Neuron(const Neuron &other);

    Neuron operator=(const Neuron &other);

    ~Neuron();

    void addValue(double v);

    void setValue(double v);

    int getId() const;

    void distributeCharge();

    void transferCharge();

    void setId(int d);

    void setSynapses(int size, Connection syn[]);

    void print() const;
protected:
private:
    void copy(const Neuron &other);

    double value;
    Connection *synapses;
    int numSynapses;
    int id;

    friend class NeuNet;
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
    void copy(const NeuNet &other);

    Neuron *neurons;
    int numNeurons;
};

#endif
