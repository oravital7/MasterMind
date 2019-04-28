/**
 * A demo program for bull-pgia.
 * 

 * @since  2019-04
 */

#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace bullpgia;

int main()
{

	badkan::TestCase testcase;
	int grade = 0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0)
	{

		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};

		testcase.setname("Calculate bull and pgia")
				.CHECK_OUTPUT(calculateBullAndPgia("1234", "1234"), "4,0") // 4 bull, 0 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("1234", "4321"), "0,4") // 0 bull, 4 pgia
				;

		testcase.setname("Play with dummy choosers and guessers")
				.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)		 // guesser wins in one turn.
				.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)	// guesser loses by running out of turns
				.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101) // guesser loses technically by making an illegal guess (too long).
				.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)	 // chooser loses technically by choosing an illegal number (too long).
				;

		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (uint i = 0; i < 100; ++i)
		{
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100) <= 10, true); // smarty should always win in at most 10 turns!
		}

		// Private tests
		testcase.setname("Calculate bull and pgia")
				.CHECK_OUTPUT(calculateBullAndPgia("1234", "5678"), "0,0") // 0 bull, 0 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("12345", "66661"), "0,1") // 0 bull, 1 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("5721", "1234"), "0,2") // 0 bull, 2 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("1111", "1111"), "4,0") // 4 bull, 0 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("555555", "111111"), "0,0") // 0 bull, 0 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("1", "2"), "0,0") // 0 bull, 0 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("1", "1"), "1,0") // 1 bull, 0 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("12", "21"), "0,2") // 0 bull, 2 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("143", "132"), "1,1") // 1 bull, 1 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("123", "321"), "1,2") // 1 bull, 2 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("1234", "4321"), "0,4") // 0 bull, 4 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("12345", "66661"), "0,1") // 0 bull, 1 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("123456789", "123456789"), "9,0") // 9 bull, 0 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("987654321", "123456789"), "1,8") // 1 bull, 8 pgia
				.CHECK_OUTPUT(calculateBullAndPgia("2234", "2111"), "1,0")
				.CHECK_OUTPUT(calculateBullAndPgia("2134", "1111"), "1,0")
				.CHECK_OUTPUT(calculateBullAndPgia("1404", "4441"), "1,2")
				.CHECK_OUTPUT(calculateBullAndPgia("5423", "3523"), "2,1");




				

		testcase.setname("Play with smart guesser");
		for (uint i = 0; i < 50; ++i)
		{
			testcase.CHECK_EQUAL(play(randy, smarty, 2, 100) <= 10, true); // smarty should always win in at most 10 turns!
		}

		for (uint i = 0; i < 50; ++i)
		{
			testcase.CHECK_EQUAL(play(randy, smarty, 3, 100) <= 10, true); // smarty should always win in at most 10 turns!
		}

		for (uint i = 0; i < 50; ++i)
		{
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100) <= 10, true); // smarty should always win in at most 10 turns!
		}

		for (uint i = 0; i < 10; ++i)
		{
			testcase.CHECK_EQUAL(play(randy, smarty, 5, 100) <= 10, true); // smarty should always win in at most 10 turns!
		}

		ConstantChooser c{"123445"};
		for (uint i = 0; i < 50; ++i)
		{
			ConstantGuesser b{"12345"+to_string(i)};
			testcase.CHECK_EQUAL(play(c, b, 6, 100), 101); // Guesser should loose always
		}

		c = ConstantChooser{"9881"};
		for (uint i = 0; i < 50; ++i)
		{			
			ConstantGuesser l{"987"+to_string(i)};
			testcase.CHECK_EQUAL(play(c, l, 4, 100), 101); // Guesser should loose always
		}

		c = ConstantChooser{"233"};
		for (uint i = 0; i < 50; ++i)
		{			
			ConstantGuesser l{"22"+to_string(i)};
			testcase.CHECK_EQUAL(play(c, l, 3, 100), 101); // Guesser should loose always
		}

		for (uint i = 10; i < 100; ++i)
		{
			c = ConstantChooser{"1234" + to_string(i)};
			ConstantGuesser b{"1234" + to_string(i)};
			testcase.CHECK_EQUAL(play(c, b, 6, 100), 1); // Guesser should win always in 1 turn
		}

		for (uint i = 10; i < 100; ++i)
		{
			c = ConstantChooser{"789" + to_string(i)};
			ConstantGuesser b{"789" + to_string(i)};
			testcase.CHECK_EQUAL(play(c, b, 5, 100), 1); // Guesser should win always in 1 turn
		}

		for (uint i = 10; i < 100; ++i)
		{
			c = ConstantChooser{"25" + to_string(i)};
			ConstantGuesser b{"25" + to_string(i)};
			testcase.CHECK_EQUAL(play(c, b, 4, 100), 1); // Guesser should win always in 1 turn
		}
		grade = testcase.grade();
	}
	else
	{
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: " << grade << endl;
	return 0;
}
