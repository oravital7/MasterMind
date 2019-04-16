#pragma once
#include <string>

using namespace std;

namespace bullpgia
{

class Guesser
{
protected:
  uint length;

public:
  virtual string guess() = 0;
  virtual void startNewGame(uint length)
  {
    this->length = length;
  }
  virtual void learn(string reply) {};
};

} // namespace bullpgia