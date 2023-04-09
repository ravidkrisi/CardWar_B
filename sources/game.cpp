#include "game.hpp"
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;
using namespace ariel;

// define constructor 
Game::Game (Player& plr_1, Player& plr_2): player_1(plr_1), player_2(plr_2), player_1_winsCount(0), player_2_winsCount(0), turnsCount(0), turnInfo(""), gameLogInfo(""), gameStatus(true), cardsPlayed(0), drawsCount(0)
{
    // check if the players are free to play else throw exception
    if(player_1.isPlaying())
    {
        throw invalid_argument("player1 is already in game \n");
    }
    if(player_2.isPlaying())
    {
        throw invalid_argument("player2 is already in game \n");
    }
    
    // set the players in game 
    player_1.setPlayerStatus(true);
    player_2.setPlayerStatus(true);

    // create game's cards stack 
    this->createCardStack();
    // shuffle game's cards stack 
    this->shuffleCardStack();
    // split cards between players
    this->splitCards();

}

// this function generate the game's cards stack 
void Game::createCardStack()
{
    this->gameStack.clear(); // make sure the stack is empty 

    for (int i=1; i<=13; i++) // all cards values 
    {
        for(int j=1; j<=4; j++) // all cards signs 
        {
            this->gameStack.push_back(Card(static_cast<CardSign>(j), static_cast<CardValue>(i))); // add each card to the game's stack  
        }
    }
}

// this function shuffles the game's cards stack
// https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector refrence and chatgpt 
void Game::shuffleCardStack()
{
    random_device rd;
    mt19937 g(rd());
    shuffle(this->gameStack.begin(), this->gameStack.end(), g);
}

// this function split evenly the game's cards stack 
void Game::splitCards()
{
    for(int i=0; i<26; i++)
    {
        this->player_1.addCard(this->gameStack.back()); // add the last card in the game's stack in p1 stack 
        this->gameStack.pop_back(); // remove the last card in the game's stack 

        this->player_2.addCard(this->gameStack.back()); // add the last card in the game's stack in p2 stack 
        this->gameStack.pop_back(); // remove the last card in the game's stack  
    }
}




