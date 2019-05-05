#pragma once
#include "Guesser.hpp"
#include "calculate.hpp"

#include <list> 
#include <vector>
#include <iterator> 

namespace bullpgia
{

class SmartGuesser : public Guesser
{
    list<string> combination;
    int numbers[10],currentNum;
    char unChosenNum,currentChar;
    bool hasFound,isIntialized;
    string lastGuess,lastReply;
    vector<char> rs;
    
    string guess() override;
    void startNewGame(uint length) override;
    void learn(string reply) override;
    
    //short length
    void initialize(string result);
    string firstGuess();
    void learnShort(string reply);

    //great length
    void learnLong(string reply);
    char notInNum();
    string nextGuess();
    void findPosition(string reply);
    void updateChar();
    int findNextChar();
    string stringMaker(char c, int position);
    void placement();
    bool sumNubers();
    int lastPosition();
    void InitLong();

};


} // namespace bullpgia