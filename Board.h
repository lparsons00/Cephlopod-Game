#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <iterator>


using namespace std;

class Board {
private:
	int **grid; // 1 = black; -1 = white; 0 = empty
        list<int> left;
        int counter = 1;
        vector<int> pipValues;
        vector<int> combination;
public:
        int pipCount = 0;
        map<int, int> pips;
        int row, col;
	Board(int r, int c) {
		row = r;
		col = c;
                //creates a new row for each col (2d array)
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];
               
                //populates the entire array with the value of 0
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				grid[i][j] = 0;

                //for the size of the 2d array push a integer value to the list named left
		for (int i = 0; i < row*col; i++) {
			left.push_back(i);
                        pips.insert(pair<int, int> (i,0));
		}
	}
        
        //de-constructor
	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}

        bool validateMoves(int x, int y, int n);
	bool addMove(int player, int x, int y, int n);
	int checkNeighbours(int n, bool smart);
	void printBoard(int x, int y);
	void play(int gameMode);
        bool boardStatus();
        void emptyNeighbours(int n, bool up, bool down, bool left, bool right);
        void displayWinner();
};

//check the surrounding pip values of a square
//also used to check if a square is empty
int Board::checkNeighbours(int n, bool smart) { 
    //var used to hold a temporary value when checking for pip values
    int tempPip;
    //var used to count the directions surrounding a square
    int directionCounter = 0;
    //direction variables
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool called = false;
    
    pipCount = 0;
    //first section: finds the number of directions surrounding a square
    //and also gathers a squares pip value
        //north
        if(n <= row-1){} else{
            tempPip = n - row;
            if(pips[tempPip] != 0){
                pipCount = pipCount + abs(pips[tempPip]);
                up = true;
                directionCounter++;
            }
        }
        //south
        if(n  >= (row*col)-col+1){} else {
            tempPip = n+row;
            if(pips[tempPip] != 0){
                pipCount = pipCount + abs(pips[tempPip]);
                down = true;
                directionCounter++;
            }
        }
        //west
        if(n%row == 0){} else {
            tempPip = n-1;
            if(pips[tempPip] != 0){
                pipCount = pipCount + abs(pips[tempPip]);
                left = true;
                directionCounter++;
            }
        }
        //east
        if(n%row == (row-1)){} else {
            tempPip = n+1;
            if(pips[tempPip] != 0){
                pipCount = pipCount + abs(pips[tempPip]);
                right = true;
                directionCounter++;
            }
        }

    
    
    //second section: processes the above info
    //if a pipcount is low enough and has enough surrounding squares,
    //we will call emptyNeighbours function
    //smart bool allows us to check without acting on the results (used in smart)
    if((pipCount <= 6) && (directionCounter >= 2)){
        if(smart == false){
            emptyNeighbours(n, up, down, left, right);
        }
        return pipCount;
    } else if((pipCount > 6) && (directionCounter >=3)){
        //remove one side when adding total pipCount 
        //allows us to check all combinations of pips (if possible)
        if (down == true){
            pipCount = pipCount - abs(pips[n+row]);
            if(pipCount <= 6){
                down = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n+row]);
            }
        } 
        if ((up == true) && (called == false)){
            pipCount = pipCount - abs(pips[n-row]);
            if(pipCount <= 6){
                up = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n-row]);
            }    
        } 
        if ((left == true) && (called == false)){
            pipCount = pipCount - abs(pips[n-1]);
            if(pipCount <= 6){
                left = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n-1]);
            }    
        } 
        if ((right == true)&&(called == false)){
            pipCount = pipCount - abs(pips[n+1]);
            if(pipCount <= 6){
                right = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n+1]);
            }    
        }
        if(called == true){
            return pipCount;
        }
    } 
    
    //third section: if a square is completely surrounded, run through all combinations
    if((pipCount > 6) && (directionCounter == 4)) {
        if(called == false){
            //remove up and right
            pipCount = pipCount - abs(pips[n-row]) - abs(pips[n+1]);
            if(pipCount <= 6){
                up = false;
                right = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n-row]) + abs(pips[n+1]);
            }
        } 
        if(called == false){
            //remove up and left
            pipCount = pipCount - abs(pips[n-row]) - abs(pips[n-1]);
            if(pipCount <= 6){
                up = false;
                left = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n-row]) + abs(pips[n-1]);
            }
        }  
        if(called == false){
            //remove up and down
            pipCount = pipCount - abs(pips[n-row]) - abs(pips[n+row]);
            if(pipCount <= 6){
                up = false;
                down = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n-row]) + abs(pips[n+row]);
            }
        } 
        if(called == false){
            //remove right and left
            pipCount = pipCount - abs(pips[n-1]) - abs(pips[n+1]);
            if(pipCount <= 6){
                right = false;
                left = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n-1]) + abs(pips[n+1]);
            }
        }  
        if(called == false){
            //remove right and down
            pipCount = pipCount - abs(pips[n+1]) - abs(pips[n+row]);
            if(pipCount <= 6){
                right = false;
                down = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n+1]) + abs(pips[n+row]);
            }
        }    
        if(called == false){
            //remove down and left
            pipCount = pipCount - abs(pips[n+row]) - abs(pips[n-1]);
            if(pipCount <= 6){
                down = false;
                left = false;
                if(smart == false){
                    emptyNeighbours(n, up, down, left, right);
                    called = true;
                }
            } else {
                pipCount = pipCount + abs(pips[n+row]) + abs(pips[n-1]);
            } 
        }
        
    } 
   
    //if no changes could be made
    if((called == false) &&(smart == false)){
        directionCounter = 0;
        return 0;
    //if changes were made
    }else if(called == true){
        return pipCount;
    //if no changes were made, but they were possible (used in smart choice)
    }else if((called == false) && (smart == true)){
        return pipCount;
    }
    
}

