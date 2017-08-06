//
//  ANN.cpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 07/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#include "ANN.hpp"

void Network:: constructNetwork(Genotype genome){
    //create nodes in a list
    
    for(int i = 0; i<genome.getGeneNodes().size(); i++)
    {
        Neuron* n = new Neuron();
        neuron_list.push_back(n);
        
        //put the neurons in correct layers
        if(genome.getGeneNodes()[i].node_type == INPUT)
        {
            input_layer.push_back(n);
        }
        else if(genome.getGeneNodes()[i].node_type == HIDDEN)
        {
            hidden_layer.push_back(n);
        }
        else
        {
            output_layer.push_back(n);
        }
        
    }
    
    //make the connection according to the Gene connection
    for(int i = 0; i<genome.getConnection().size(); i++)
    {
        struct GeneConnection connection = genome.getConnection()[i];
        
        if(connection.status == ENABLED)
        {
            Synapse *s = new Synapse(connection.weight, neuron_list[connection.in-1], neuron_list[connection.out-1]);
            neuron_list[connection.in-1]->addOutgoingSynapses(s);
            neuron_list[connection.out-1]->addIncommingSynapses(s);
        }
    }
    
    
    //    //set the inputs
    //    for(int i = 0; i< input_layer.size(); i++)
    //    {
    //        input_layer[i]->setOutput(input_data[i]);
    //    }
    
}
vector<double> Network::forwardPropagation(){
    //set the inputs
    
    nw_output.clear();
    for(int i =0;i< output_layer.size();i++)
    {
        nw_output.push_back(output_layer[i]->getOutput());
    }
    return nw_output;
}
void Network::printOutput(){
    
    cout<<"-------------------------------------------------\n";

    cout<<"input layer"<<endl;
    for(int i = 0; i< input_layer.size();i++)
    {
        
        cout<<"\noutput :"<<input_layer[i]->retOutput();
        for(int j=0; j<input_layer[i]->getOutgoingSynapses().size();j++)
        {
            cout<<"\tw :"<<input_layer[i]->getOutgoingSynapses()[j]->getWeight()<<"\t\t\t";
        }
        
    }
    
    cout<<"\n\nhidden layer \n";
    for(int i = 0; i< hidden_layer.size();i++)
    {
        cout<<"output: "<<hidden_layer[i]->retOutput();
        for(int j=0; j<hidden_layer[i]->getOutgoingSynapses().size();j++)
        {
            cout<<"\t\t\tw :"<<hidden_layer[i]->getOutgoingSynapses()[j]->getWeight()<<" \t\t\t";
            cout<<"d :"<<hidden_layer[i]->getDelta()<<endl;
        }
        
    }
    cout<<"\n\nOutput of network is \n";
    
    for(int i = 0; i< nw_output.size();i++)
    {
        cout<<"output :"<<nw_output[i];
    }
    cout<<"\t\t\td :"<<output_layer[0]->getDelta()<<endl;
    
}
void Network::setTargetForANN(vector<double> t){
    if(target_output.size()!=0)
        target_output.clear();
    for(int i = 0; i< t.size();i++)
    {
        target_output.push_back(t[i]);
    }
}
void Network::setInputForANN(vector<double> v){
    for(int i = 0; i< input_layer.size();i++)
    {
        input_layer[i]->setOutput(v[i]);
    }
}
void Network::setOutputLayerDelta(){
    for(int i=0; i<output_layer.size(); i++)
    {
        output_layer[i]->setOutputDelta(target_output[i]);
    }
}
void Network::setHiddenLayerDelta(){
    for(int i=0; i<output_layer.size(); i++)
    {
        output_layer[i]->setHiddenDelta();
    }
}
void Network::updateWeights(){
    for(int i=0; i<output_layer.size(); i++)
    {
        output_layer[i]->adjustWeights();
    }
}
vector<double> Network::getOutputFromANN(){
    return nw_output;
}
void Network::backPropagation(){
    setOutputLayerDelta();
    setHiddenLayerDelta();
    updateWeights();
//    target_output.clear();
   
}

Network:: ~Network(){
    for(int i = 0; i<neuron_list.size(); i++)
    {
        
        //delete neurons
        delete neuron_list[i];
    }
    input_layer.clear();
    output_layer.clear();
    hidden_layer.clear();
    
}
