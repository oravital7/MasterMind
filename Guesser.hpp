#pragma once
#include <string>

using namespace std;

namespace bullpgia
{

class Guesser
{
    protected:
    uint length;
    string lastReply;

    public:
    
    virtual string guess() = 0;
    void startNewGame(uint length){
        this->length = length;
    }
    void learn(string reply){
        lastReply = reply;
    }
};

} // namespace bullpgia