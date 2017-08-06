//
//  Species.hpp
//  SnakeGAME
//
//  Created by Hemanta Pun on 01/07/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#ifndef Species_hpp
#define Species_hpp

#include <iostream>
#include <vector>

#include "Population.hpp"
#include "SnakeGAME/constants.h"

using namespace std;

class Species{
private:
    vector<Population> species;
    //    double threshold;
    
    
    
public:
    //    Species();
    void speciate(Population p);
    double calculateDelta(Genotype A, Genotype B, int n);
    void adjustFitness();
    
    
    void printSpecies();
    void setPopulationSize(int tot_pop);
    Population returnPopulation(); //flatten species as population
    void orderSpecies();    //sort species by fitness
    
    void betterPopandXover(Population p);
    
    void findBetterPopulation(); //select better species
    void crossOver();
    void mutation(Population p);
    
    
    
    
};


#endif /* Species_hpp */
