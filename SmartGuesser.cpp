#include "SmartGuesser.hpp"

using namespace bullpgia;

// Guess combination based on the length of the string
string SmartGuesser::guess()
{

	if (length < 6)
	{
		if (lastGuess == "")
		{
			lastGuess = firstGuess();
		}
		else
		{	//guess a random number from the remaining options
			int index = rand() % combination.size();
			auto it = combination.begin();
			for (int i = 0; i < index; i++)
			{
				it++;
			}			
			lastGuess = *it;
		}
	}
	else if (currentNum < 10)
	{
		//finds the digits
		lastGuess = nextGuess();
	}
	return lastGuess;
}


// Initializing globals variables
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

// Router to the right funcion for each length
void SmartGuesser::learn(string reply)
{
	length < 6 ? learnShort(reply) : learnLong(reply);
}

//************************* short length functions **************************//
// First guess 
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
// Intilaizing all possible combinations 
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

// For each guss we filter the bad choices
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

//************************* great length functions **************************//

// Responsible for crreating next guesses
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

// First guesses - finds all digits of the number
string SmartGuesser::nextGuess()
{
	string nGuess = "";
	for (size_t i = 0; i < length; i++)
	{
		nGuess += to_string(currentNum);
	}
	return nGuess;
}

// Finds a num that is not in the "secret number"
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

// Finds the next possible guess
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
// Updating the result with the right char
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

// Finding the next char that need to placed
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

// Creates a string of the first guess
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

// Creating possible guesses based on earlier knowladge (does everything - including coffee)
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

// Returns true if all digits where found
bool SmartGuesser::sumNubers()
{
	int sum = 0;
	for (int i : numbers)
	{
		sum += i;
	}
	return sum == length;
}
// Finds the position of a given char
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

// Initializing when all digits where found
void SmartGuesser::InitLong()
{
	unChosenNum = notInNum();
	rs.assign(length, unChosenNum);

	isIntialized = true;
	currentChar = findNextChar();
	lastGuess = stringMaker(currentChar, 0); //creating the first string
}
