#pragma once
#include"commonFunction.h"
#include"EnvironmentVariable.h"
#include<ctype.h>	

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
		if (userCommand.substr(4, 2) == "c:" || userCommand.substr(4, 2) == "d:" || userCommand.substr(4, 2) == "e:") {

			/*NOTICE: This code is not optimize, You should check to determine whether the path is exist or not*/
			
			string path = userCommand.substr(4, userCommand.size() - 5);
			if(checkPath(path))
				Env->currentPath = path;
			else 
				cout << endl << endl << "[ERROR]: " << "This path doesn't exist!!! :((" << endl << endl;
		}

		//cd "Latex"
		else {																
			string folder = userCommand.substr(4, userCommand.size() - 5);

			string path = Env->currentPath + "\\" + folder;
			if (checkPath(path))
				Env->currentPath = path;
			else
				cout << endl << "[ERROR]: " << folder << "is not in this directory!!!" << endl;
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