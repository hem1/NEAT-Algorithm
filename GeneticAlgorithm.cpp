//
//  GeneticAlgorithm.cpp
//  NeuroEvolution of Augmenting Topologies
//
//  Created by Hemanta Pun on 11/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#include "GeneticAlgorithm.hpp"

double getRandomDouble(int min, int max){
    //returns random double; inclusive
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(min, max);
    return (dis(gen));
}
int getRandomInt(int min, int max){
    //returns random int; inclusive
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return (dis(gen));
}
bool coinToss(double probability){
    //probability p of giving head(True)
    random_device random_device;
    mt19937 random_engine{random_device()};
    bernoulli_distribution coin_distribution{probability};
    return coin_distribution(random_engine);
}
Genotype getCrossOver(Genotype parent1, Genotype parent2){
    Genotype g;
    
    //addGeneNode of both parents
    vector<GeneNode> parent1Nodes = parent1.getGeneNodes();
    vector<GeneNode> parent2Nodes = parent2.getGeneNodes();
    
    for(int i = 0; i< parent1Nodes.size(); i++)
        g.addGeneNode(parent1Nodes[i]);
    
    for(int i =  0 ; i<parent2Nodes.size(); i++)
    {
        //add node of parent2 if not in parent1
        bool found = false;
        for(int j =0; j< parent1Nodes.size(); j++)
        {
            if(parent2Nodes[i].node_Id == parent1Nodes[j].node_Id)
            {   found = true;
                break;
            }
        }
        if (found == false)
        {
            g.addGeneNode(parent2Nodes[i]);
        }
    }
    
    
    //add node connections of both parents
    
    //    vector<GeneConnection> tmp1, tmp2, tmpg;
    //    
    //    int n1 = (int) parent1.getConnection().size();
    //    int n2 = (int) parent2.getConnection().size();
    //    int l1 = parent1.getConnection()[n1-1].innovation;
    //    int l2 = parent2.getConnection()[n2-1].innovation;
    //    
    //    
    //    int large = (l1>l2) ? l1 : l2;
    //    
    //    vector<GeneConnection> con1 = parent1.getConnection();
    //    vector<GeneConnection> con2 = parent2.getConnection();
    //    GeneConnection null_connection = parent1.createGeneConnection(0, 0, 0.0, DISABLED, 0);
    //    
    //    int i1 = 0;
    //    int i2 = 0;
    //    
    //    for(int j = 1; j<= large; j++)
    //    {
    //        if( i1 < n1 && con1[i1].innovation == j )
    //        {
    //            tmp1.push_back(con1[i1]);
    //            i1++;
    //        }
    //        else
    //            tmp1.push_back(null_connection);
    //        
    //        if(i2 < n2 && con2[i2].innovation == j)
    //        {
    //            tmp2.push_back(con2[i2]);
    //            i2++;
    //        }
    //        else
    //            tmp2.push_back(null_connection);
    //    }
    //    
    //    for(int j = 0; j< large; j++)
    //    {
    //        if( (tmp1[j].innovation != 0) && (tmp2[j].innovation != 0) )
    //        {
    //            if(coinToss(0.5))
    //                g.addConnection(tmp1[j]);
    //            else
    //                g.addConnection(tmp2[j]);
    //        }
    //        else if(tmp1[j].innovation != 0 && parent1.getFitness() > parent2.getFitness())
    //        {
    //            g.addConnection(tmp1[j]);
    //        }
    //        else if(tmp2[j].innovation != 0 && parent2.getFitness() > parent1.getFitness() )
    //        {
    //            g.addConnection(tmp2[j]);
    //        }
    //        
    //    }
    //    
    //    for(int j = 0; j< large; j++)
    //    {
    //        if(tmpg[j].innovation != 0)
    //            g.addConnection(tmpg[j]);
    //    }
    
    
    
    
    int n1, n2;
    vector<GeneConnection> con1, con2;
    if(parent1.getFitness() > parent2.getFitness())
    {
        n1 = (int) parent1.getConnection().size();
        n2 = (int) parent2.getConnection().size();
        con1 = parent1.getConnection();
        con2 = parent2.getConnection();
        
    }
    else
    {
        n1 = (int) parent2.getConnection().size();
        n2 = (int) parent1.getConnection().size();
        con1 = parent2.getConnection();
        con2 = parent1.getConnection();
    }
    
    for(int i = 0; i<n1; i++)
    {
        bool found = false;
        for(int j = 0; j< n2; j++)
        {
            if(con1[i].innovation == con2[j].innovation)
            {
                found = true;
                if(coinToss(0.5))
                    g.addConnection(con1[i]);
                else
                    g.addConnection(con2[j]);
                break;
            }
        }
        if(!found)
        {
            g.addConnection(con1[i]);
        }
    }
    
    
    
    //    if(g.getConnection().size()>300)
    //    {
    //        cout<<"probably xover error   here"<<endl;
    //        cout<<g.getConnection().size()<<endl;
    //        
    //    }
    return g;
}

