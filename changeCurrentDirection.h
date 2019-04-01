#pragma once
#include"commonFunction.h"
#include"EnvironmentVariable.h"
#include<ctype.h>	

vector<string> dirFolder(string path);	//List all folder in this path

/*********************************  MAIN FUNCTION  ****************************************/
/*
Pre:
	- cd ./..
	- cd "Latex"
	- cd "C:\Users\nghia.vt173284\Desktop"
Post:
	- if path is ok then change Environment.currentPath = newPath
	- else Print ERROR.                                                                 */
void changeCurrentDirection(string userInput, string userCommand, EnvironmentVariable *Env)
{
	//cd "     "
	if (userCommand.size() >= 6 && userCommand.find_first_of('\"') == 3 && userCommand.find_last_of('\"') == userCommand.size() - 1) {
		//cd "C:\Users\nghia.vt173284\Desktop" 
		if (userCommand.substr(4, 2) == "c:" || userCommand.substr(4, 2) == "d:") {		

			/*NOTICE: This code is not optimize, You should check to determine whether the path is exist or not*/

			string path = userCommand.substr(4, userCommand.size() - 5);
			Env->currentPath = path;
		}

		//cd "Latex"
		else {																
			string folder = userCommand.substr(4, userCommand.size() - 5);
		
			/*=====================================================================*/
			//This is a special case because my shell can't list "Users" in "C:"  and "Desktop" in "C:\Users\nghia.vt173284"
			bool check = toLower(folder) == "users" || toLower(folder) == "program files" || toLower(folder) == "program files (x86)";
			if (toLower(Env->currentPath) == "c:" && check) {
				Env->currentPath += "\\" + folder;
				return;
			}

			if (toLower(Env->currentPath) == "c:\\users\\nghia.vt173284" && toLower(folder) == "desktop") {
				Env->currentPath += "\\" + folder;
				return;
			}
			/*====================================================================*/

			vector<string> ListFolder = dirFolder(Env->currentPath);
			for (int i = 0; i < ListFolder.size(); ++i) {
				if (toLower(folder) == toLower(ListFolder[i])) {
					Env->currentPath += "\\" + ListFolder[i];
					return;
				}
			}

			cout << endl << folder << " is not in this directory!!!" << endl;
		}
	}

	//cd ./..
	else if (userCommand == "cd ./..") {											
		if (Env->currentPath.size() >= 3) {
			while (Env->currentPath.back() != '\\')
				Env->currentPath.pop_back();
			Env->currentPath.pop_back();
		}
	}

	//wrong input
	else {
		cout << endl << "Systex Error: " << userInput << " is not recognized as the name of a cmdlet, function, script file, oroperable program.Check the spelling of the name, or if a path was included, verify that the path is correct and try again." << endl;
	}
}

vector<string> dirFolder(string path)
{
	path += "\\*";
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	vector<string> ListFolder;
	TCHAR p[200] = {};
	for (int i = 0; i < path.size(); ++i)
		p[i] = path[i];

	hFind = FindFirstFile(p, &FindFileData);
	do
	{
		if (FindFileData.dwFileAttributes == 16)
			ListFolder.push_back(FindFileData.cFileName);
	} while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

	return ListFolder;
}
