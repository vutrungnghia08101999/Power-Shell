#include"commonFunction.h"
#include<ctime>
#include<tlhelp32.h>
#include<tchar.h>
#include<psapi.h>

void additionalFunction(string userInput, string userCommand)
{
	if (userCommand == "listall") {
		cout << endl << endl;
		printf("%-13s%-30s\n", "ProcessID", "ProcessName");
		printf("%-13s%-30s\n", "-------------", "-------------");

		DWORD aProcesses[1024], cbNeeded, cProcesses;
		unsigned int i;

		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
			return;

		// Calculate how many process identifiers were returned.	
		cProcesses = cbNeeded / sizeof(DWORD);

		for (int i = 0; i < cProcesses; ++i) {
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, aProcesses[i]);
			printf("   %-10d%-30s\n", aProcesses[i], ProcessName(hProcess).c_str());
		}
		cout << endl << endl;
	}
	else if (userCommand.size() >= 12 && userCommand.substr(0, 11) == "listthread ") {
		string id = userCommand.substr(11);
		if (isInteger(id)) {
			int ProcessID = toInteger(id);
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);
			vector<ThreadAndStatus> threadList = getThreadIDAndState(hProcess);
			
			cout << endl << endl;
			printf("%-10s%-20s%-30s\n", "", "ThreadID", "ThreadState");
			printf("%-10s%-20s%-30s\n", "", "----------", "------------");
			for (int i = 0; i < threadList.size(); ++i) {
				printf("%-10s%-20d%-30s\n", "", threadList[i].ID, threadList[i].ThreadStatus.c_str());
			}

			cout << endl << endl;
		}
		else {
			printError("ERROR: " + id + " is not an integer!");
		}

	}
	else if (userCommand.size() >= 12 && userCommand.substr(0, 11) == "suspendadd ") {
		string id = userCommand.substr(11);
		if (isInteger(id)) {
			int ProcessID = toInteger(id);
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);
			vector<ThreadAndStatus> threadList = getThreadIDAndState(hProcess);

			HANDLE hThread;
			for (int i = 0; i < threadList.size(); ++i) {
				hThread = OpenThread(THREAD_ALL_ACCESS, false, threadList[i].ID);
				SuspendThread(hThread);
			}
		}
		else {
			
			printError("ERROR: " + id + " is not an integer!");
		}
	}
	else if (userCommand.size() >= 11 && userCommand.substr(0, 10) == "resumeadd ") {
		string id = userCommand.substr(10);
		if (isInteger(id)) {
			int ProcessID = toInteger(id);
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);
			vector<ThreadAndStatus> threadList = getThreadIDAndState(hProcess);

			HANDLE hThread;
			for (int i = 0; i < threadList.size(); ++i) {
				hThread = OpenThread(THREAD_ALL_ACCESS, false, threadList[i].ID);
				ResumeThread(hThread);
			}
		}
		else {
			printError("ERROR: " + id + " is not an integer!");
		}
	}

	else if (userCommand.size() >= 13 && userCommand.substr(0, 13) == "terminateadd ") {
		string id = userCommand.substr(13);
		if (isInteger(id)) {
			int ProcessID = toInteger(id);
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);
			TerminateProcess(hProcess, 1);
		}
		else {
			printError("ERROR: " + id + " is not an integer!");
		}
	}

	else {
		printError("ERROR: Systax error!!!");
	}
}
