#pragma once
#include<iostream>
#include<string>
#include<ctype.h>
using namespace std;

/*
	- Delete all meaningless space that is not in  ""   Ex: |   acsvs       "  nghia "|		=>			|acsvs "   nghia"| 
	- Delete all the leter that is behind ""			Ex: | sadfdasf   "abc   "asdfdasf|	=>			|sadfdasf "abc   "|
	- Transform all upperletter to lowerletter			Ex: | sadfdasf   "ABC   "asdfdasf|  =>			|sadfdasf "abc   "|
*/
string normalize(string s)
{
	string result;
	
	if (s.find_first_of('\"') != string::npos && s.find_last_of('\"') != string::npos) {
		int start = s.find_first_of('\"');
		int end = s.find_last_of('\"');

		int temp = (s.find_first_not_of(' ') != string::npos) ? s.find_first_not_of(' ') : s.size();
		for (int i = temp; i < start; ++i) {
			if (s[i] != ' ' || (s[i] == ' ' && s[i + 1] != ' '))
				result.push_back(s[i]);
		}

		for (int i = start; i <= end; ++i)
			result.push_back(s[i]);
	}
	else {
		int start = (s.find_first_not_of(' ') != string::npos) ? s.find_first_not_of(' ') : s.size();
		for (int i = start ; i < (int)s.size() - 1; ++i) {	
			if (s[i] != ' ' || (s[i] == ' ' && s[i + 1] != ' '))
				result.push_back(s[i]);
		}
		if (s.size() > 0 && s[s.size() - 1] != ' ')
			result.push_back(s[s.size() - 1]);
	}
	 
	string temp;
	for (int i = 0; i < result.size(); ++i) {
		if (isalpha(result[i]))
			temp.push_back(tolower(result[i]));
		else
			temp.push_back(result[i]);
	}
	return temp;
}

//Because the conditions are too long, so I need this function to check the conditions
//For [1] [2] [3] [5] [6]we don't need to create a whole function
bool checkUtinity(string userCommand)				//main function for this module//
{
	if (userCommand == "date" || userCommand == "exit" || userCommand == "dir" || userCommand == "list" || userCommand == "getenv" || userCommand == "clear" || userCommand == "exitall")
		return true;
	if (userCommand.size() >= 10 && userCommand.substr(0, 10) == "terminate ")
		return true;
	if (userCommand.size() >= 8 && userCommand.substr(0, 8) == "suspend ")
		return true;
	if (userCommand.size() >= 7 && userCommand.substr(0, 7) == "resume ")
		return true;
	return false;
}

bool checkAdditionalFunction(string userCommand)
{
	if (userCommand == "listall")
		return true;
	if (userCommand.size() >= 11 && userCommand.substr(0, 11) == "listthread ")
		return true;
	if (userCommand.size() >= 11 && userCommand.substr(0, 11) == "suspendadd ")
		return true;
	if (userCommand.size() >= 10 && userCommand.substr(0, 10) == "resumeadd ")
		return true;
	if (userCommand.size() >= 13 && userCommand.substr(0, 13) == "terminateadd ")
		return true;
	return false;
}

string inputHandle(string userInput, int *manipulation)
{
	string userCommand = normalize(userInput);

	if (userCommand.size() >= 4 && userCommand.substr(0, 4) == "help")
		*manipulation = 1;
	else if (userCommand.size() >= 5 && (userCommand.substr(0, 5) == "fore " || userCommand.substr(0, 5) == "back "))
		*manipulation = 2;
	else if ((userCommand.size() >= 5 && userCommand.substr(0, 3) == "cd "))
		*manipulation = 3;
	else if (userCommand.size() >= 7 && userCommand.substr(0, 4) == "env:")
		*manipulation = 4;
	else if (checkUtinity(userCommand))
		*manipulation = 5;
	else if (checkAdditionalFunction(userCommand))
		*manipulation = 6;
	else
		*manipulation = 7;
	
	return userCommand;
}


