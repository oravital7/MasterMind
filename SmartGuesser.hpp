#pragma once
#include "Guesser.hpp"

namespace bullpgia
{

class SmartGuesser : public Guesser
{

    virtual string guess() override;
    virtual void startNewGame(uint length) override;
    virtual void learn(string reply) override;
};

} // namespace bullpgia