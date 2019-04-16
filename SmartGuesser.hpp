#pragma once
#include "Guesser.hpp"
#include "calculate.hpp"

#include <list> 
#include <iterator> 

namespace bullpgia
{

class SmartGuesser : public Guesser
{
    list<string> combination = {};
    //list<string> :: iterator it;
    string lastGuess,lastReply;

    string guess() override;
    void startNewGame(uint length) override;
    void learn(string reply) override;



    void initialize(string result );
    void removeCombination();
    string randomString(int index);

};


} // namespace bullpgia