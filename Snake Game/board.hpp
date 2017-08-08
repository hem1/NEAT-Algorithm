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

struct position{
    int x;
    int y;
};

class Board
{
    
private:
    vector<struct position> snake;
    volatile int direction;
    
    
    bool game_over;
    struct position food_pos;
    
    vector<double> perc;
    
    int no_of_steps_without_eating;
    
    double fitness;
    double food_consumed;
    double dist_travelled;
    double dist_fm_food;
    double prev_dist_fm_food;
    double food_dist_penalty;
    
    
    int getRandomNumber(int min, int max);
    double getAngle(struct position v);
    vector<double> getpercpt(struct position v);
    struct position rotateRight(struct position v);
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
    int isGameOver(struct position v);
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
