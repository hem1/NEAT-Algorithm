//
//  Population.hpp
//  NeuroEvolution of Augmenting Topologies
//
//  Created by Hemanta Pun on 11/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#ifndef Population_hpp
#define Population_hpp

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


#include "Genotype.hpp"
#include "GeneticAlgorithm.hpp"
#include "SnakeGAME/constants.h"

//input layer should be 13
//#define INPUT_LAYER_SIZE            13
//#define OUTPUT_LAYER_SIZE           3

using namespace std;

class Population{
private:
    int population_size;
    vector<Genotype> population;
    vector<GeneConnection> connection_list; //to maintain innovation number
    
    //used for speciation
    
    double fitness_of_population;   //sum of adjusted fitness of population
    double no_of_offsprings;        //no of offspring allowed , proportion to the finess_of_population used by species
    
    
public:
    Genotype createGene();
    Population();
    void clear();
    int getSize();
    void generatePopulation(int p);
    int getInnovation(struct GeneConnection c);
    vector<Genotype> getPopulation();
    void increaseSize(int n);
    void addToPopulation(Genotype g);
    void printPopulation();
    
    void replaceGene(Genotype g, int n);
    void setFitnessOfGenes(vector<double> f);
    void setFitnessOfGenes(double f, int n);
    
    //used for speciation
    //population size is proportional to fitness_of_population
    void addToPopulationFitness(double f);
    double getPopulationFitness();
    void setPopulationOffspringSize(int n);
    
    
    void orderPopulation();
    
    //keep track of innovation number
};

#endif /* Population_hpp */
