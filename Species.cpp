//
//  Species.cpp
//  SnakeGAME
//
//  Created by Hemanta Pun on 01/07/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#include "Species.hpp"


//Species::Species()
//{
//    //threshold to determine if a gene is in the species
//    //if less than threshold , it is in the species otherwise not.
//    //    threshold = 5;
//    
//}
double Species:: calculateDelta(Genotype A, Genotype B, int n){
    double del =    0;
    int excess =    0;
    int disjoint =  0;
    double av_weight_diff = 0;
    
    int i1 = 0;
    int i2 = 0;
    int n1 = (int)A.getConnection().size();
    int n2 = (int)B.getConnection().size();
    vector<GeneConnection> con1 = A.getConnection();
    vector<GeneConnection> con2 = B.getConnection();
    
    while((i1<n1) && (i2<n2))
    {
        if(con1[i1].innovation == con2[i2].innovation)
        {
            av_weight_diff = (av_weight_diff==0) ? (abs(con1[i1].weight - con2[i2].weight)) : ((abs(con1[i1].weight - con2[i2].weight)+av_weight_diff)/2);
            i1++;
            i2++;
        }
        else
        {
            if(con1[i1].innovation < con2[i2].innovation)
            {
                while((con1[i1].innovation < con2[i2].innovation) && (i1<n1))
                {
                    disjoint++;
                    i1++;
                }
            }
            else
            {
                while((con1[i1].innovation > con2[i2].innovation) && (i2<n2))
                {
                    disjoint++;
                    i2++;
                }
            }
        }
    }
    
    excess = (i1<n1) ? (n1-i1) : (n2-i2);
    //    cout<<" e: "<<excess<<" d: "<<disjoint<<" a: "<<av_weight_diff<<endl;
    
    //TODO determine the equation for del value
    del = (c1 * (excess/n)) + (c2 * (disjoint/n)) + (c3 * av_weight_diff);
    //    cout<<"del "<<del<<endl;
    return del;
}

void Species::speciate(Population p){
    vector<Genotype> pop = p.getPopulation();
    int n = p.getSize();
    species.clear();
    
    for(int i = 0; i< n; i++)
    {
        if(species.size() == 0)
        {
            Population temp ;
            temp.addToPopulation(pop[i]);
            temp.addToPopulationFitness(pop[i].getFitness());
            species.push_back(temp);
            
        }
        else
        {
            //compare the genotype with each in every species.
            bool flag = false;
            for(int j=0; j<species.size(); j++)
            {
                double del = calculateDelta(pop[i], species[j].getPopulation()[0], species[j].getSize());
                if(del < threshold)
                {
                    species[j].addToPopulation(pop[i]);
                    species[j].addToPopulationFitness(pop[i].getFitness());
                    flag = true;
                    break;
                }
            }
            if(!flag)
            {
                Population temp;
                temp.addToPopulation(pop[i]);
                temp.addToPopulationFitness(pop[i].getFitness());
                species.push_back(temp);
                flag = true;
            }
        }
    }
}
void Species::printSpecies(){
    cout<<"------------------\n";
    cout<<"no of species is "<<species.size()<<endl;
    for(int i = 0; i< species.size(); i++)
    {
        cout<<i+1<<"] "<<species[i].getPopulation().size()<< endl;
        
        //        cout<<"total fitness of species is "<<species[i].getPopulationFitness()<<endl;
        //                species[i].printPopulation();
    }
}
void Species::adjustFitness(){
    //set normalized fitness of each
    for(int i=0;i<species.size();i++)
    {
        for(int j=0; j< species[i].getPopulation().size();j++)
        {
            double fitness= species[i].getPopulation()[j].getFitness()/species[i].getSize();
            species[i].getPopulation()[j].setFitness(fitness);
            species[i].addToPopulationFitness(fitness);
        }
    }
}
void Species:: setPopulationSize(int tot_pop){
    //set the populatin size of each species proportional to the avg_fitness of the species
    int tot_fitness = 0;
    for(int i = 0; i< species.size();i++)
    {
        tot_fitness += species[i].getPopulationFitness();
    }
    
    for(int i = 0; i< species.size();i++)
    {
        double fitness = species[i].getPopulationFitness();
        int n = int((fitness/ tot_fitness) * tot_pop);
        species[i].setPopulationOffspringSize(n);
    }
}
//void Species:: findBetterPopulation(){
//    for(int i = 0; i<species.size(); i++)
//    {
//        species[i] = getBetterPopulation(species[i], p);
//    }
//    
//    
//}
Population Species:: returnPopulation(){
    //flatten species(vector<vector>) as population(vector)
    Population p;
    for(int i = 0; i<species.size(); i++)
    {
        //        cout<<"size "<<species[i].getPopulation().size()<<endl;
        for(int j = 0; j< species[i].getPopulation().size();j++)
        {
            p.addToPopulation(species[i].getPopulation()[j]);
        }
    }
    return p;
}
void Species:: crossOver(){
    //randomly select 2 genes from a species and perform cross over
    vector<Population> new_pop;
    for(int i = 0; i<species.size();i++)
    {
        Population p;
        int size = species[i].getSize();
        for(int j = 0; j< size; j++)
        {
            int a = getRandomInt(0, size-1);
            int b = getRandomInt(0, size-1);
            Genotype g = getCrossOver(species[i].getPopulation()[a], species[i].getPopulation()[b]);
            
            p.addToPopulation(g);
        }
        
        species[i] = p;
    }
    
}
void Species:: mutation(Population p){
    
    for(int i = 0; i< species.size(); i++)
    {
        int size = species[i].getSize();
        for(int j = 0; j< size; j++)
        {
            int r =  getRandomInt(0, size-1);
            Genotype g = species[i].getPopulation()[r];
            
            if(coinToss(0.1))
            {
                //add connection
                g = getMutateAddConnection(p, g);
            }
            else
            {
                if(coinToss(0.05))
                {
                    //add node
                    g = getMutateAddNode(p, g);
                }
                else if (coinToss(0.1))
                {
                    //invert connection status
                    g = getMutateInvertConnectionStatus(g);
                }
                else if (coinToss(0.1))
                {
                    //randomize weight
                    g = getRandomWeight(g);
                }
                else{
                    //unifrom weight increase
                    g = getUniformWeightIncrease(g);
                }
            }
            species[i].replaceGene(g, r);
            
        }
    }
}



void Species:: orderSpecies(){
    for(int i = 0; i<species.size(); i++)
    {
        species[i].orderPopulation();
    }
    
}

void Species::betterPopandXover(Population p){
    
    for(int i = 0; i< species.size(); i++)
    {
        species[i] = getBetterPopulation(species[i], p);
    }
    
}










