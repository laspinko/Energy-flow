#include"neural_network.h"


Connection::Connection(double w, Neuron& rec) {
    weight = w;
    recipient = &rec;
}

Connection::Connection(){
    weight = 0;
}

Connection::Connection(const Connection &other) {
    weight = other.weight;
    recipient = other.recipient;
}

Connection Connection::operator=(const Connection &other) {
    weight = other.weight;
    recipient = other.recipient;
}

Connection::~Connection() {

}

void Connection::print() const{
    std::cout << "Connection to: (";
    recipient -> print();
    std::cout << ")";
}

Neuron::Neuron(){
    value = 0;
    numSynapses = 0;
    synapses = new Connection[numSynapses];
}

Neuron::Neuron(const Neuron &other) {
    value = other.value;
    setSynapses(other.synapses);
}

Neuron Neuron::operator=(const Neuron &other) {
    value = other.value;
    setSynapses(other.synapses);
}

Neuron::~Neuron() {
    if(synapses) delete[] synapses;
}

void Neuron::setSynapses(Connection syn[]) {
    if(synapses) delete[] synapses;
    numSynapses = sizeof(*syn) / sizeof(syn[0]);
    synapses = new Connection[numSynapses];
    for(int i = 0; i < numSynapses; i ++){
        synapses[i] = Connection(syn[i].weight, *syn[i].recipient);
    }
}

void Neuron::print() const{
    std::cout << "Neuron : " << value << std::endl;
    std::cout << numSynapses << " synapses :" << std::endl;
    for(int i = 0; i < numSynapses; i ++){
        synapses[i].print();
    }
}




NeuNet::NeuNet() {

}

NeuNet::NeuNet(const NeuNet &other) {

}

NeuNet NeuNet::operator=(const NeuNet &other) {

}

NeuNet::~NeuNet() {

}

