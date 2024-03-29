#pragma once
#include <string>

namespace bullpgia
{

class Chooser
{
    public:
    virtual std::string choose(uint length) = 0;
};

} // namespace bullpgia