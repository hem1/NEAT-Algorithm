//
//  Genotype.hpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 07/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

//  Genotype contains Node genes and gene conection
//
//  node e.g., (node1 input), (node2 input),(node3 input),(node4 hidden),(node5 output)
//  gene connection e.g.,
//      (in 1, out 4, weight 0.7, enabled, innov 1)
//      (in 2, out 4, weight -0.3, enabled, innov 3)
//      (in 2, out 5, weight 0.3, disabled, innov 4)
//      (in 3, out 5, weight 0.2, enabled, innov 5)
//      (in 4, out 5, weight 0.2, enabled, innov 6)
//      (in 5, out 4, weight 0.9, enabled, innov 10)



#ifndef Genotype_hpp
#define Genotype_hpp

#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include "SnakeGAME/constants.h"


//#define INPUT             0
//#define HIDDEN            1
//#define OUTPUT            2
//
//#define ENABLED           3
//#define DISABLED          4
//#define del_weight        0.2

using namespace std;

struct GeneNode{
    int node_Id;
    int node_type;
};

struct GeneConnection{
    int in;
    int out;
    double weight;
    int status;         // ENABLED/DISABLED
    int innovation;
};

class Genotype{
private:
    //defines the topology/structure of n/w
    vector<GeneNode> genes;
    vector<GeneConnection> connections;
    
public:
    double fitness;
    Genotype();
    void addGeneNode(GeneNode g);
    void addConnection(GeneConnection c);
    struct GeneNode createGeneNode(int n_id, int n_type);
    struct GeneConnection createGeneConnection(int i, int o, double w, int s, int inn);
    
    vector<GeneNode> getGeneNodes();
    vector<GeneConnection> getConnection();
    void printGene();
    void disableConnection(int i);
    void invertConnection(int i);
    double getRandomWeight(double l, double u);
    void setRandomWeight(int i);
    void addUniformWeight(int i);
    void setFitness(double f);
    double getFitness();
    
    
    
};




#endif /* Genotype_hpp */
