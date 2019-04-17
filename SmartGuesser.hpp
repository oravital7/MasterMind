#pragma once
#include "Guesser.hpp"
#include "calculate.hpp"

#include <list> 
#include <iterator> 
#include <map>

namespace bullpgia
{

class SmartGuesser : public Guesser
{
    list<string> combination;

    string lastGuess,lastReply;

    string guess() override;
    void startNewGame(uint length) override;
    void learn(string reply) override;



    void initialize(string result);
    string miniMax();
    int getMax(map<string, int> &scoreCount);
    string getMin(map<string, int> &score);


};


} // namespace bullpgia