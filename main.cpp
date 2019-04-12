#include"inputHandle.h"
#include"help.h"
#include"newProcess.h"
#include"changeCurrentDirection.h"
#include"changeEnv.h"
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
void newProcess(string userInput, string userCommand, STARTUPINFO *startUpInfor, PROCESS_INFORMATION *processList, EnvironmentVariable *Env, int *NUMBER_OF_PROCESS);
void changeCurrentDirection(string userInput, string userCommand, EnvironmentVariable *Env);
void changeEnv(string userCommand, EnvironmentVariable *Env);
void utinity(string userInput, string userCommand, EnvironmentVariable *Env, PROCESS_INFORMATION *processList, int *NUMBER_OF_PROCESS);
void additionalFunction(string userInput, string userCommand);
void wrongManipulation(string userInput);

int main()
{
	SetConsoleCtrlHandler(consoleHandler, TRUE);		//CTRL-C Handle

	int manipulation = -1;
	EnvironmentVariable *Env = new EnvironmentVariable();

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

		//
		printf("MyShell %s>", Env->currentPath.c_str());
		//

		getline(cin, userInput);
		userCommand = inputHandle(userInput, &manipulation);
		switch (manipulation)
		{
		case 1:
			help(userCommand);
			break;
		case 2:
			newProcess(userInput, userCommand, startUpInfor, processList, Env, &NUMBER_OF_PROCESS);
			break;
		case 3:
			changeCurrentDirection(userInput, userCommand, Env);
			break;
		case 4:
			changeEnv(userCommand, Env);
			break;
		case 5:
			utinity(userInput, userCommand, Env, processList, &NUMBER_OF_PROCESS);
			break;
		case 6:
			additionalFunction(userInput, userCommand);
			break;
		case 7:
			Sleep(1);		//synchronize this thread and cosoleHandler thread. just for good user interface
			wrongManipulation(userInput);
			break;
		default:
			break;
		}
		manipulation = -1;
	}

	return 0;
}