//remove neighbours around a collecting pip
void Board::emptyNeighbours(int n, bool up, bool down, bool left, bool right){
    int tempPips, x, y;
    //change n value to coordinates
    x = n/row;
    y = n%row;

    //north
    if(up == true){
        tempPips = n - row;
        pips[tempPips] = 0;
    } 
    //south
    if(down == true){
        tempPips = n + row;
        pips[tempPips] = 0;
    }
    //west
    if(left == true){
        tempPips = n-1;
        pips[tempPips] = 0;
    }
    //east
    if(right == true){
        tempPips = n+1;
        pips[tempPips] = 0;
    }
}

//add moves to the board
bool Board::addMove(int player, int x, int y, int n) {
        int pipsSurround;
        bool smart = false;   
        pipsSurround = checkNeighbours(n, smart);
   
        //allows to display the players symbol and pip score of a square
        if(pipsSurround == 0) {
            pipsSurround = player;
        } else {
            pipsSurround = pipsSurround * player;
        }
        
        grid[x][y] = pipsSurround;
        pips[n] = grid[x][y];
	return true;
}

//simple validator of moves
bool Board::validateMoves(int x, int y, int n){
    bool internalValidator = true;
    //within row limit
    if(x > row){
        internalValidator = false;
    //within col limit 
    } else if ( y > col){
        internalValidator = false;
    //on an empty square
    } else if ( pips[n] != 0){
        internalValidator = false;
    }
    return internalValidator;
}

//checks if board is empty
bool Board::boardStatus(){
    bool boardStat = true;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int n = (i)*row+(j);
            if(pips[n] == 0){
                boardStat = false;
            }
        }
    }
    return boardStat;
    
}

//print the entire board
void Board::printBoard(int x, int y) {
        //converts x and y into n to allow use of the map
        int n = ((x-1)*row)+(y-1);
    
	cout << "    ";
        //top row of numbers
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

        
	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
                    n = ((i)*row)+(j);
			if (pips[n] == 0) {
				cout << "   |";
			} else if (pips[n] > 0) {
				cout << " " <<pips[n] << " |";
			} else if (pips[n] < 0) {
				cout << "" << pips[n] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

//print the winner of the game
void Board::displayWinner(){
    int player1 = 0;
    int player2 = 0;
    //compares scores and displays winner
    for(int i = 0; i < row*col; i++){
        if(pips[i] > 0){
            player1 = player1 + abs(pips[i]);
        } else if (pips[i] < 0){
            player2 = player2 + abs(pips[i]);
        }
    }
    if(player1 > player2){
       cout << "PLAYER 1 is the winner!\n"; 
    } else {
        cout << "PLAYER 2 is the winner!\n";
    }
    cout << "FINAL SCORE: \n PLAYER 1: " << player1 << "\n PLAYER 2: " << player2 << endl; 
}
#endif /* BOARD_H_ */