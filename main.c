/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: super
 *
 * Created on September 22, 2016, 8:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define N 11

void printMaze(char maze[][N], int x, int y);
int findBotX(const char maze[][N], int r, int c);
int findBotY(const char maze[][N], int r, int c);
int goUp(char maze[][N], int posX, int posY);
int goLeft(char maze[][N], int posX, int posY);
int goDown(char maze[][N], int posX, int posY);
int goRight(char maze[][N], int posX, int posY);
int checkAround(char maze[][N], int c, int r, int pos);

int main(int argc, char** argv) {
    int ROWS = 11;
    int COLS = 11;
    int alignment = 0;  // This variable represents the alignment of the "car"
    /*when it is equal to 0 it means up
    when it is equal to 1 it means left
    when it is equal to 2 it means down
    when it is equal to 3 it means right
    */
    int botX, botY, counter = 0;
    char maze[11][11] = {{'1','1','1','1','1','Z','1','1','1','1','1'}, {'1',' ',' ',' ','1',' ',' ',' ','1',' ','1'}, {'1',' ','1',' ','1','1','1',' ','1',' ','1'},{'1',' ','1',' ',' ',' ','1',' ',' ',' ','1'},{'1',' ','1','1','1',' ','1','1','1',' ','1'},{'1',' ',' ',' ','1',' ',' ',' ','1',' ','1'},{'1','1','1',' ','1','1','1','1','1',' ','1'},{'1',' ',' ',' ','1',' ',' ',' ',' ',' ','1'},{'1',' ','1','1','1',' ','1','1','1','1','1'},{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},{'1','1','1','1','1','B','1','1','1','1','1'}};
    printMaze(maze, ROWS,COLS);
    printf("\n");
    //botX = findBotX(maze, ROWS, COLS);
    //botY = findBotY(maze, ROWS, COLS);
    //maze[botY-1][botX] = 'U';
    //maze[botY][botX-1] = 'L';
    //maze[botY+1][botX] = 'D';
    //maze[botY][botX+1] = 'R';
    //botX = findBotX(maze, ROWS, COLS);
    //botY = findBotY(maze, ROWS, COLS);
    //maze[botY-1][botX] = 'B';
    //maze[botY][botX] = 'x';
    //printMaze(maze, ROWS,COLS);
    
    do{
        botX = findBotX(maze, ROWS, COLS);
        botY = findBotY(maze, ROWS, COLS);
        if(alignment == 0)
            alignment =  goUp(maze, botX, botY);
        else if(alignment == 1)
            alignment =  goLeft(maze, botX, botY);
        else if(alignment == 2)
            alignment =  goDown(maze, botX, botY);
        else
            alignment =  goRight(maze, botX, botY);
        botX = findBotX(maze, ROWS, COLS);
        botY = findBotY(maze, ROWS, COLS);
        alignment = checkAround(maze, botX, botY, alignment);
        printf("Run %d\n", counter);
        printMaze(maze, ROWS,COLS);
        counter++;
    }while(alignment != 4);
    
    printf("Maze complete!\n");
    return (EXIT_SUCCESS); 
}
/*This method is called when the bot is going up (0). 
 * If the path for the bot is obstructed than the bot will turn left making it's position left (1)
 */
int goUp(char maze[][N], int posX, int posY){
    if(maze[posY-1][posX] == 'Z'){
        maze[posY-1][posX] = 'B';
        maze[posY][posX] = 'x';
        return 4;
    }else if(maze[posY-1][posX] != '1'){
        maze[posY-1][posX] = 'B';
        maze[posY][posX] = 'x';
        return 0;
    }else
        return 1;
}

/*This method is called when the bot is moving left (1)
 * If the path for the bot is obstructed than the bot will turn down (2)
 */
int goLeft(char maze[][N], int posX, int posY){
    if(maze[posY][posX-1] == 'Z'){
        maze[posY][posX-1] = 'B';
        maze[posY][posX] = 'x';
        return 4;
    }else if(maze[posY][posX-1] != '1'){
        maze[posY][posX-1] = 'B';
        maze[posY][posX] = 'x';
        return 1;
    }else
        return 2;
}

/*This method is called when the bot is moving down (2)
 * if the way is obstructed the bot will turn right (3)
 */
int goDown(char maze[][N], int posX, int posY){ //
    if(maze[posY+1][posX] == 'Z'){
        maze[posY+1][posX] = 'B';
        maze[posY][posX] = 'x';
        return 4;
    }else if(maze[posY+1][posX] != '1'){
        maze[posY+1][posX] = 'B';
        maze[posY][posX] = 'x';
        return 2;
    }else
        return 3;
}

/*This method is called when the bot is moving right (3)
 * if the way is obstructed the bot will turn up (0)
 */
int goRight(char maze[][N], int posX, int posY){
    if(maze[posY][posX+1] == 'Z'){
        maze[posY][posX+1] = 'B';
        maze[posY][posX] = 'x';
        return 4;
    }else if(maze[posY][posX+1] != '1'){
        maze[posY][posX+1] = 'B';
        maze[posY][posX] = 'x';
        return 3;
    }else
        return 0;
}

void printMaze(char maze[][N], int x, int y){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

int findBotX(const char maze[][N], int r, int c){
    int X = 0;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(maze[i][j] == 'B'){
                X = j;
                break;
            }
            if(X != 0)
                break;
        }
    }
    return X;
}

int findBotY(const char maze[][N], int r, int c){
    int y = 0;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(maze[i][j] == 'B'){
                y = i;
                break;
            }
            if(y != 0)
                break;
        }
    }
    return y;
}

int checkAround(char maze[][N], int c, int r, int pos){
    if(pos == 0){
        if(maze[r][c-1] != '1')
            pos = goLeft(maze, c, r);
        else if(maze[r][c+1] != '1')
            pos = goRight(maze, c, r);
        else
            return pos;
    }else if(pos == 1){
        if(maze[r+1][c] != '1')
            pos = goDown(maze, c, r);
        else if(maze[r-1][c] != '1')
            pos = goUp(maze, c, r);
        else
            return pos;
    }else if(pos == 2){
        if(maze[r][c+1] != '1')
            pos = goRight(maze, c, r);
        else if(maze[r][c-1] != '1')
            pos = goLeft(maze, c, r);
        else
            return pos;
    }else{
        if(maze[r-1][c] != '1')
            pos = goUp(maze, c, r);
        else if(maze[r+1][c] != '1')
            pos = goDown(maze, c, r);
        else
            return pos;
    }
}