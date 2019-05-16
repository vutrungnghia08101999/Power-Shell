#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
using namespace std;

struct ThreadAndStatus
{
	int ID;
	string ThreadStatus;
};

struct ProcessInformation
{
	string ProcessName;
	int ID;
	vector<ThreadAndStatus> ThreadList;
};

struct FileInformation
{
	string name;
	string categories;
	string dateLastWrite;
	string timeLastWrite;

	FileInformation(string name_x, string categories_x, string dateLastWrite_x, string timeLastWrite_x) {
		name = name_x;
		categories = categories_x;
		dateLastWrite = dateLastWrite_x;
		timeLastWrite = timeLastWrite_x;
	}
};

