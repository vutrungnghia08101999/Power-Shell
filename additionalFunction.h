#pragma once
#include"commonFunction.h"
#include"EnvironmentVariable.h"
#include"utinity.h"
#include<ctime>
#include<tlhelp32.h>
#include<tchar.h>
#include<psapi.h>

string threadState(HANDLE hThread);							//Determine state of a thread given its handle (already define in "utinity.h")
string ProcessName(HANDLE hProcess);							//Given a Handle return its name
vector<ThreadAndStatus> getThreadIDAndState(HANDLE hProcess);	//Given a Process Handle return a vector contain all its threadID and state for each state

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
			printf("   %-10d%-30s\n", GetProcessId(hProcess), ProcessName(hProcess).c_str());
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
			cout << endl << "ERROR: " << id << " is not an integer!" << endl << endl;
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
			cout << endl << "ERROR: " << id << " is not an integer!" << endl << endl;
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
			cout << endl << "ERROR: " << id << " is not an integer!" << endl << endl;
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
			cout << endl << "ERROR: " << id << " is not an integer!" << endl << endl;
		}
	}

	else {
		cout << endl << "ERROR: Systax error!!! (utinity module) " << endl;
	}
}

string ProcessName(HANDLE hProcess)
{
	if (hProcess == NULL)
		return "<unknown>";

	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	HMODULE hMod;
	DWORD cbNeeded;

	if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
	{
		GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
		return szProcessName;
	}

	return "<unknown>";
}
vector<ThreadAndStatus> getThreadIDAndState(HANDLE hProcess)
{
	vector<ThreadAndStatus> threadList;

	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return threadList;

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return threadList;
	}

	// Now walk the thread list of the system, and display information about each thread associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == GetProcessId(hProcess))
		{
			ThreadAndStatus ThreadInfo;
			ThreadInfo.ID = te32.th32ThreadID;

			HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, ThreadInfo.ID);
			ThreadInfo.ThreadStatus = threadState(hThread);

			threadList.push_back(ThreadInfo);
		}
	} while (Thread32Next(hThreadSnap, &te32));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);

	return threadList;
}
