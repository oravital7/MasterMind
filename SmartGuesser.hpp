#pragma once
#include "Guesser.hpp"
#include <vector> 
#include "calculate.hpp"

namespace bullpgia
{

class SmartGuesser : public Guesser
{
    vector<string> combination;
    string lastGuess;

    string guess() override;
    void initialize(string result );
    void removeCombination();

};


} // namespace bullpgia