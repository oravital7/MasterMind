#include "calculate.hpp"

using namespace std;

string bullpgia::calculateBullAndPgia(string choice, string guess)
{
    int bull = 0, pgia = 0;

    for(int i=0; i<guess.length(); i++) {
        if(choice[i] == guess[i]) {
            bull++;
            guess[i] = choice[i] = '\0';
        }
    }

    for(int i=0; i<guess.length(); i++) {
        if(guess[i] && choice.find(guess[i])!=-1) {
            pgia++;
            choice[choice.find(guess[i])] = '\0';
        }
    }
    return to_string(bull) + "," + to_string(pgia);
}
