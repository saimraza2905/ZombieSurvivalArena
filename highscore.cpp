#include <fstream>
#include <iostream>
#include "highscore.h"
using namespace std;

int best[3] = {0, 0, 0};
bool newhighscore = false;

void loadscores(){
    ifstream file("highscores.txt");
    for(int i = 0; i < 3; i++){
        if(!(file >> best[i]))
           best[i] = 0;
    }
    file.close();
}

void savescore(int score){
    newhighscore = (score > best[0]);
    bool madelist = false;

    for(int i = 0; i < 3; i++){
        if(score > best[i]){
            for(int j = 2; j > i; j--)
               best[j] = best[j - 1];
            best[i] = score;
            madelist = true;
            break;
        }
    }
    if(madelist == false)
       return;

    ofstream file("highscores.txt");
    if(!file){
        cout << "Could not save highscores.txt" << endl;
        return;
    }
    for(int i = 0; i < 3; i++)
       file << best[i] << endl;
    file.close();
}