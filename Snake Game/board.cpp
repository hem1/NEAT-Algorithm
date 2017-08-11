//
//  board.cpp
//  SnakeGAME
//
//  Created by Hemanta Pun on 06/10/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#include "board.hpp"

Board::Board(){
    int x = getRandomNumber(0, ROW-4);
    int y = getRandomNumber(0, COL-4);
    
//    snake = { {x,y},{x,y+1},{x,y+2} };
    struct position tmp = {x,y};
    snake.push_back(tmp);
    tmp.y++;
    snake.push_back(tmp);
    tmp.y++;
    snake.push_back(tmp);
    
    
    no_of_steps_without_eating = 0;
    direction = KEY_LEFT;
    //    direction = getRandomNumber(KEY_UP, KEY_LEFT);
    //    while(direction == 67)
    //    {direction=getRandomNumber(KEY_UP, KEY_LEFT);}
    game_over = false;
    fitness = 0.0;
    
    food_dist_penalty = 0.0;
    food_consumed = 0.0;
    dist_travelled = 0.0;
    dist_fm_food = 0.0;
    
    generateFood();
    
    prev_dist_fm_food += (sqrt(pow((snake[0].x - food_pos.x), 2) + pow((snake[0].y - food_pos.y), 2)));

    
    for(int i = 0; i<ROW; i++)
    {
        for(int j = 0; j<COL; j++)
        {
            gameboard[i][j] = 0;
        }
    }
}
double Board::getFitness(){
//    return  (1000 * food_consumed) + (0.1 * dist_travelled)- (10 * food_dist_penalty);
    return  (1000 * food_consumed) + (0.5 * dist_travelled)- (100 * food_dist_penalty);
//    return food_consumed;
    
}
int Board:: getRandomNumber(int min, int max){
    
//    return (rand() %(min+max));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return (dis(gen));
}
int Board::gameOver(){
    return game_over;
}
void Board::printBoard(){
    for(int i = 0; i <=COL; i++)
    {
        cout<<TOP_EDGE;
    }
    cout<<endl;
    for(int i = 0; i<ROW; i++)
    {
        cout<<SIDE_EDGE;
        for(int j = 0; j<COL; j++)
        {
            cout<<pieces[gameboard[i][j]];
        }
        cout<<SIDE_EDGE<<'\n';
    }
    
    for(int i = 0; i <=COL; i++)
    {
        cout<<TOP_EDGE;
    }
    cout<<endl;
    
    cout<< "score : "<<food_consumed<<" steps : "<< dist_travelled<<endl;
}
void Board:: clearBoard(){
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j< COL; j++)
        {
            gameboard[i][j] = EMPTY;
        }
    }
}
void Board::updateBoard(){
    clearBoard();
    for(int i = 0 ; i< snake.size(); i++)
    {
        gameboard[snake[i].x][snake[i].y] = SNAKE;
    }
    gameboard[food_pos.x][food_pos.y] = FOOD;
    //    printBoard();
}
int Board::oppositeDir(int a, int b){
    if(((a==KEY_UP) && (b == KEY_DOWN)) || ((a ==KEY_DOWN) && (b==KEY_UP)))
        return 1;
    else if(((a==KEY_LEFT) && (b==KEY_RIGHT)) || ((b==KEY_LEFT) && (a == KEY_RIGHT)) )
        return 1;
    else
        return 0;
}
void Board::setDirection(int d){
    //!!!! not a good implementation
    //direction from the point of view of snake, straight, left or right.
    //convert snakes move straight, right , left to direction in the board, up, down, right, left
    if(direction == KEY_LEFT)
    {
        if(d == RIGHT)
            direction = KEY_UP;
        else if(d == LEFT)
            direction = KEY_DOWN;
    }
    
    else if(direction == KEY_RIGHT)
    {
        if(d == RIGHT)
            direction = KEY_DOWN;
        else if(d == LEFT)
            direction = KEY_UP;
    }
    
    else if(direction == KEY_UP)
    {
        if(d == RIGHT)
            direction = KEY_RIGHT;
        else if(d == LEFT)
            direction = KEY_LEFT;
    }
    
    else if(direction == KEY_DOWN)
    {
        if(d == RIGHT)
            direction = KEY_LEFT;
        else if(d == LEFT)
            direction = KEY_RIGHT;
    }
    //if straight do nothing
}
int Board::isGameOver(struct position v){
    //check if snake's head hits the wall
    if((v.x < 0) || (v.y < 0) || (v.x >= ROW) || (v.y >= COL))
    {
        //        cout<<"hit wall "<<v[0]<<" "<<v[1]<<endl;
        game_over = true;
        return 1;
    }
    
    //check if snake hits its body
    for(int i = 1;i < snake.size(); i++)
    {
        if((snake[0].x == snake[i].x) && (snake[0].y ==snake[i].y))
        {
            game_over = 1;
            return 1;
        }
    }
    
    
    return 0;
}
int Board::getDirection(){
    return direction;
}
double Board::hitWall(int dir){
    //check if the snake hits wall in next n moves
    double dist = 0.0;
//    switch(dir)
//    {
//        case (KEY_LEFT):
//            
//            dist = double (snake[0].y/COL);
//            break;
//            
//        case (KEY_RIGHT):
//            dist = double(COL - snake[0].y) / COL;
//            break;
//            
//        case (KEY_UP):
//            dist = double(snake[0].x) / ROW;
//            break;
//            
//        case (KEY_DOWN):
//            dist = double(ROW - snake[0].x)/ ROW;
//            break;
//    }
    int n = 5;
    
    switch(dir)
    {
        case (KEY_LEFT):
            
            if((snake[0].y -n )< 0 )
                dist = 1;
            break;
            
        case (KEY_RIGHT):
            if((snake[0].y +n ) > COL-1 )
                dist = 1;            break;
            
        case (KEY_UP):
            if((snake[0].x -n )< 0 )
                dist = 1;
            break;
            
        case (KEY_DOWN):
            if((snake[0].x +n )> COL-1 )
                dist = 1;
            break;
    }
    return dist;
    
}
void Board::moveSnake(){
    struct position v;
    
    switch(direction)
    {
        case (KEY_LEFT):
            v.x = snake[0].x;
            v.y = (snake[0].y - 1);
            break;
            
        case (KEY_RIGHT):
            v.x = (snake[0].x);
            v.y = (snake[0].y + 1);
            break;
            
        case (KEY_UP):
            v.x = (snake[0].x - 1);
            v.y = (snake[0].y);
            break;
            
        case (KEY_DOWN):
            v.x = (snake[0].x + 1);
            v.y = (snake[0].y);
            break;
            
        default :
            break;
    }
    
    if(!isGameOver(v))
    {
        
        snake.insert(snake.begin(), v);
        
        //check if food is eaten
        if((v.x == food_pos.x) && (v.y == food_pos.y))
        {
            food_consumed += 1;
            no_of_steps_without_eating = 0;
            generateFood();
            //snake doesnot grow
            snake.pop_back();
        }
        else
        {
            snake.pop_back();
            no_of_steps_without_eating++;
            if(no_of_steps_without_eating > 100)
                game_over = true;
        }
        dist_travelled++;
        dist_fm_food += (sqrt(pow((snake[0].x - food_pos.x), 2) + pow((snake[0].y - food_pos.y), 2)));
        
        if(prev_dist_fm_food > dist_fm_food) //moving away
        {
            food_dist_penalty++;
        }
        else
            food_dist_penalty--;
        
        prev_dist_fm_food = dist_fm_food;
        
    }
}
void Board::generateFood(){
    vector<int> tmp;
    
    int r, c;
    while(1)
    {
//        r = 0 + rand() % (ROW-1);
//        c = 0 + rand() % (COL-1);
        r = getRandomNumber(0, ROW-1);
        c = getRandomNumber(0, COL-1);
        if(gameboard[r][c] == EMPTY)
            break;
    }
    
    food_pos.x = r;
    food_pos.y = c;
    
    
    
    
}
double Board:: getAngle(struct position v){
    int x = pow((snake[0].y-v.y) ,2);
    int y = pow((snake[0].x-v.x),2 );
    return (atan2(x,y)) * (180/3.14);
}
struct position Board:: rotateRight(struct position v){
    //rotate vector v to right once
    struct position rot;
    int dr, dc;
    
