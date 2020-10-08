#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include "Board.h"

class RandomPlayer{
public: 
    void play(int row, int col, bool humanPlayer);
    int randomInput(int max);
};
//basic random number generator
int RandomPlayer::randomInput(int max){
    int n = -10;
    n = rand()%max;
    return n;
}

void RandomPlayer::play(int row, int col, bool humanPlayer){
	int x, y, n;
        int max;
        int player = 1;
        bool validInputs = false;
        bool boardFull = false;
        
        //create board object to play game on
        Board board(row, col);
        
	do {
                srand(time(0));
                //gets a random input
                cout << "Random Input:" << endl;
                max = row*col;
                validInputs = false;
                while(validInputs == false){
                    n = randomInput(max);
                    //change n value into x and y values
                    x = (n/row)+1;
                    y = (n%row)+1;
                    //check if move is empty
                    validInputs = board.validateMoves(x, y, n);
                    if(validInputs == false){
                        if(n!= max){
                            n = n+1;
                        } else { n = 0; }
                        validInputs = board.validateMoves(x, y, n);
                    }
                }

                //process who's move it is   
                player = player%2;
                if(player == 0){
                    player--;
                    cout << "PLAYER " << player << ":" << endl;
                    board.addMove(player, x-1, y-1, n);
                    player++;
                } else {
                    //if selected for human player (instead of two random)
                    //change selection to input by player
                    cout << "PLAYER " << player << ":" << endl;
                    if(humanPlayer == true){
                        validInputs = false;
                        while(validInputs == false){
                            cout << "Please enter valid moves: " << endl;
                            cin >> x >> y;
                            n =(x-1)*board.row+(y-1);
                            validInputs = board.validateMoves(x-1, y-1, n);
                        }
                        
                    }
                    board.addMove(player, x-1, y-1, n); 
                }
                player++;
                
                //prints game board
		cout << "Game board:" << endl;
                board.printBoard(x, y);
                
        //check if board is full
                boardFull = board.boardStatus();
	} while (boardFull == false);
        //displays winner when game finished
        if(boardFull){
            board.displayWinner();
        }
}


#endif /* RANDOMPLAYER_H */

