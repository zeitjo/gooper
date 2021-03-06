/**********************************************
 * Hungman Program
 * Author: Jonathon Zeitler
 * Created: 05/14/2017
 **********************************************/
 
 #include <iostream>
 #include <fstream>	// Standard library for i/o file streams
 #include <string>	// Standard library for handy string functions
 
 // These are for random number generation
 #include <chrono>
 #include <random>
 
 using namespace std;
 
 /* A constant is defined once at compile time and cannot change
  * Use the keyword "const" in the variable's declaration to
  * make it constant.
  * While not required by the compiler, it is a common convention
  * to use all caps in the name of a constant to make it readily
  * identifiable as such.
  */
 const int NUM_LINES = 116;	///< Number of lines in words.txt
 
 // Generate a random integer between 0 and max - 1
 int random_int(int max);
 
 int main()
 {
	// Open words.txt file
	ifstream inf;	///< Input file stream
	inf.open("words.txt");
	if (!inf.good())
	{
		cerr << "Failed to open \"words.txt\"." << endl;
		return -1;
	}
	
	// Collect words
	/*
	 * To declare an array of objects of type T and size N:
	 * 		T arrayname[N];
	 *
	 * examples:
	 *		int numbers[100];	///< An array of 100 ints named "numbers"
	 *		char word[45];		///< Array of 45 characters called "word"
	 *		ifstream files[4];	///< Array of 4 filestreams called "files"
	 *
	 * IMPORTANT: In order to use this method to declare an array, the size
	 *		must be known at compile time. N must be a positive integer
	 *		expressed either as a literal (e.g. 100, 45, 4) or a constant
	 *		(like NUM_LINES in this program).
	 *		We'll discuss dynamic arrays, whose size can be determined at
	 *		runtime, a little bit later
	 */
	string words[NUM_LINES];	///< Array of strings
	
	
	for (int i=0; i<NUM_LINES; i++)
	{
		getline(inf, words[i]);	// Extract line as string to index i
		
		/*
		 * A typical way to extract a string from a stream would be:
		 *
		 *		inf >> words[i];
		 *
		 * But this will extract a whitespace-delimited string, and
		 * some of our "words" are actually two words. So instead,
		 * I use a standard library function to grab a newline ('\n')
		 * delimited line at a time.
		 *
		 * The function getline takes a stream, an output string, and
		 * optionallya delimiting character. If the third argument
		 * is not given, like in my use of the function above, it
		 * defaults to '\n'.
		 *
		 * By the way:
		 *		Single quotes ('') are used for a single character literal (value)
		 *		Double quotes ("") are used for a string literal
		 */
	}
	
	// We're done now, close the file
	inf.close();
	
	// Now for the game
	string guess;	// To hold the player's guesses
	bool playing=true;	// For game loop
	
	// Game loop
	while (playing)	// A bool can be used as a condition directly
	{
		// select a string from random index
		string word = words[random_int(NUM_LINES)];
		
		// Prompt
		
		cout << endl << ":::::::::::::::::::::::::" << endl
			 << ": Try to guess my word! :" << endl
			 << ":::::::::::::::::::::::::" << endl << endl;
		
		cout << "\t";	// '\t' is the escape character for a tab
		
		/* Unsigned indicates an unsigned int, i.e. no negatives.
		 * You'll get a warning if you use a regular int for comparing
		 * sizes like in string's length() but it'll work either way
		 * and honestly, I miss it all the time.
		 */
		for (unsigned i=0; i<word.length(); i++)
		{
			/*
			 * Now's a good time to discuss the 'equals' operator.
			 * It's used to check for equivalence and returns a bool.
			 * It is "==". Know it.
			 *
			 * A common error is to use "=" in place of an intended "==".
			 * "=" is the assignment operator - it is used to set the value
			 * of a variable. It usually returns a reference to the variable
			 * itself.
			 *
			 * If you try to to use "=" in a conditional, the value of
			 * the variable will be cast to a boolean where anything besides
			 * "null" (whice is zero for an int) will be true.
			 */
			if (random_int(2) == 0) // 50% chance for each option below
			{
				// Character from word
				cout << word[i];	// strings can be treated like arrays
									// of characters
			}
			else
			{
				// Hide character
				cout << '_';
			}
		}
		cout << endl << endl << "What could it be, baby? ";
		
		// Take the player's guess
		getline(cin, guess);	// "cin" is the standard input stream
		
		cout << endl;
		
		// Check the player's guess and print outcome
		if (guess == word)
		{
			// Win
			cout << ":):):):):):):):):)" << endl
				 << ":) Your Winner! :)" << endl
				 << ":):):):):):):):):)" << endl;
		}
		else
		{
			// Lose
			cout << ":(:(:(:(:(:(:(:(:(:(:(:(:(" << endl
				 << ":( You're are not good. :(" << endl
				 << ":( Correct answer is \"" << word << "\"." << endl
				 << ":(:(:(:(:(:(:(:(:(:(:(:(:(" << endl;
		}
		
		// Ask to play again
		cout << endl << "Play again? (y/n)";
		
		// Get response
		getline(cin, guess);	// I'm just reusing guess for input
		
		// Set the condition for continuing the game based on the first character
		// of the user input
		playing = (guess[0] == 'y' || guess[0] == 'Y');
		
		// Program will only perform another iteration of while loop if the first
		// character (index 0) of the response is either 'y' or 'Y'
		
		// Output a blank line
		cout << endl;
	}
	
	 
	return 0;
 }
 
 /*************************************
  * random_int
  * param	: max - top value bound
  * returns	: random int 0 to max-1
  *************************************/
 int random_int(int max)
 {
	static unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937 generator(seed);
	
	return (generator() % max);
 }