    dr = v.x - snake[0].x;
    dc = v.y - snake[0].y;
    dr = -dr;
    
    rot.x = snake[0].x +dc;
    rot.y = snake[0].y +dr;
    return rot;
}
vector<double> Board:: orVectors(vector<double> v1, vector<double>v2){
    for(int i = 0; i<v1.size(); i++)
    {
        if(v2[i] > v1[i])
            v1[i] = v2[i];
    }
    return v1;
}
vector<double> Board:: getpercpt(struct position v){
    //return reading at 5 positions separated by 20 degrees, so total angle of view is 240 degrees
    //distance / no of cols
    vector<double> p =  {0.0,0.0,0.0,0.0,0.0};
    int n = (direction == KEY_UP) ? 0 : ( (direction-KEY_UP>2)? 1 : (direction-KEY_UP)+1);
    
//    double dist = sqrt(pow((v.x - snake[0].x),2) + pow((v.y-snake[0].y), 2));
//    dist = dist / COL;
    
    //rotate v accordingly, so that snake's direction is up.
    for(int i = 0; i< n; i++)
        v = rotateRight(v);
    
    if(v.x < snake[0].x) //only if v is above snake's head else not visible
    {
        double angle = getAngle(v);
        
        if(angle <18)
            p[2] = 1;
        else if((angle > 18) && (angle < 54))
        {
            if(v.y < snake[0].y) //left side
                p[1] = 1;
            else
                p[3] = 1;
        }
        else
        {
            if(v.y < snake[0].y) //left side
                p[0] = 1;
            else
                p[4] = 1;
        }
        
    }
    
    return p;
}

