#include"inputHandle.h"
#include"help.h"
#include"newProcess.h"
#include"setCurrentDirectory.h"
#include"setEnv.h"
#include"utinity.h"
#include"wrongManipulation.h"
#include"additionalFunction.h"
#include"CtrlC.h"
#include<stdio.h>
#include<stdio.h>
#include<tchar.h>
#include<psapi.h>
#include<vector>
using namespace std;


string inputHandle(string userInput, int *manipulation);
void help(string usercommand);
void newProcess(string userInput, string userCommand, STARTUPINFO *startUpInfor, PROCESS_INFORMATION *processList, int *NUMBER_OF_PROCESS);
void setCurrentDirection(string userInput, string userCommand);
void setEnv(string userCommand);
void utinity(string userInput, string userCommand, PROCESS_INFORMATION *processList, int *NUMBER_OF_PROCESS);
void additionalFunction(string userInput, string userCommand);
void wrongManipulation(string userInput);

int main()
{
	SetConsoleCtrlHandler(consoleHandler, TRUE);		//CTRL-C Handle

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	
	cout << "Windows PowerShell" << endl;
	cout << "Authors: Vu Trung Nghia - Le Vu Loi. All rights reserved." << endl << endl;
	int manipulation = -1;

	STARTUPINFO startUpInfor[1000];
	PROCESS_INFORMATION processList[1000];
	int NUMBER_OF_PROCESS = 0;

	for (int i = 0; i < 1000; ++i) {
		ZeroMemory(&startUpInfor[i], sizeof(startUpInfor[i]));
		startUpInfor[i].cb = sizeof(startUpInfor[i]);
	}
	string userInput;
	string userCommand;
	while (true) {
		printf("MyShell %s>", getCurrentDirectory().c_str());
		SetConsoleTextAttribute(hConsole, 6);		
		getline(cin, userInput);
		SetConsoleTextAttribute(hConsole, 15);
		userCommand = inputHandle(userInput, &manipulation);
		switch (manipulation)
		{
		case 1:
			help(userCommand);
			break;
		case 2:
			newProcess(userInput, userCommand, startUpInfor, processList, &NUMBER_OF_PROCESS);
			break;
		case 3:
			changeCurrentDirection(userInput, userCommand);
			break;
		case 4:
			setEnv(userCommand);
			break;
		case 5:
			utinity(userInput, userCommand, processList, &NUMBER_OF_PROCESS);
			break;
		case 6:
			additionalFunction(userInput, userCommand);
			break;
		case 7:
			Sleep(1);		//synchronize main thread and cosoleHandler thread. Just for good user interface
			wrongManipulation(userInput);
			break;
		default:
			break;
		}
		manipulation = -1;
	}

	return 0;
}
