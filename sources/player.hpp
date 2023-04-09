#pragma once 

#include <string>
#include <vector>
#include "card.hpp"

using namespace std;

namespace ariel
{
    class Player 
    {
        private:
            // define attributes 
            string name; //Player's name 
            vector <Card> cardStack; // Player's stack of cards
            int cardsTakenCount; // player's stack of cards taken count 
            bool isPlayerPlaying; // boolean indicates if player in game 
        
        public:
            // decalare constructor deconstructor 
            Player(); // defaltive constructor 
            Player(string name); 
            // declare functions  
            int stacksize() const; // this method returns the amount of cards left
            int cardesTaken(); // this method print the amount of cards the Player has won
            // declare getters and setters
            bool isPlaying() const; // getter return isPlayerPlaying status
            void setPlayerStatus(bool status); // set Player isPlayerPlaying status
            void addCard(Card newCard); // add the players cardStack a card
            Card getCard(); // return card from player's cards stack 
            void removeCard(); // remove card from player's cards stack  
            void cardsTakenCountAdd(); // increment the cardsTakenCount
            string getPlayerName() const; // return player name
            int getCardsTakenCount() const; // return players cards taken count 
    };
}

