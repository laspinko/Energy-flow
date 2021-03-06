#include"neural_network.h"

//Connection

Connection::Connection(double w, Neuron& rec) {
    weight = w;
    recipient = &rec;
    value = 0;
}

Connection::Connection() {
    weight = 0;
    value = 0;
}

Connection::Connection(const Connection &other) {
    copy(other);
}

Connection Connection::operator=(const Connection &other) {
    copy(other);
    return *this;
}

Connection::~Connection() {

}

double Connection::getWeight() const{
    return weight;
}

void Connection::setWeight(double w) {
    weight = w;
}

void Connection::hold(double c) {
    value = c;
}

void Connection::transfer() {
    recipient->addValue(value);
    value = 0;
}

void Connection::print() const{
    std::cout << "-- " << value << "--(w" << weight << ")--> " << recipient -> getId();
}

void Connection::copy(const Connection &other) {
    weight = other.weight;
    recipient = other.recipient;
    value = other.value;
}

//Neuron

Neuron::Neuron(int d) {
    value = 0;
    id = d;
    numSynapses = 0;
    synapses = new Connection[numSynapses];
}

Neuron::Neuron(const Neuron &other) {
    copy(other);
}

Neuron Neuron::operator=(const Neuron &other) {
    delete[] synapses;
    copy(other);
    return *this;
}

Neuron::~Neuron() {
    delete[] synapses;
}

void Neuron::addValue(double v) {
    value += v;
}

void Neuron::setValue(double v) {
    value = v;
}

void Neuron::distributeCharge() {
    for(int i = 0; i < numSynapses; i ++) {
        synapses[i].hold( value * synapses[i].getWeight() );
    }
    value = 0;
}

void Neuron::transferCharge() {
    for(int i = 0; i < numSynapses; i ++) {
        synapses[i].transfer();
    }
}

int Neuron::getId() const {
    return id;
}

void Neuron::setId(int d) {
    id = d;
}

void Neuron::setInputFunction(double (&f)(void)) {
    if(type == OUTPUT || type == MIXED) type = MIXED;
    else    type = INPUT;
    input = f;
}


void Neuron::setOutputFunction(void (&f)(double)) {
    if(type == INPUT || type == MIXED) type = MIXED;
    else    type = OUTPUT;
    output = f;
}

void Neuron::getInput() {
    if(type == INPUT || type == MIXED) {
        setValue(input());
    } else {
        std::cerr << "This is not an input neuron";
    }
}

void Neuron::setOutput() {
    if(type == OUTPUT || type == MIXED) {
        output(value);
    } else {
        std::cerr << "This is not an output neuron";
    }
}

void Neuron::setSynapses(int size, Connection syn[]) {
    delete[] synapses;
    numSynapses = size;
    synapses = new Connection[numSynapses];
    for(int i = 0; i < numSynapses; i ++) {
        synapses[i] = Connection(syn[i]);
    }
}

void Neuron::print() const{
    std::cout << "Value : " << value << std::endl;
    std::cout << numSynapses << " synapses ";
    for(int i = 0; i < numSynapses; i ++) {
        synapses[i].print();
        if(i + 1 != numSynapses)    std::cout << ",";
    }
    std::cout << std::endl;
}

void Neuron::copy(const Neuron &other) {
    value = other.value;
    id = other.id;
    type = other.type;
    input = other.input;
    output = other.output;
    setSynapses(other.numSynapses, other.synapses);
}

// NeuNet

NeuNet::NeuNet() {

    //Sample network

    numNeurons = 3;
    neurons = new Neuron[numNeurons];
    Connection syn[1];
    for(int i = 0; i < numNeurons; i ++) {
        if(i + 1 != numNeurons) {
            syn[0] = Connection( 1.0 / ( i + 1 ) , neurons[i+1]);
            neurons[i].setSynapses(1,syn);
        }
        neurons[i].setId(i);
    }

}

NeuNet::NeuNet(const NeuNet &other) {
    copy(other);
}

NeuNet NeuNet::operator=(const NeuNet &other) {
    delete[] neurons;
    copy(other);
    return *this;
}

NeuNet::~NeuNet() {
    delete[] neurons;
}

void NeuNet::setInputFunction(int d, double (&inp)(void)) {
    if(d >= 0 && d < numNeurons) {
        neurons[d].setInputFunction(inp);
    } else {
        std::cerr << "Invalid id";
    }
}

void NeuNet::setOutputFunction(int d, void (&outp)(double)) {
    if(d >= 0 && d < numNeurons) {
        neurons[d].setOutputFunction(outp);
    } else {
        std::cerr << "Invalid id";
    }
}

void NeuNet::makeStep() {
    for(int i = 0; i < numNeurons; i ++) {
        if(neurons[i].type == INPUT || neurons[i].type == MIXED) {
            neurons[i].getInput();
        }
    }
    for(int i = 0; i < numNeurons; i ++) {
        neurons[i].distributeCharge();
    }
    for(int i = 0; i < numNeurons; i ++) {
        neurons[i].transferCharge();
    }
    std::cout << "hi";
    for(int i = 0; i < numNeurons; i ++) {
        if(neurons[i].type == OUTPUT || neurons[i].type == MIXED) {
            neurons[i].setOutput();
        }
    }
}

void NeuNet::print() const {
    std::cout << "Neural network:" << std::endl;
    for(int i = 0; i < numNeurons; i ++) {
        std::cout << i << ":" << std::endl;
        neurons[i].print();
        std::cout << std::endl;
    }
}

void NeuNet::copy(const NeuNet &other) {
    numNeurons = other.numNeurons;
    neurons = new Neuron[numNeurons];
    for(int i = 0; i < numNeurons; i ++) {
        Connection syn[other.neurons[i].numSynapses];
        for(int j = 0; j < other.neurons[i].numSynapses; j ++) {
            syn[j] = Connection(other.neurons[i].synapses[j].weight,
                                neurons[other.neurons[i].synapses[j].recipient -> getId()]);
        }
        neurons[i].setSynapses(other.neurons[i].numSynapses,syn);
        neurons[i].setId(i);
        neurons[i].type = other.neurons[i].type;
        neurons[i].input = other.neurons[i].input;
        neurons[i].output = other.neurons[i].output;
    }
}
