#include"neural_network.h"

//Connection

Connection::Connection(double w, Neuron& rec) {
    weight = w;
    recipient = &rec;
    value = 0;
}

Connection::Connection(){
    weight = 0;
    value = 0;
}

Connection::Connection(const Connection &other) {
    weight = other.weight;
    recipient = other.recipient;
    value = other.value;
}

Connection Connection::operator=(const Connection &other) {
    weight = other.weight;
    recipient = other.recipient;
    value = other.value;
}

Connection::~Connection() {

}

double Connection::getWeight() {
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
    std::cout << "-- " << value << " --> " << recipient -> getId();
}

//Neuron

Neuron::Neuron(int d){
    value = 0;
    id = d;
    numSynapses = 0;
    synapses = new Connection[numSynapses];
}

Neuron::Neuron(const Neuron &other) {
    value = other.value;
    id = other.id;
    setSynapses(other.synapses);
}

Neuron Neuron::operator=(const Neuron &other) {
    value = other.value;
    id = other.id;
    setSynapses(other.synapses);
}

Neuron::~Neuron() {
    if(synapses) delete[] synapses;
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

int Neuron::getId(){
    return id;
}

void Neuron::setId(int d){
    id = d;
}

void Neuron::setSynapses(Connection syn[]) {
    if(synapses) delete[] synapses;
    numSynapses = sizeof(*syn) / sizeof(syn[0]);
    synapses = new Connection[numSynapses];
    for(int i = 0; i < numSynapses; i ++){
        synapses[i] = Connection(syn[i]);
    }
}

void Neuron::print() const{
    std::cout << "Value : " << value << std::endl;
    std::cout << numSynapses << " synapses ";
    for(int i = 0; i < numSynapses; i ++){
        synapses[i].print();
        if(i + 1 != numSynapses)    std::cout << ",";
    }
    std::cout << std::endl;
}

// NeuNet

NeuNet::NeuNet() {

    //Sample network

    numNeurons = 5;
    neurons = new Neuron[numNeurons];
    Connection syn[1];
    for(int i = 0; i < numNeurons; i ++) {
        if(i + 1 != numNeurons) {
            syn[0] = Connection( 1.0 / ( i + 1 ) , neurons[i+1]);
            neurons[i].setSynapses(syn);
        }
        neurons[i].setId(i);
    }

}

NeuNet::NeuNet(const NeuNet &other) {

}

NeuNet NeuNet::operator=(const NeuNet &other) {

}

NeuNet::~NeuNet() {
    delete[] neurons;
}

void NeuNet::makeStep() {
    neurons[0].setValue(1);

    for(int i = 0; i < numNeurons; i ++) {
        neurons[i].distributeCharge();
    }
    for(int i = 0; i < numNeurons; i ++) {
        neurons[i].transferCharge();
    }

    neurons[0].setValue(1);
}

void NeuNet::print() const {
    std::cout << "Neural network:" << std::endl;
    for(int i = 0; i < numNeurons; i ++){
        std::cout << i << ":" << std::endl;
        neurons[i].print();
        std::cout << std::endl;
    }
}
