//
//  constants.h
//  SnakeGAME
//
//  Created by Hemanta Pun on 06/10/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#ifndef constants_h
#define constants_h

#define ROW                     20
#define COL                     50

#define TOP_EDGE                '-'
#define SIDE_EDGE               '|'

#define STRAIGHT                201
#define LEFT                    202
#define RIGHT                   203


#define KEY_UP                  65
#define KEY_DOWN                66
#define KEY_RIGHT               67
#define KEY_LEFT                68

#define EMPTY                   0
#define SNAKE                   1
#define FOOD                    2

const char pieces[]={' ' , 'o','x'};

//used in main
#define pop_size                300
#define iteration               100
#define n_movesf                300
#define n_movest                5000

//used in Genotype
#define INPUT                   0
#define HIDDEN                  1
#define OUTPUT                  2
#define ENABLED                 3
#define DISABLED                4
#define del_weight              0.01


//used in Population
#define INPUT_LAYER_SIZE        13
#define OUTPUT_LAYER_SIZE       3


//used in Species
#define threshold               3
#define c1                      2.0
#define c2                      2.0
#define c3                      4.0

#endif /* constants_h */
