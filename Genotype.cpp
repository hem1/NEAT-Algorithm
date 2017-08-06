//
//  Genotype.cpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 07/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#include "Genotype.hpp"


Genotype::Genotype(){
    fitness = 0.0;
}
void Genotype::addGeneNode(GeneNode g){
    genes.push_back(g);
}
void Genotype::addConnection(GeneConnection c){
    connections.push_back(c);
}
vector<GeneNode> Genotype::getGeneNodes(){
    return genes;
}
vector<GeneConnection> Genotype:: getConnection(){
    return connections;
}
struct GeneNode Genotype::createGeneNode(int n_id, int n_type){
    struct GeneNode g;
    g.node_Id = n_id;
    g.node_type = n_type;
    return g;
}
struct GeneConnection Genotype::createGeneConnection(int i, int o, double w, int s, int inn){
    struct GeneConnection c;
    c.in = i;
    c.out = o;
    c.weight = w;
    c.status = s;
    c.innovation = inn;
    return c;
}
void Genotype::printGene(){
    cout<<"GeneNodes \n";
    for(int i = 0; i< genes.size();i++)
    {
        cout<<setw(2)<<genes[i].node_Id<<" "<<setw(2)<<genes[i].node_type<<endl;
    }
    cout<<"Connections\n";
    for(int i = 0; i< connections.size();i++)
    {
        cout<<setw(2)<<connections[i].in<<" to "<<setw(2)<<connections[i].out<<" w: "<<setw(7)<<setprecision(3)<<connections[i].weight<<" st: ";
        if(connections[i].status==ENABLED)
            cout<<setw(3)<<"EN";
        else
            cout<<setw(3)<<"DIS";
        
        cout<<" inn : "<<setw(2)<<connections[i].innovation<<endl;;
        
    }
    
}
void Genotype:: disableConnection(int i){
    connections[i].status = DISABLED;
}
void Genotype:: invertConnection(int i){
    if(connections[i].status == ENABLED)
        connections[i].status = DISABLED;
    else
        connections[i].status = ENABLED;
}
double Genotype:: getFitness(){
    return fitness;
}
void Genotype:: setFitness(double f){
    fitness = f;
}

double Genotype:: getRandomWeight(double min, double max){
    //returns random double
    return (min + (rand()/ (RAND_MAX /(max-min) )));
}
void Genotype:: setRandomWeight(int i){
    connections[i].weight = getRandomWeight(-1, 1);
}
void Genotype:: addUniformWeight(int i){
    connections[i].weight += del_weight;
}
