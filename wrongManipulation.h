#pragma once
#include<iostream>
#include<string>
using namespace std;

/*Pre: a user input (!= user command)
Post: show that user have typed a wrong command */
void wrongManipulation(string userInput)
{
	for (int i = 0; i < userInput.size(); ++i) {
		if (userInput[i] != ' ') {
			cout << endl << endl << "The term  '" << userInput << "' is not recognized as the name of a cmdlet, function, script file, or operable program.Check the spelling of the name, or if a path was included, verify that the path is correct and try again." << endl << endl;
			return;
		}
	}
}