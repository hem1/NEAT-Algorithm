//
//  Neuron.cpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 09/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#include "Neuron.hpp"

double Neuron::activationFunction(double val){
    return (1/(1+exp(-val)));
}
double Neuron::activationFunctionDerivative(double val){
    return (val * (1-val));
}
Neuron:: Neuron(){
    sum_input = 0.0;
    output = 0.0;
    eta = 0.25;
    delta = 0.0;
    //to reduce space complexity while computing delta and a flag to rerun backprop multiple times
    is_delta_set = false;
}
void Neuron::addIncommingSynapses(Synapse* s){
    inSynapse.push_back(s);
}
void Neuron::addOutgoingSynapses(Synapse* s){
    outSynapse.push_back(s);
}
double Neuron::retOutput(){
    return output;
}
double Neuron::getDelta(){
    return delta;
}
double Neuron::getOutput(){
    //for input Neurons
    if (inSynapse.size() == 0)
        return output;
    
    //for non-input Neurons
    else
    {
        sum_input=0.0;
        for(int i = 0; i< inSynapse.size(); i++)
        {
            sum_input += inSynapse[i]->getWeight() * ((inSynapse[i]->getfmNeuron())->getOutput());
        }
        //        return out;
        output = activationFunction(sum_input);
        return output;
    }
    
}
vector<Synapse*> Neuron::getIncommingSynapses(){
    return inSynapse;
}
vector<Synapse*> Neuron::getOutgoingSynapses(){
    return outSynapse;
}
//To be used only for input neurons
void Neuron::setOutput(double o){
    output = o;
}
void Neuron::setOutputDelta(double val){
    double error = val - output;
    
    delta = (error * (activationFunctionDerivative(output)));
    is_delta_set = true;
    
}
void Neuron::setHiddenDelta(){
    //for input layer Neurons count of incomming synapse is 0
    if ((inSynapse.size() == 0) || ((outSynapse.size()>0) && (is_delta_set = true)))
        return ;
    
    //for non-input layer Neurons
    else
    {
        for(int i = 0; i< inSynapse.size(); i++)
        {
            Neuron *n = inSynapse[i]->getfmNeuron();
            double sum = 0;
            for(int j=0; j< n->outSynapse.size(); j++) //all synapse
            {
//                sum += ((n->outSynapse[j]->getWeight()) * delta ); //????delta
                sum += ((n->outSynapse[j]->getWeight()) * (n->outSynapse[j]->gettoNeuron()->delta) );
            }
            n->delta = (sum * activationFunctionDerivative(n->getOutput()));
            
            for(int k=0; k< n->inSynapse.size(); k++)
            {
                n->inSynapse[k]->getfmNeuron()->setHiddenDelta();
            }
        }
    }
}
void Neuron::adjustWeights(){
    
    //for input layer Neurons size of synapse is zero
    if ((inSynapse.size() == 0))
        return ;
    
    //for non-input layer Neurons
    else
    {
        is_delta_set = false;
        for(int i = 0; i< inSynapse.size(); i++)
        {
            double delweight = eta * inSynapse[i]->getfmNeuron()->retOutput() *delta;
            inSynapse[i]->addWeight(delweight);
            inSynapse[i]->getfmNeuron()->adjustWeights();
        }
    }
}
Neuron:: ~Neuron(){
    for(int j =0; j<outSynapse.size();j++)
    {
        delete outSynapse[j];
    }
}
