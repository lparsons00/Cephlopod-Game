#ifndef DECIDER_H
#define DECIDER_H
#include<iostream>
#include<list>
#include<vector>
#include <map>
#include <string>
#include <iterator>
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "SmartPlayer.h"

class decider{
public: 
    void decide(int gameMode, int row, int col);
    bool humanPlayer = false;
};
void decider::decide(int gameMode, int row, int col){
    if(gameMode == 1){
        HumanPlayer humanplayer;
        humanplayer.play(row, col);
    } else if (gameMode == 2){
        RandomPlayer randomplayer;
        randomplayer.play(row, col, humanPlayer);
    } else if (gameMode == 3){ 
        SmartPlayer smartplayer;
        smartplayer.play(row, col, humanPlayer);
    } else if (gameMode == 4){
        SmartPlayer smartplayer;
        humanPlayer = true;
        smartplayer.play(row, col, humanPlayer);
    } else if (gameMode == 5){
        RandomPlayer randomplayer;
        humanPlayer = true;
        randomplayer.play(row, col, humanPlayer);
    }
}




#endif /* DECIDER_H */

