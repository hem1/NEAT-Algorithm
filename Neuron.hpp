//
//  Neuron.hpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 09/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#ifndef Neuron_hpp
#define Neuron_hpp

#include <iostream>
#include <cmath>

#include "Synapse.hpp"

using namespace std;
class Synapse;
class Neuron{
    
private:
    //    int node_id;
    vector<Synapse*> inSynapse;
    vector<Synapse*> outSynapse;
    double sum_input;
    double output;
    double delta;
    double eta;
    bool is_delta_set;
    
    double activationFunction(double val);
    double activationFunctionDerivative(double val);
    
public:
    Neuron();
    ~Neuron();
    void addIncommingSynapses(Synapse* s);
    void addOutgoingSynapses(Synapse* s);
    double retOutput();
    //recursively from output neurons
    double getOutput();
    double getDelta();
    
    vector<Synapse*> getIncommingSynapses();
    vector<Synapse*> getOutgoingSynapses();
    
    //To be used only for input neurons
    void setOutput(double o);
    void setOutputDelta(double val);
    void setHiddenDelta();
    void adjustWeights();
    
};
#endif /* Neuron_hpp */
