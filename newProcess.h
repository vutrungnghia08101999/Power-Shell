#pragma once
#include"EnvironmentVariable.h"
using namespace std;

void newProcess(string userInput, string userCommand, STARTUPINFO *startUpInfor, PROCESS_INFORMATION *processList, EnvironmentVariable *Env, int *NUMBER_OF_PROCESS)
{
	int n = userCommand.size();
	if (userCommand.size() >= 8 && userCommand.find_first_of('\"') == 5 && userCommand.find_last_of('\"') == userCommand.size() - 1) {
		string path = userCommand.substr(6, n - 7);
		if (userCommand.substr(n - 4, 3) == "exe" || userCommand.substr(n - 4, 3) == "bat") {	//exe, bat
			if (userCommand.substr(6, 2) == "c:" || userCommand.substr(6, 2) == "d:" || userCommand.substr(6,2) == "e:") {							//Complete path
				TCHAR p[200] = {};
				for (int i = 0; i < path.size(); ++i)
					p[i] = path[i];
				if (CreateProcess(p, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startUpInfor[*NUMBER_OF_PROCESS], &processList[*NUMBER_OF_PROCESS])) {
					if (userCommand.substr(n - 4, 3) == "exe" && userCommand.substr(0, 4) == "back")
						*NUMBER_OF_PROCESS += 1;
					if (userCommand.substr(0, 4) == "fore") {
						WaitForSingleObject(processList[*NUMBER_OF_PROCESS].hProcess, INFINITE);
					}
		
					return;
				}
				else {																			
					cout << endl << "ERROR: " << "Cannot find this path because it does not exist" << endl;
				}
			}
			else {																								//Reduce path
				//Firstly search in current working direction
				string s = Env->currentPath + "\\" + path.substr(2);
				TCHAR p[200] = {};
				for (int i = 0; i < s.size(); ++i)
					p[i] = s[i];
				if (CreateProcess(p, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startUpInfor[*NUMBER_OF_PROCESS], &processList[*NUMBER_OF_PROCESS])) {
					if (userCommand.substr(n - 4, 3) == "exe" && userCommand.substr(0, 4) == "back")
						*NUMBER_OF_PROCESS += 1;
					if (userCommand.substr(0, 4) == "fore") {
						WaitForSingleObject(processList[*NUMBER_OF_PROCESS].hProcess, INFINITE);
					}
					return;
				}

				//Secondlly search in path
				else {
					for (int i = 0; i < Env->Path.size(); ++i) {
						string s = Env->Path[i] + "\\" + path.substr(2);
						TCHAR p[200] = {};
						for (int i = 0; i < s.size(); ++i)
							p[i] = s[i];
						if (CreateProcess(p, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startUpInfor[*NUMBER_OF_PROCESS], &processList[*NUMBER_OF_PROCESS])) {
							if (userCommand.substr(n - 4, 3) == "exe" && userCommand.substr(0, 4) == "back")
								*NUMBER_OF_PROCESS += 1;
							if (userCommand.substr(0, 4) == "fore") {
								WaitForSingleObject(processList[*NUMBER_OF_PROCESS].hProcess, INFINITE);
							}
							
							return;
						}
					}

					cout << endl << "ERROR: " << "Cannot find this path because it does not exist" << endl;
				}
			}
		}

		else if (userCommand.substr(n - 4, 3) == "mp4") {									//.mp4, ...
			if (userCommand.substr(6, 2) == "c:" || userCommand.substr(6, 2) == "d:" || userCommand.substr(6, 2) == "e:") {						//Complete path
				string s = "cmd.exe /c " + path;
				TCHAR p[200] = {};
				for (int i = 0; i < s.size(); ++i)
					p[i] = s[i];
				if (CreateProcess(NULL, p, NULL, NULL, false, CREATE_UNICODE_ENVIRONMENT, NULL, NULL, &startUpInfor[*NUMBER_OF_PROCESS], &processList[*NUMBER_OF_PROCESS]))
					return;
				else {
					cout << endl << "ERROR: " << "Cannot find this path because it does not exist" << endl;
				}
			}
			else {																							//Reduce path
				//Firstly search in current working direction
				string s = "cmd.exe /c " + Env->currentPath + "\\" + path.substr(2);
				//cout << s << endl;
				TCHAR p[200] = {};
				for (int i = 0; i < s.size(); ++i)
					p[i] = s[i];
				if (CreateProcess(NULL, p, NULL, NULL, false, CREATE_UNICODE_ENVIRONMENT, NULL, NULL, &startUpInfor[*NUMBER_OF_PROCESS], &processList[*NUMBER_OF_PROCESS]))
					return;

				//Secondlly search in path
				else {
					for (int i = 0; i < Env->Path.size(); ++i) {
						string s = "cmd.exe /c " + Env->Path[i] + "\\" + path.substr(2);
						TCHAR p[200] = {};
						for (int i = 0; i < s.size(); ++i)
							p[i] = s[i];
						if (CreateProcess(NULL, p, NULL, NULL, false, CREATE_UNICODE_ENVIRONMENT, NULL, NULL, &startUpInfor[*NUMBER_OF_PROCESS], &processList[*NUMBER_OF_PROCESS]))
							return;
					}

					cout << endl << "ERROR: " << "Cannot find this path because it does not exist" << endl;
				}
			}
		}

		else {
			cout << endl << "Because this is a tiny shell so we can't run this kind of file" << endl;
		}
	}
	else {
		cout << endl << "Systex Error: " << userInput << " is not recognized as the name of a cmdlet, function, script file, oroperable program.Check the spelling of the name, or if a path was included, verify that the path is correct and try again." << endl;
	}
}
	