Genotype getMutateAddNode(Population p, Genotype g){
    //add node
    int node_size = (int)g.getGeneNodes().size();
    int conn_size = (int)g.getConnection().size();
    int r = getRandomInt(0, conn_size-1); //select random connection
    g.disableConnection(r);                 
    
    //create hidden neuron
    g.addGeneNode(g.createGeneNode(node_size+1, HIDDEN));
    
    struct GeneConnection c = g.getConnection()[r];
    struct GeneConnection con1;
    struct GeneConnection con2;
    
    if(c.in<1 || c.out>2000)
    {
        cout<< c.in<<" "<<c.out<<endl;
        //        cout<<" w "<<c.weight<<" st "<<c.status<<" inn "<<c.innovation<<endl;
        while(1);
    }
    con1.in = c.in;
    con1.out = node_size+1;
    
    con2.in = node_size+1;
    con2.out = c.out;
    
    con1.weight = 1;
    con2.weight = c.weight;
    
    con1.status = ENABLED;
    con2.status = ENABLED;
    
    con1.innovation = p.getInnovation(con1);
    con2.innovation = p.getInnovation(con2);
    
    g.addConnection(con1);
    g.addConnection(con2);
    
    //    cout<<"in1: "<<con1.in<<" out1: "<<con1.out<<endl;
    //    cout<<"in2: "<<con2.in<<" out2: "<<con2.out<<endl;
    //    if(g.getConnection().size()>300) {cout<<"probably mutation error here"<<g.getConnection().size()<< endl; }
    return g;
    
}
Genotype getMutateAddConnection(Population::Population p, Genotype g){
    //add connection between random two input node and hidden layer node which are not connected
    vector<int> inputNodes;
    vector<int> otherNodes;
    vector<vector<int>> possible_connections;
    
    for(auto const& i:g.getGeneNodes())
    {
        if(i.node_type == INPUT)
            inputNodes.push_back(i.node_Id);
        else
            otherNodes.push_back(i.node_Id);
    }
    
    //calculate all possible connections
    for(auto const& i: inputNodes)
    {
        for(auto const& j:otherNodes)
            possible_connections.push_back({i,j});
    }
    
    for(auto const& i: g.getConnection())
    {
        vector<int> tmp = {i.in, i.out};
        //remove existing connections
        possible_connections.erase(remove(possible_connections.begin(), possible_connections.end(), tmp), possible_connections.end());
    }
    if(possible_connections.size()>0)
    {
        int index = getRandomInt(0, (int)possible_connections.size()-1);
        struct GeneConnection c;
        c.in =      possible_connections[index][0];
        c.out =     possible_connections[index][1];
        c.weight =  getRandomDouble(-1, 1);
        c.status =  ENABLED;
        c.innovation = p.getInnovation(c);
        
        //add connection to g
        g.addConnection(c);
    }
    return g;
}
Genotype getMutateInvertConnectionStatus(Genotype g)
{
    int r = getRandomInt(0, (int)g.getConnection().size()-1);
    g.invertConnection(r);
    return g;
}
Genotype getRandomWeight(Genotype g){
    int r = getRandomInt(0, (int)g.getConnection().size()-1);
    g.setRandomWeight(r);
    return g;
}
Genotype getUniformWeightIncrease(Genotype g){
    int r = getRandomInt(0, (int)g.getConnection().size()-1);
    g.addUniformWeight(r);
    return g;
}
Population getBetterPopulation(Population pop_in, Population p){
    //remove 50% of lowest performing individuals and replace them 
    Population pop_out;
    
    int size = pop_in.getSize();
    int r_size = (size * 0.5);
    vector<Genotype> in = pop_in.getPopulation();
    
    
    r_size = ((size * 0.25)< 1) ? 1 : (size *0.25);
    //add the most fit genome directly
    pop_out.addToPopulation(in[0]);
    
    //clone 25% of genes
    for(int i = 1; i< r_size; i++) {
        int r = getRandomInt(0, r_size-1);
        
        pop_out.addToPopulation(in[r]);
    }
    //remaining is added by crossing over 2 genome
    for(int i = r_size; i< size; i++) {
        int r = getRandomInt(0, r_size-1);
        int s = getRandomInt(0, r_size-1);
        
        pop_out.addToPopulation(getCrossOver(in[r], in[s]));
    }
    
    if(pop_in.getSize() != pop_out.getSize())
    {
        cout<<"error in size";
        exit(1);
//        while(1);
    }
    
        
    return pop_out;
}


//Population getBetterPopulation(Population pop_in){
//    //remove 50% of lowest performing individuals and replace them by random better ones
//    Population pop_out;
//    
//    int size = pop_in.getSize();
//    int r_size = (size * 0.5);
//    vector<Genotype> in = pop_in.getPopulation();
//    
//    for(int i = 0; i< size; i++)
//    {
//        if(i <= r_size)
//        {
//            pop_out.addToPopulation(in[i]);
//            pop_out.addToPopulationFitness(in[i].getFitness());
//        }
//        
//        else{
//            int a = getRandomInt(0, ((size-1)-r_size));
//            pop_out.addToPopulation(in[a]);
//            pop_out.addToPopulationFitness(in[a].getFitness());
//        }
//    }
//    
//    return pop_out;
//}




