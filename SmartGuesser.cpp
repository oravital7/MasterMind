#include "SmartGuesser.hpp"
#include <iostream>
using namespace bullpgia;

string SmartGuesser::guess()
{

	if (length < 6)
	{
		if (lastGuess == "")
		{
			lastGuess = firstGuess();
		}
		else
		{
			int index = rand() % combination.size();

			auto it = combination.begin();
			for (int i = 0; i < index; i++)
			{
				it++;
			}
			//  lastGuess = miniMax();
			lastGuess = *it;
		}
	}
	else if (currentNum < 10)
	{
		//finds the digits
		lastGuess = nextGuess();
	}
	cout << "LastGuess: " << lastGuess << endl;
	return lastGuess;
}

string SmartGuesser::firstGuess()
{
	string str = "1";
	if (length == 1)
		return str;

	for (int i = 0; i < length - 2; i++)
	{
		str += "1";
	}

	return str + "2";
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
	if (length < 6)
	{
		combination.clear();
		initialize("");
	}
	else
	{
		currentNum = 0;
		std::fill(numbers, numbers + 10, 0);
		unChosenNum = '\0';
		hasFound = true;
		isIntialized = false;
	}
}

void SmartGuesser::learn(string reply)
{
	if (length < 6)
		learnShort(reply);
	else
	{
		learnLong(reply);
	}
}

void SmartGuesser::learnShort(string reply)
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

//great length: 6-9

void SmartGuesser::learnLong(string reply)
{
	if (currentNum < 10)
	{
		numbers[currentNum] = reply[0] - '0';
		if (sumNubers())
		{
			currentNum = 10;
			InitLong();
		}
		else
			currentNum++;
	}
	else if (!isIntialized)
	{
		InitLong();
	}
	else
	{
		findPosition(reply);
	}
}

string SmartGuesser::nextGuess()
{
	string nGuess = "";
	for (size_t i = 0; i < length; i++)
	{
		nGuess += to_string(currentNum);
	}
	return nGuess;
}
char SmartGuesser::notInNum()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (numbers[i] == 0)
			break;
	}
	return i + '0';
}

void SmartGuesser::findPosition(string reply)
{
	// if the right position was found
	if (reply[0] == '1')
	{
		updateChar();
		hasFound = true;
		currentChar = findNextChar();
		if (hasFound)
		{
			string st(rs.begin(), rs.end());
			lastGuess = st;
		}
		else
		{
			int post = lastPosition();
			lastGuess = stringMaker(currentChar, post);

			if (post || rs[0] != unChosenNum)
				placement();
		}
	}

	else
	{
		placement();
	}
}

void SmartGuesser::updateChar()
{
	for (int i = 0; i < length; i++)
	{
		if (lastGuess[i] != unChosenNum)
		{
			rs[i] = lastGuess[i];
			break;
		}
	}
}

int SmartGuesser::findNextChar()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (numbers[i] > 0)
		{
			hasFound = false;
			numbers[i]--;
			break;
		}
	}
	return i + '0';
}

string SmartGuesser::stringMaker(char c, int position)
{
	string str = "";
	for (int i = 0; i < length; i++)
	{
		if (i == position)
			str += c;
		else
		{
			str += unChosenNum;
		}
	}
	return str;
}

void SmartGuesser::placement()
{
	bool found = false;
	for (int i = 0; i < lastGuess.length() - 1 && !found; i++)
	{
		if (lastGuess[i] == currentChar)
		{

			for (int j = i + 1; j < lastGuess.length() && !found; j++)
			{
				if (rs[j] == unChosenNum)
				{
					lastGuess[i] = unChosenNum;
					lastGuess[j] = currentChar;
					found = true;
				}
			}
		}
	}
}

bool SmartGuesser::sumNubers()
{
	int sum = 0;
	for (int i : numbers)
	{
		sum += i;
	}
	return sum == length;
}

int SmartGuesser::lastPosition()
{
	for (int i = rs.size() - 1; i >= 0; i--)
	{
		if (rs[i] == currentChar)
		{
			return i;
		}
	}
	return 0;
}

void SmartGuesser::InitLong()
{
	unChosenNum = notInNum();
	rs.assign(length, unChosenNum);

	isIntialized = true;
	currentChar = findNextChar();
	lastGuess = stringMaker(currentChar, 0); //creating the first string
}