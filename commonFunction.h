#pragma once
#include<iostream>
#include<sstream>
using namespace std;

//Vu Trung Nghia => vu trung nghia
string toLower(string s)
{
	for (int i = 0; i < s.size(); ++i) {
		if (isalpha(s[i]))
			s[i] = tolower(s[i]);
	}

	return s;
}

bool isInteger(string s)
{
	for (int i = 0; i < s.size(); ++i) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

int toInteger(string s)
{
	int number;
	istringstream iss(s);
	iss >> number;
	return number;
}
