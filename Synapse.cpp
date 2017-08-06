//
//  Synapse.cpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 09/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#include "Synapse.hpp"

Synapse::Synapse(double w, Neuron* fm, Neuron* to)
{
    weight = w;
    fmNeuron = fm;
    toNeuron = to;
}
void Synapse::addWeight(double w)
{
    weight += w;
}
void Synapse::setfmNeuron(Neuron* n)
{
    fmNeuron = n;
}
void Synapse::settoNeuron(Neuron* n)
{
    toNeuron = n;
}
//getters
double Synapse::getWeight()
{
    return weight;
}
Neuron* Synapse::getfmNeuron()
{
    return fmNeuron;
}
Neuron* Synapse::gettoNeuron()
{
    return toNeuron;
}
