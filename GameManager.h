#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <queue>
using namespace std;

class GameManager
{
    private:
        const int MAX_TRIES;
        string word;
        string player1_name;
        string player2_name;

    private:
        int letterFill (char, string&);
        void updateHighScores(int current_score, string pname);

    public:
        GameManager();
        void getPlayer1Name();
        void getPlayer2Name();
        void showRules();
        void startAIGame();
        void showTitle();
        void showHighScores();
        void startMultiPlayer();
};

#endif
