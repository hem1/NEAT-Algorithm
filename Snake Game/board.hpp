//
//  board.hpp
//  SnakeGAME
//
//  Created by Hemanta Pun on 06/10/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "constants.h"

using namespace std;

class Board
{
private:
    vector<vector <int> > snake;
    volatile int direction;
    
    
    bool game_over;
    vector<int> food_pos;
    vector<double> perc;
    
    int fitness;
    int score;
    int energy;
    int dist_travelled;
    int dist_fm_food;
    
    
    int getRandomNumber(int min, int max);
    double getAngle(vector<int> v);
    vector<double> getpercpt(vector<int> v);
    vector<int> rotateRight(vector<int> v);
    int oppositeDir(int a, int b);
    vector<double> orVectors(vector<double> v1, vector<double>v2);
    double hitWall(int dir);
    void clearBoard();
    
public:
    Board();
    int gameboard[ROW][COL];
    int gameOver();
    
    void updateBoard();
    void printBoard();
    void moveSnake();
    void setDirection(int d);
    int getDirection();
    int isGameOver(vector<int> v);
    void generateFood();
    double getFitness();
    int getMoveForSnake(vector<double> v);
    
    vector<double> getInputForANN();
    vector<double> getPerception();
    vector<double> getTargetMove();
    vector<double> normalizeInput(vector<double> p);
    double mapminmax(double x, int xmin, int xmax, int ymin, int ymax);
    double mapstd(double x, double xmean , double xstd, double ystd, double ymean);

    
};




#endif /* board_hpp */
