#pragma once 
#include <string>
using namespace std;
namespace ariel {

    // define enums 
    enum CardSign{SPADES=1, HEARTS=2, CLUBS=3, DIAMONDS=4};
    enum CardValue{ACE=1, TWO=2, THREE=3, FOUR=4, 
                    FIVE=5, SIX=6, SEVEN=7, EIGHT=8, 
                    NINE=9, TEN=10, PRINCE=11, QUEEN=12, KING=13};
    class Card
    {
        private:
            CardSign sign; 
            CardValue value;

        public:
            // declare constructor and deconstructor
            Card(CardSign sign, CardValue value); // constructor
            // declare set get functions 
            // void setSign(int sign);
            // void setValue(int value);
            CardSign getCardSign() const; // return the sign of the card
            CardValue getCardValue() const; // return the value of the card
            int cardCompare(Card other); // this functions compare cards value 
            string toString() const; // toString method of card  
    };
}
