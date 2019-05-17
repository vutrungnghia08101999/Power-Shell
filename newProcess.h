#include"CtrlC.h"
#include"commonFunction.h"
using namespace std;

void newProcess(string userInput, string userCommand, STARTUPINFO *startUpInfor, PROCESS_INFORMATION *processList, int *NUMBER_OF_PROCESS)
{
	int n = userCommand.size();
	if (userCommand.size() >= 9 && userCommand.find_first_of('\"') == 5 && userCommand.find_last_of('\"') == userCommand.size() - 1) {
	
		string path = userCommand.substr(6, n - 7);			//main.exe or C:\Users\nghia.vt173284\Desktop\main.exe
		TCHAR p[200] = {};
		stringToTCHAR(p, path);

		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);

		if (!CreateProcess(NULL, p, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			printError("[ERROR]: " + path + " is not exist!!!");
			return;
		}

		string backOrFore = userCommand.substr(0, 4);
		if (backOrFore == "back") {
			processList[*NUMBER_OF_PROCESS] = pi;
			*NUMBER_OF_PROCESS += 1;
		}
		else if (backOrFore == "fore") {
			hForeProcess = pi.hProcess;		//This is for Ctrl-C Handle
			WaitForSingleObject(pi.hProcess, INFINITE);
		}
		
	}
	else {
		printError("Systex Error: " + userInput + " is not recognized as the name of a cmdlet, function, script file, oroperable program.Check the spelling of the name, or if a path was included, verify that the path is correct and try again.");
	}
}
	