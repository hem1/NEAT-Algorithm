//
//  ANN.hpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 07/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

//reset delta to zero on forward feed and set it on backward prop to reduce memory on recursion

#ifndef ANN_hpp
#define ANN_hpp
#include <iostream>
#include "Neuron.hpp"
#include "Genotype.hpp"
#include "Synapse.hpp"

using namespace std;



class Network{
    //feedforward ann
private:
    vector<Neuron*> input_layer;
    vector<Neuron*> output_layer;
    vector<Neuron*> hidden_layer;
    vector<Neuron*> neuron_list;
    
    vector<double> target_output;
    vector<double> nw_output;
    
    
public:
    void constructNetwork(Genotype genome);
    vector<double> forwardPropagation();
    void setTargetForANN(vector<double> t);
    void setInputForANN(vector<double> v);
    vector<double> getOutputFromANN();
    
    void backPropagation();
    void setOutputLayerDelta();
    void setHiddenLayerDelta();
    void updateWeights();
    
    void printOutput();
    
    ~Network();
};


#endif /* ANN_hpp */
