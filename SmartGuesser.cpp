#include "SmartGuesser.hpp"
#include <iostream>

using namespace bullpgia;

string SmartGuesser::guess()
{
	if (lastGuess == "")
	{
		lastGuess = "1122";
	}
	else
	{
		int index = rand() % combination.size();
		auto it = combination.begin();
		for(int i = 0; i < index; i++) {
			it++;
		}
	//	lastGuess = miniMax();
		lastGuess = *it;
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

void SmartGuesser::startNewGame(uint length)
{
	lastGuess = "";
	this->length = length;
	combination.clear();
	initialize("");
}

void SmartGuesser::learn(string reply)
{
	for (auto it = combination.begin(); it != combination.end(); ++it)
	{
		if (calculateBullAndPgia(*it, lastGuess).compare(reply) != 0)
		{
			  it = combination.erase(it);
			  it--;
		}
	}

}

string SmartGuesser::miniMax()
{
	map<string, int> scoreCount;
	map<string, int> score;

	string key;

	for (auto i = combination.begin(); i != combination.end(); ++i)
	{
				//cout <<"i: " <<  *i<< endl;

		for (auto j = combination.begin(); j != combination.end(); ++j)
		{
			key = calculateBullAndPgia(*j, *i);
			if (scoreCount.count(key) > 0)
			{
				scoreCount.at(key)++;
			}
			else
			{
				scoreCount.emplace(key, 1);
			}
		}

		int max = getMax(scoreCount);
		scoreCount.clear();
		score.emplace(*i, max);
	}
	string result = getMin(score);
	combination.remove(result);

	return result;
}

int SmartGuesser::getMax(map<string, int> &scoreCount)
{
	int max = 0;
	for (auto it : scoreCount)
	{
		if (it.second > max)
			max = it.second;
	}
	return max;
}

string SmartGuesser::getMin(map<string, int> &score)
{
	int min = std::numeric_limits<int>::max();
	string str;
	for (auto it : score)
	{
		if (it.second < min)
		{
			min = it.second;
			str = it.first;
		}
		return str;
	}

}