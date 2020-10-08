#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include<iostream>
#include<list>
#include<vector>
#include <map>
#include <string>
#include <iterator>
#include "Board.h"
class HumanPlayer{
public: 
    void play(int row, int col);
};
void HumanPlayer::play(int row, int col) {
	int x, y, n;
        int player = 1;
        bool validInputs = false;
        bool boardFull = false;
        Board board(row, col);
	do {    
                //asks user for their input
                cout << "Input your move with row and column numbers:" << endl;
                cin >> x >> y;
                
                //while the inputs are not valid keep asking for valid inputs
                validInputs = false;
                while(validInputs == false){
                    n = (x-1)*board.row+(y-1);
                    validInputs = board.validateMoves(x-1, y-1, n);
                    if(validInputs == false){
                        cout << "Please enter valid moves:" << endl;
                        cin >> x >> y;
                    }
                    n = (x-1)*board.row+(y-1);
                }
                
                //process who's move it is   
                player = player%2;
                if(player == 0){
                    player--;
                    cout << "PLAYER " << player << ":" << endl;
                    board.addMove(player, x-1, y-1, n);
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
        
        //displays who won after game complete
        if(boardFull){
            board.displayWinner();
        }
}



#endif /* HUMANPLAYER_H */

