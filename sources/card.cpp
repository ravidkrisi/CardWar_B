// #pragma once 

#include "card.hpp"
#include <iostream>

using namespace std;
using namespace ariel;

//define constructor 
Card::Card(CardSign cardSign, CardValue cardValue): sign(cardSign), value(cardValue){}
// define getters 

// return the value of the card
CardValue Card::getCardValue() const
{
    return this->value;
}

// return the sign of the card
CardSign Card::getCardSign() const
{
    return this->sign;
}

// this function compare two cards and return 1 if this card is bigger 0 if both even -1 if other card is bigger
int Card::cardCompare(Card other)
{
    if(this->getCardValue()==other.getCardValue()) return 0; // both cards equel 
    if(this->getCardValue() == 1 && other.getCardValue() != 2) return 1; // p1 has ace and beats every value except 2
    if(this->getCardValue() != 2 && other.getCardValue() == 1) return -1; // p2 has ace and beats every value except 2
    if(this->getCardValue()>other.getCardValue()) return 1; // this card is bigger 
    return -1; // other card is bigger  
}

// toString method of card
string Card::toString() const
{
    string cardSignString;
    string cardValueString;

    // set cardSign
    switch (this->sign)
    {
    case CardSign::CLUBS:
        cardSignString = "Clubs";
        break;
    case CardSign::DIAMONDS:
        cardSignString = "Diamonds";
        break;
    case CardSign::HEARTS:
        cardSignString = "Hearts";
        break;
    case CardSign::SPADES:
        cardSignString = "Spades";
        break;
    }
    
    // set cardValue 
    switch (this->value)
    {
    case CardValue::ACE:
        cardValueString = "Ace";
        break;
    case CardValue::TWO:
        cardValueString = "2";
        break;
    case CardValue::THREE:
        cardValueString = "3";
        break;
    case CardValue::FOUR:
        cardValueString = "4";
        break;
    case CardValue::FIVE:
        cardValueString = "5";
        break;
    case CardValue::SIX:
        cardValueString = "6";
        break;
    case CardValue::SEVEN:
        cardValueString = "7";
        break;
    case CardValue::EIGHT:
        cardValueString = "8";
        break;
    case CardValue::NINE:
        cardValueString = "9";
        break;
    case CardValue::TEN:
        cardValueString = "10";
        break;
    case CardValue::PRINCE:
        cardValueString = "Prince";
        break;
    case CardValue::QUEEN:
        cardValueString = "Queen";
        break;
    case CardValue::KING:
        cardValueString = "King";
        break;
    }

    return cardValueString + " of " + cardSignString; // return the card as string
}

