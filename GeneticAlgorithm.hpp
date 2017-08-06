//
//  GeneticAlgorithm.hpp
//  NeuroEvolution of Augmenting Topologies
//
//  Created by Hemanta Pun on 11/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#ifndef GeneticAlgorithm_hpp
#define GeneticAlgorithm_hpp

#include <iostream>
#include <random>
#include <algorithm>

#include "Genotype.hpp"
#include "Population.hpp"

class Population;
class Genotype;

bool coinToss(double probability);
double getRandomDouble(int min, int max);
int getRandomInt(int min, int max);

Genotype getCrossOver(Genotype g1, Genotype g2);

Genotype getMutateAddNode(Population p, Genotype g);
Genotype getMutateAddConnection(Population p, Genotype g);
Genotype getMutateInvertConnectionStatus(Genotype g);
Genotype getRandomWeight(Genotype g);
Genotype getUniformWeightIncrease(Genotype g);

Population getBetterPopulation(Population pop_in, Population p);
//Population getBetterPopulation(Population pop_in);



#endif /* GeneticAlgorithm_hpp */
