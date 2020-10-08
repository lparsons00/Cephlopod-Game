
#include<iostream>
#include<time.h>

#include "decider.h"
//#include "HumanPlayer.h"

using namespace std;

int main()
{
        int gameMode = -10;
        int row, col = -10;

        //welcome message
	cout <<"Welcome to Cephalopod Game" << endl;
        cout <<"Created BY LUKE PARSONS - 19336086" << endl; 
       
        //options for game type
        cout << "Please Select Game-Mode:\n"
             << "1. Human VS Human\n"
             << "2. Random VS Random\n"
             << "3. Smart VS Random\n"
             << "4. Smart VS Human\n"
             << "5. Random VS Human\n\n";
        while((gameMode < 0) || gameMode > 5){
            cout << "Input Game-Mode Number:" << endl;
            cin >> gameMode;
        }
        //input size of board
        while((row <= 1) || (col <= 0)){
            cout <<"Input the size of board: " << endl;
            cin >> row >> col;
        }

        
        //creates new decider object to decide what gamemode is active
        decider decider;
	decider.decide(gameMode, row, col);

	return 0;
}
