//
//  main.cpp
//  SnakeGAME
//
//  Created by Hemanta Pun on 06/10/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#include <iostream>
#include <thread>
#include <fstream>


#include "board.hpp"
#include "constants.h"

#include "../Species.hpp"
#include "../Population.hpp"
#include "../Genotype.hpp"
#include "../ANN.hpp"



using namespace std;

double fitness[pop_size];


//sig_atomic_t volatile done = 0;
//void end_program(int) { done = 1; }
void writeToFile(Genotype g);
void readSolFromFile();
void startGame(Genotype pop, int  i, bool prn_board);

void writeToFile(Genotype g){
    ofstream f;
    f.open("solution.txt");
    
    vector<GeneNode> n = g.getGeneNodes();
    vector<GeneConnection> c = g.getConnection();
    f<<"GeneNodes\n";
    for(int i = 0; i< n.size(); i++)
    {
        f<<n[i].node_Id<<" "<<n[i].node_type<<endl;
    }
    f<<endl;
    f<<"Gene Connections\n";
    for(int i = 0; i< c.size(); i++)
    {
        f<<c[i].in<<" "<<c[i].out<<" "<<c[i].weight<<" "<<c[i].status<<" "<<c[i].innovation<<endl;
    }
    f.close();
}

void readSolFromFile(){
    ifstream f("solution.txt");
    string n_id, n_type;
    string c_in, c_out, c_weight, c_status, c_innovation;
    Genotype g;
    
    if(f.is_open())
    {
        f>>n_id;
        while(1)
        {
            f>>n_id;
            f>>n_type;
            if((n_id == "Gene"))               break;
            
            g.addGeneNode(g.createGeneNode(stoi(n_id), stoi(n_type)));
            cout<<n_id<<" ";
            cout<<n_type<<endl;
        }
        while (!f.eof())
        {
            f>>c_in;
            f>>c_out;
            f>>c_weight;
            f>>c_status;
            f>>c_innovation;
            g.addConnection(g.createGeneConnection(stoi(c_in), stoi(c_out), stod(c_weight), stoi(c_status), stoi(c_innovation)));
        }
        //    g.printGene();
        startGame(g, 0, true);
    }
    
    f.close();
    
    
}

void startGame(Genotype pop, int  i, bool prn_board){
    Network nw;
    Board b;
    nw.constructNetwork(pop);
    
    
    int tot_move = (prn_board == false) ? prn_brd_false : prn_brd_true;
    
    while (!b.gameOver() && (--tot_move))
    {
        nw.setInputForANN(b.getInputForANN());
        nw.forwardPropagation();
       
        b.setDirection(b.getMoveForSnake(nw.getOutputFromANN()));
        
        b.moveSnake();
        b.updateBoard();
        
        nw.setTargetForANN(b.getTargetMove());
        nw.backPropagation();
        
        //        if(b.getScore() >1000)
        //            cout<<" bazingaaa!!";
        if(prn_board)
        {
            b.printBoard();
            cout<<i<<endl;
            cout<<"Score :------------ "<<b.getFitness()<<endl;
            
//            system("sleep 0.05");
        }
    }
    //    cout<<"Game Over "<<b.gameOver()<<endl;
    fitness[i]= b.getFitness();
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout<<"Processing...\n";
    
    if(read_file)
    {
        readSolFromFile();
        exit(0);
    }
    
    Population p;
    p.generatePopulation(pop_size);
    Species s;
    int c = 0;
    int index = 0;
    double max=0.0;
    int iter = iteration;
    
    
    while (++c < iter )
    {
        vector<Genotype> pop;
        pop = p.getPopulation();
        //        cout<<"----------------------------------------------"<<endl;
        if (c%10 ==0)
            cout<<"iteration "<<c<<endl;
        //        p.printPopulation();
        for(int i = 0; i< pop_size; i++)
        {

//                startGame( pop[i],i, true);
            startGame( pop[i],i, false);
        }
        
        max = 0;
        for(int i = 0; i< pop_size; i++)
        {
            //            cout<<"score "<<i<<" : "<<score[i]<<endl;
            p.setFitnessOfGenes(fitness[i], i);
            //find max fitness
            if(max < fitness[i])
            {
                max = fitness[i];
                index = i;
            }
            
        }
        //        cout<<"ite "<<c<<" max fitness : "<<pop[index].getFitness()<<endl;
        
//        if(c%50 == 0)
//        {
//            startGame(pop[index], index, true);
//            writeToFile(pop[index]);
//        }
        
        if((iter - c )== 1)
            break;
        
        s.speciate(p);
        s.orderSpecies();
        s.setPopulationSize(pop_size);
        
        s.betterPopandXover(p);
        s.mutation(p);
        
        //        s.findBetterPopulation();
        //        s.crossOver();
        
        
        
        p.clear();
        p = s.returnPopulation();
        
    }
    
    Genotype sol = p.getPopulation()[index];
    
    //wrtie to file
    writeToFile(sol);
    
    startGame(sol, index, true);
    //    p.getPopulation()[index].printGene();
    //    cout<<index<<endl;
    
    cout<<"Max score is "<<max<<endl;
    cout<<"nodes "<<sol.getGeneNodes().size()<<endl;
    cout<<"conn "<<sol.getConnection().size()<<endl;
    //    sol.printGene();
    s.printSpecies();
    
//    sol.printGene();
    return 0;
}



//int main(int argc, const char * argv[]) {
//    // insert code here...
//    Population p;
//    p.generatePopulation(pop_size);
//    Species s;
//    int c = 0;
//
//
//    thread t[5];                   //change population size
//    while (c<20)
//    {
//
//
//        vector<Genotype> pop;
//        pop = p.getPopulation();
//        cout<<"----------------------------------------------"<<endl;
//            cout<<"iteration "<<++c<<endl;
//        p.printPopulation();
//        for(int i = 0; i< pop_size; i++)
//        {
//            t[i]=thread(startGame, pop[i],i, false);
//        }
//
//        for(int i = 0; i< pop_size; i++)
//        {
//            t[i].join();
//        }
//        int index = 0;
//        int max = 0;
//        for(int i = 0; i< pop_size; i++)
//        {
//            p.setFitnessOfGenes(score[i], i);
//
//            //find max fitness
////            if(max < score[i])
//            {
//                max = score[i];
//                index = i;
//            }
//
//        }
//        s.speciate(p);
//        s.setPopulationSize(pop_size);
//
//        s.findBetterPopulation();
//        s.crossOver();
//        s.mutation(p);
//
//        p.clear();
//        p = s.returnPopulation();
//
//    }
//
//    return 0;
//}
