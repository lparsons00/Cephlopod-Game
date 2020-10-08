#ifndef SMARTPLAYER_H
#define SMARTPLAYER_H


#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include "Board.h"

class SmartPlayer{
public: 
    void play(int row, int col, bool humanPlayer);
    int randomInput(int max);
};
//random number generator
int SmartPlayer::randomInput(int max){
    int n = -10;
    n = rand()%max;
    return n;
}



void SmartPlayer::play(int row, int col, bool humanPlayer){
	int x, y, tempN, max, highestPips;
        int n = -1;
        int player = 1;
        int tempcounter;
        bool validInputs = false;
        bool boardFull = false;
        srand(time(0));
        
        
        //creates object to play game on
        Board board(row, col);
        board.printBoard(row, col);
        
	do { 
            max = row*col;
            //tempcounter allows us to temporarily hold the highest pip value
            //allowing us to find the best position for the algorithm
            //tempcounter = -1;    
            
            //searches through all values to see highest combination possible
            highestPips = 0;
            for(int i = 1; i <= max; i++){
                bool smart = true;
                tempcounter = board.checkNeighbours(i, smart);
                if(tempcounter >= highestPips){
                    highestPips = tempcounter;         
                    //n is given the value of the highest pip
                    validInputs = false;
                    tempN = -1;
                    n = i; 
                    x = (n/row)+1;
                    y = (n%col)+1;
                    //checking if n is a valid input
                    validInputs = board.validateMoves( x, y, n);
                    if(validInputs == false){
                        tempcounter = 0;
                        n = tempN;
                    }
                } 
            }   
            
           
            //if the board is empty, simply place a random move
            if( n == -1){
                validInputs = false;
                while(validInputs == false){
                    n = randomInput(max);
                    x = (n/row)+1;
                    y = (n%col)+1;
                    validInputs = board.validateMoves( x, y, n);
                }
            }
            
            //process who's move it is   
            //player 1; smart moves
            player = player%2;
            if(player == 0){
                player--;
                cout << "PLAYER " << player << ":" << endl;
                validInputs = false;
                //call random move function if vs a random
                if(humanPlayer == false){    
                    while(validInputs == false){
                        n = randomInput(max);
                        x = (n/row)+1;
                        y = (n%row)+1;
                        validInputs = board.validateMoves(x, y, n);
                    }
                board.addMove(player, x-1, y-1, n);
                //otherwise allow human input
                } else if (humanPlayer == true){
                    while(validInputs == false ){
                        cout << "Please enter valid moves:" << endl;
                        cin >> x >> y;
                        n=(x-1)*board.row+(y-1);
                        validInputs = board.validateMoves(x-1, y-1, n);
                    }
                    board.addMove(player, x-1, y-1, n);
                }
                player++;
            } else {
                cout << "PLAYER " << player << ":" << endl;
                board.addMove(player, x-1, y-1, n);
            }
            
            player++;
                
            
            //prints game board
            cout << "Game board:" << endl;  
            board.printBoard(x, y);
                
            
        //check if board is full
            boardFull = board.boardStatus();
	} while (boardFull == false);
        
        //prints to console the winner
        if(boardFull){
            board.displayWinner();
        }
}


#endif /* SMARTPLAYER_H */

