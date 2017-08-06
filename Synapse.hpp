//
//  Synapse.hpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 09/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#ifndef Synapse_hpp
#define Synapse_hpp

#include <stdio.h>
#include <vector>
#include "Neuron.hpp"

using namespace std;
class Neuron;

class Synapse{
private:
    Neuron* fmNeuron;
    Neuron* toNeuron;
    
    double weight;
    
public:
    //constructor
    Synapse(double w, Neuron* fm, Neuron* to);
    //setters
    void addWeight(double w);
    void  setfmNeuron(Neuron* n);
    void settoNeuron(Neuron* n);
    //getters
    double getWeight();
    Neuron* getfmNeuron();
    Neuron* gettoNeuron();
    
};


#endif /* Synapse_hpp */
