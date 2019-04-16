#include "SmartGuesser.hpp"
#include <iostream>

using namespace bullpgia;

string SmartGuesser::guess()
{
	if (lastReply == "")
	{
		combination.clear();
		initialize("");
		lastGuess = "1122";
		return lastGuess;
	}

	else
	{
		removeCombination();
		int index =  (rand()% combination.size());
		lastGuess = combination[index];
		return combination[index];

	}
}

void SmartGuesser::initialize(string result)
{
	if (result.length() == length)
	{
		combination.push_back(result);
		return;
	}

	for (int i = 0; i <= 9; i++)
	{
		initialize(result + to_string(i));
	}
}

void SmartGuesser::removeCombination()
{
	for (int i = 0; i < combination.size(); i++)
	{
		if (calculateBullAndPgia(combination[i], lastGuess) != lastReply)
		{
			combination.erase(combination.begin() + i);
		}
	}
}
