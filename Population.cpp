//
//  Population.cpp
//  NeuroEvolution of Augmenting Topologies
//
//  Created by Hemanta Pun on 11/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#include "Population.hpp"

int innovation = 0;

vector<Genotype> Population::getPopulation(){
    return population;
}
int Population:: getInnovation(struct GeneConnection c){
    for(int i=0;i<connection_list.size();i++)
    {
        if(connection_list[i].in == c.in && connection_list[i].out == c.out)
            return connection_list[i].innovation;
    }
    
    c.innovation = ++innovation;
    connection_list.push_back(c);
    
    return c.innovation;
}
Genotype Population::createGene(){
    //create simple input and output layers , no hidden layer
    Genotype gene;
    
    //create Gene Node
    //input layer
    for(int i = 1; i<=INPUT_LAYER_SIZE;i++)
        gene.addGeneNode(gene.createGeneNode(i, INPUT));
    
    //output layer
    for(int i = 1; i<=OUTPUT_LAYER_SIZE;i++)
        gene.addGeneNode(gene.createGeneNode((INPUT_LAYER_SIZE+i), OUTPUT));
    
    
    //create Gene connections
    for(int i = 1; i<= INPUT_LAYER_SIZE; i++)
    {
        for(int j = 1; j<=OUTPUT_LAYER_SIZE; j++)
        {
            //initially all nodes are connected
            int status = ENABLED;
            
            //check if connection exists-> to increase innovation no
            struct GeneConnection c = gene.createGeneConnection( (i), (INPUT_LAYER_SIZE+j), getRandomDouble(-1,1), status, 0);
            c.innovation = getInnovation(c);
            
            gene.addConnection(c);
        }
    }
    
    return gene;
}
Population::Population(){
    population_size = 0;
    fitness_of_population = 0.0;
}
void Population:: generatePopulation(int n){
    population_size = n;
    for(int i=0;i<population_size;i++)
    {
        population.push_back(createGene());
    }
}
int Population::getSize(){
    return population_size;
}
void Population:: increaseSize(int n){
    population_size += n;
}
void Population:: addToPopulation(Genotype g){
    population.push_back(g);
    population_size++;
}
void Population::printPopulation(){
    cout<<"size of population is "<<population_size<<endl;
    for(int i =0; i< population_size; i++)
    {
        cout<<"fitness is ........."<<population[i].getFitness()<<endl;
        //                        population[i].printGene();
        //        cout<<"size of "<<i<<" : "<<population[i].getConnection().size()<<endl;
        
        
    }
}
void Population:: addToPopulationFitness(double f){
    fitness_of_population += f;
}
void Population::replaceGene(Genotype g, int n){
    population[n] = g;
}
double Population:: getPopulationFitness(){
    return fitness_of_population;
}
void Population:: setFitnessOfGenes(vector<double> f)
{
    for(int i = 0; i< population_size; i++)
    {
        population[i].setFitness(f[i]);
    }
}

void Population::setFitnessOfGenes(double f, int n){
    // ???? dont work
    population[n].setFitness(f);
    addToPopulationFitness(f);
}
void Population:: setPopulationOffspringSize(int n){
    no_of_offsprings = n;
}
void Population:: clear()
{
    population_size = 0;
    population.clear();
    connection_list.clear();
    fitness_of_population = 0.0;
    no_of_offsprings = 0.0;
}

void Population:: orderPopulation(){
    sort(population.begin(), population.end(),
         [] (const Genotype &a, const Genotype &b)
         {
             return (a.fitness > b.fitness);
         }
         );
}

