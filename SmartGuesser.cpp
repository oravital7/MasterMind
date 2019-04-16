#include "SmartGuesser.hpp"
#include <iostream>

using namespace bullpgia;

string SmartGuesser::guess()
{
	if(lastGuess == "") {
		lastGuess = "1122";
	}
	else {
	int index = (rand() % combination.size());
	lastGuess = randomString(index);
	}
	return lastGuess;
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

string SmartGuesser::randomString(int index)
{
	auto it = combination.begin();
	for (int i = 0; i < index; i++)
	{
		it++;
	}
	return *it;
}

void SmartGuesser::startNewGame(uint length)
{
	lastGuess = "";
	this->length = length;
	initialize("");
}

void SmartGuesser::learn(string reply)
{
	for (auto it = combination.begin(); it != combination.end(); ++it)
	{
		if (calculateBullAndPgia(*it, lastGuess) != reply)
		{
			it = combination.erase(it);
		}
	}

}