//this function handles a turn in game 
void Game::playTurn()
{
    // check if both players has cards to play
    if(this->player_1.stacksize() == 0 || this->player_2.stacksize() == 0)
    {
        throw logic_error("cant play turn when game is over \n");
    }
    if(&this->player_1 == &this->player_2)
    {
        throw logic_error(" cant play game with the same person \n");
    }
    if(this->cardsPlayed<26) // a game can't be played more than 26 turns 
    {
        this->turnsCount++; // increament of the turn count 
        this->cardsPlayed++;    
        // clear last turn stats 
        // this->turnInfo = "turn "+to_string(this->turnsCount)+ ": ";
        this->turnInfo = "";

        // get players cards 
        Card player1_card = this->player_1.getCard();
        Card player2_card = this->player_2.getCard();

        // add info about the cards of the 2 players 
        this->turnInfo += player_1.getPlayerName() + " played " + player1_card.toString() + " " + player_2.getPlayerName() + " played " + player2_card.toString()+ ". ";
        
        int tieCount = 0;
        // case 1: a tie 
        while(player1_card.cardCompare(player2_card)==0) // a tie 
        {
            /*
            first we need to check both players has at least 2 cards to play tie 
            else we will take the remaining cards in for each player 
            */
           
           // increment tie count for each tie happend
           tieCount++;
            // increment draws count for each tie happend 
           this->drawsCount++;
           // add info about tie had happend
           this->turnInfo += " Draw. ";
           if(player_1.stacksize()== 0 && player_2.stacksize()==0) 
           {
                // increment players cards taken
                this->player_1.cardsTakenCountAdd();
                this->player_2.cardsTakenCountAdd();
                return;
           }
           else if(player_1.stacksize()== 1 && player_2.stacksize()==1) 
           {
                // player one increment and remove the left card from his stack 
                this->player_1.cardsTakenCountAdd();
                this->player_1.removeCard();
                this->player_1.cardsTakenCountAdd();
                // player two increment and remove the left card from his stack 
                this->player_2.cardsTakenCountAdd();
                this->player_2.removeCard();
                this->player_2.cardsTakenCountAdd();
                // break from while loop 
                return; 
           }
            // remove folded cards of both players hands
            this->player_1.removeCard();
            this->player_2.removeCard();
            // increment cardPlayed
            this->cardsPlayed++;

            // remove cards from both hands unfolded for a match 
            player1_card = this->player_1.getCard();
            player2_card = this->player_2.getCard();
            // increment cardPlayed
            this->cardsPlayed++;

            // add info about the cards of the 2 players 
            this->turnInfo += player_1.getPlayerName() + " played " + player1_card.toString() + " " + player_2.getPlayerName() + " played " + player2_card.toString()+ ". ";

            // if one of the players win the tie round 
            if(player1_card.cardCompare(player2_card) == 1|| player1_card.cardCompare(player2_card) == -1)
            {
                // break from the while loop 
                break;
            }
            // else there is a tie again and it will enter the while loop again
        }

        // case2: player1 wins 
        if(player1_card.cardCompare(player2_card)==1)
        {
            // add 4*tieCount to cardsTakenCount for each tie win
            for (int i=0; i<tieCount*4;i++)
            {
                this->player_2.cardsTakenCountAdd();
            }
            // add 2 cards to p1 cards taken count 
            this->player_1.cardsTakenCountAdd();
            this->player_1.cardsTakenCountAdd();
            //increment player1 wins
            this->player_1_winsCount++;
            // add info about the winner in the turn 
            this->turnInfo+= this->player_1.getPlayerName()+ " wins.";
        }
        // case3: player2 wins
        if(player1_card.cardCompare(player2_card)==-1)
        {
            // add 4*tieCount to cardsTakenCount for each tie win
            for (int i=0; i<tieCount*4;i++)
            {
                this->player_2.cardsTakenCountAdd();
            }
            // add 2 cards to p1 cards taken count 
            this->player_2.cardsTakenCountAdd();
            this->player_2.cardsTakenCountAdd();
            //increment player1 wins
            this->player_2_winsCount++;
            // add info about the winner in the turn 
            this->turnInfo+= this->player_2.getPlayerName() + " wins.";
        }
        // add turn info to game log info 
        this->turnInfo += "p1 count: " + to_string(this->player_1.stacksize()) + "  p2 count: " + to_string(this->player_2.stacksize())+"\n";
        this->gameLogInfo+= this->turnInfo + " \n"; 
    }

    
}
void Game::printLastTurn()
{
    cout << "\n" << this->turnInfo;
}
// function that play the whole turns till game is finished 
void Game::playAll()
{
    while (this->player_1.stacksize()>0&& this->player_2.stacksize()>0)
    {
        this->playTurn();
    }
}
// this function print the game winner
void Game::printWiner()
{
    string winnerName;
    if(player_1.getCardsTakenCount() == player_2.getCardsTakenCount())
    {
        cout << "the game ended up a tie";
    }
    // player1 wins
    if(this->player_1.getCardsTakenCount()>this->player_2.getCardsTakenCount())
    {
        winnerName = player_1.getPlayerName();
    }
    // player2 wins
    else if(this->player_1.getCardsTakenCount()<this->player_2.getCardsTakenCount())
    {
        winnerName = player_2.getPlayerName();
    }

    cout << "the winner is: " + winnerName + " \n";

}
void Game::printLog()
{
    cout << this->gameLogInfo;
}
void Game::printStats()
{
    cout << "\n******stats******\n\n";
    // player 1 stats 
    cout << this->player_1.getPlayerName() << ":\n"; // player name 
    cout << "win rate: " << this->player_1_winsCount << "\n"; // win count 
    cout << "cards won: " << this->player_1.getCardsTakenCount() << "\n\n"; // cards won
    // player 2 stats 
    cout << this->player_2.getPlayerName() << ":\n"; // player name
    cout << "win rate: " << this->player_2_winsCount << "\n"; // win count
    cout << "cards won: " << this->player_2.getCardsTakenCount() << "\n\n"; // cards won
    
    
    cout << "draws count: " << this->drawsCount << " \n";
    cout << "draws rate: " << ((double)this->drawsCount/this->turnsCount)*100 << "%\n";
    cout << this->drawsCount << "\n";
    cout << this->turnsCount << "\n";

}



