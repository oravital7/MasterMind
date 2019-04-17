#include "calculate.hpp"
#include <iostream>

using namespace std;

string bullpgia::calculateBullAndPgia(string choice, string guess)
{
    int bull=0, pgia=0;
    for(int i=0; i<choice.length(); i++) {
        if(choice[i] == guess[i]) {
            bull++;
        }
        else if(choice.find(guess[i])!=-1) {
            pgia++;
        }
    }
    return  to_string(bull)+","+to_string(pgia);
}

// int main() {
//     std::cout << bullpgia::calculateBullAndPgia("33","31") << endl;

//     return 0;
// }