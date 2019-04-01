#include"inputHandle.h"
#include"help.h"
#include"newProcess.h"
#include"changeCurrentDirection.h"
#include"changeEnv.h"
#include"utinity.h"
#include"wrongManipulation.h"
#include"additionalFunction.h"
//#include"CtrlC.h"
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
	///*********************************************/
	//bool running = true;
	//setconsolectrlhandler(consolehandler, true);
	///*********************************************/

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
		fflush(stdin);
		printf("MyShell %s>", Env->currentPath.c_str());
		getline(cin, userInput);
		userCommand = inputHandle(userInput, &manipulation);
		switch (manipulation)
		{
		case 1:
			help(userCommand);
			break;
		case 2:
			newProcess(userInput, userCommand, startUpInfor, processList, Env, &NUMBER_OF_PROCESS);
			/*hForegoundProcess is a global pointer. It is in CtrlC.h. I can't find other way to kill current foreground process by ConsoleHandler
			because there are only one parameter to this function is "DWORD signal", thus I ca't give a handle to this function*/
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
			wrongManipulation(userInput);
			break;
		default:
			break;
		}
		//printf("<MyShell>%s>", Env->currentPath);
		manipulation = -1;
	}

	return 0;
}