double Board:: mapminmax(double x, int xmin, int xmax, int ymin, int ymax)
{
    return (ymax-ymin)*(x-xmin) /(xmax-xmin) +ymin;
}

double Board:: mapstd(double x, double xmean , double xstd, double ystd, double ymean)
{
    return ((x-xmean) *(ystd/xstd) +ymean);
}

vector<double> Board:: normalizeInput(vector<double> p)
{
    //mapminmax
    p[0] = mapminmax(p[0], 0, 49, -1, 1);
    p[1] = mapminmax(p[1], 0, 19, -1, 1);
    p[2] = mapminmax(p[2], 0, 49, -1, 1);
    p[3] = mapminmax(p[3], 0, 19, -1, 1);
    
    //mapstd
    double xstd = 0.0;
    double xmean = 0;
    for(int i = 0; i< p.size(); i++)
    {
        xmean += p[i];
    }
    xmean /= p.size();
    
    for(int i = 0; i< p.size(); i++)
    {
        xstd += (pow((p[i] - xmean),2));
    }
    xstd = sqrt(xstd/p.size());
    
    
    for(int i = 0; i< p.size(); i++)
    {
        p[i] = mapstd(p[i], xmean, xstd, 1, 0);
    }
    
    
    return p;
}

//vector<double> Board::getInputForANN(){
//    perc.clear();
//    
//    perc.push_back((double)snake[0][0]);
//    perc.push_back((double)snake[0][1]);
//    perc.push_back((double)food_pos[0]);
//    perc.push_back((double)food_pos[1]);
//    
//    perc = normalizeInput(perc);
//    
//    return perc;
//}


vector<double> Board::getPerception(){
    return perc;
}
vector<double>Board:: getTargetMove(){
    vector<double> out = {0,0,0};
    
    //determine next move before the ann depending on where the food is at
    if(perc[0] > 0  )
        out ={1,0,0};   //left
    else if(perc[4] > 0 )
        out = {0,0,1};  //right
    else
        out = {0,1,0};  //straight
    
    return out;
}

int Board::getMoveForSnake(vector<double> v){
    int ret = 0;
    int index = 0;
    for(int i =0; i< v.size()-1; i++)
    {
        index = (v[i] > v[i+1]) ? i : i+1;
    }
    switch(index)
    {
        case 0:
            ret = LEFT;
            //            cout<<"l \n";
            break;
        case 1:
            ret = STRAIGHT;
            //            cout<<"r \n";
            
            break;
        case 2:
            ret = RIGHT;
            //            cout<<"s \n";
            
            break;
        default:
            break;
    }
    
    return ret;
}


vector<double> Board::getInputForANN(){
    //size of return value is 13
    perc.clear();
    vector<double> p_food;
    vector<double> p_body;
    vector<double> p_wall;


    //find the angle between food_pos and head pos(snake[0][0]).
    //get perception for food
    p_food = getpercpt(food_pos);


    //get perception for body
    p_body = {0.0,0.0,0.0,0.0,0.0};
    for(int i = 1; i<snake.size(); i++ )
    {
        vector<double> tmp = getpercpt(snake[i]);
        p_body = orVectors(p_body, tmp);
    }

    //if the snake sees wall in next 5 steps
    int dir;

    p_wall = {0.0,0.0,0.0};
    p_wall[1] = hitWall(direction);


    //check right
    if(direction == KEY_LEFT)
        dir = KEY_UP;
    else if(direction == KEY_RIGHT)
        dir = KEY_DOWN;
    else if(direction == KEY_UP)
        dir = KEY_RIGHT;
    else if(direction == KEY_DOWN)
        dir = KEY_LEFT;


    p_wall[2] = hitWall(dir);

    //check left
    if(direction == KEY_LEFT)
        dir = KEY_DOWN;
    else if(direction == KEY_RIGHT)
        dir = KEY_UP;
    else if(direction == KEY_UP)
        dir = KEY_LEFT;
    else if(direction == KEY_DOWN)
        dir = KEY_RIGHT;
    p_wall[0] = hitWall(dir);

    perc.insert(perc.end(), p_wall.begin(), p_wall.end());
    perc.insert(perc.end(), p_food.begin(), p_food.end());
    perc.insert(perc.end(), p_body.begin(), p_body.end());

    return perc;
}
