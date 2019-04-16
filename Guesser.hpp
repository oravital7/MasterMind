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

    int test = 0;

  public:
    virtual string guess() = 0;
    void startNewGame(uint length)
    {
        this->length = length;
        lastReply = "";
        test = 0;
    }
    void learn(string reply)
    {
        lastReply = reply;
    }
};

} // namespace bullpgia