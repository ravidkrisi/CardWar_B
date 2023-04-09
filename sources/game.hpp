#pragma once 
#include "player.hpp"    
#include "card.hpp"
namespace ariel {

    class Game
    {
    private:
    // define attributes 
        Player& player_1; // ref for first player
        Player& player_2; // ref for sec player 

        vector <Card> gameStack; //list of the game cards

        int player_1_winsCount; // count the wins of first player 
        int player_2_winsCount; // count the wins of sec player 
        int turnsCount; // count the number of turns
        int cardsPlayed; // count the number of cards played by both player (26 in total)
        int drawsCount; // count the number of draws per game 
        
        string turnInfo; // string to hold the information about the turn stats
        string gameLogInfo; // string to hole the information about the game stats

        bool gameStatus; // indicates when game starts and finished

        
    public:
        // declare constructor and deconstructor 
        Game(Player& plr_1, Player& plr_2);
        // decalare functions
        void createCardStack(); // generate game's cards stack 
        void shuffleCardStack(); // shuffle the game's cards stack 
        void splitCards(); // split evenly the game's cards stack between p1 and p2
        void playTurn(); 
        void printLastTurn(); // print the last turn stats
        void playAll(); // playes the game untill the end
        void printWiner(); // prints the name of the winning player
        void printLog(); // prints all the turns played one line per turn (same format as game.printLastTurn())
        void printStats(); // for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
    };
}
