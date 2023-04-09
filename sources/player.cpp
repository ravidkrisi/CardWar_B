#include "player.hpp"

using namespace ariel;
// define constructors
Player::Player(): name("anon"), cardsTakenCount(0), isPlayerPlaying(false){} // defaultive constructor 

Player::Player(string playerName): name(playerName), cardsTakenCount(0), isPlayerPlaying(false){}

// return player's stack size
int Player::stacksize() const
{
    return this->cardStack.size();
}

int Player::cardesTaken()
{
    return this->cardsTakenCount;
}


// getter return isPlayerPlaying status
bool Player::isPlaying() const
{
    return this->isPlayerPlaying;
}

// set Player isPlayerPlaying status
void Player::setPlayerStatus(bool status)
{
    this->isPlayerPlaying=status;
}

// add card to player's cardStack 
void Player::addCard(Card newCard)
{
    this->cardStack.push_back(newCard);
}

// return last card from player's cards stack 
Card Player::getCard()
{
    Card c = this->cardStack.back();
    this->cardStack.pop_back();
    return c;
}

// removes card from player cards stack 
void Player::removeCard()
{
    this->cardStack.pop_back();
}

// increment the CardsTakenCount
void Player::cardsTakenCountAdd()
{
    this->cardsTakenCount++;
}

// return playerName 
string Player::getPlayerName() const
{
    return this->name;
}


// return players cards taken count 
int Player::getCardsTakenCount() const
{
    return this->cardsTakenCount;
}



