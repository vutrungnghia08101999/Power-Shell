#pragma once
#include"commonFunction.h"
#include"EnvironmentVariable.h"
#include<ctime>
#include<tlhelp32.h>
#include<tchar.h>
#include<psapi.h>

vector<string> dir(string path, int *pivot);				//return all files and folder in this path, pivot to separate folder and file
ProcessInformation ProcessInformations(HANDLE hProcess);	//return a struct that contains all information about the process such as name, ID, Thread list and state for each thread
string threadState(HANDLE hThread);							//Determine state of a thread given its handle

void utinity(string userInput, string userCommand, EnvironmentVariable *Env, PROCESS_INFORMATION *processList, int *NUMBER_OF_PROCESS)
{
	if (userCommand == "date") {
		time_t now = time(0);
		char* dt = ctime(&now);
		cout << endl << "The local date and time is: " << dt << endl << endl;
	}
	else if (userCommand == "exit") {
		exit(1);
	}

	else if (userCommand == "clear") {
		system("cls");
	}

	else if (userCommand == "exitall") {
		for (int i = 0; i < *NUMBER_OF_PROCESS; ++i) {
			TerminateProcess(processList[i].hProcess, 1);
		}
		exit(1);
	}

	else if (userCommand == "dir") {
		int pivot = 0;
		vector<string> List = dir(Env->currentPath, &pivot);
		cout << endl << endl;
		printf("%-30s%-30s\n", "Categories", "Name");
		printf("%-30s%-30s\n", "------------", "-------");
		for (int i = 0; i <= pivot; ++i) {
			printf("%-30s%-30s\n", "FOLDER", List[i].c_str());
		}
		for (int i = pivot + 1; i < List.size(); ++i) {
			printf("%-30s%-30s\n", "FILE", List[i].c_str());
		}
		cout << endl << endl;
	}
	else if (userCommand == "list") {

		cout << endl << endl;
		printf("%-30s%-20s%-20s%-20s\n", "ProcessName", "ProcessID", "ThreadID", "ThreadStatus");
		printf("%-30s%-20s%-20s%-20s\n", "-------------", "-----------", "------------", "--------------");

		int n = 0;
		for (int i = 0; i < *NUMBER_OF_PROCESS; ++i) {
			ProcessInformation PI = ProcessInformations(processList[i].hProcess);
			if (PI.ThreadList.size() > 0) {
				processList[n] = processList[i];
				++n;
				printf("%-30s%-20d%-20d%-20s\n", PI.ProcessName.c_str(), PI.ID, PI.ThreadList[0].ID, PI.ThreadList[0].ThreadStatus.c_str());
				for (int j = 1; j < PI.ThreadList.size(); ++j) {
					printf("%-30s%-20s%-20d%-20s\n", "", "", PI.ThreadList[j].ID, PI.ThreadList[j].ThreadStatus.c_str());
				}

				cout << endl;
			}
		}

		*NUMBER_OF_PROCESS = n;
		cout << endl << "NUMBER_OF_PROCESS: " << n << endl;
		cout << endl << endl;
	}
	else if (userCommand == "getenv") {
		Env->print();
	}
	else if (userCommand.size() >= 11 && userCommand.substr(0, 10) == "terminate ") {
		string id = userCommand.substr(10);
		if (isInteger(id)) {
			int ProcessID = toInteger(id);
			for (int i = 0; i < *NUMBER_OF_PROCESS; ++i) {
				if (ProcessID == processList[i].dwProcessId) {
					TerminateProcess(processList[i].hProcess, 1);

					processList[i] = processList[*NUMBER_OF_PROCESS - 1];
					*NUMBER_OF_PROCESS -= 1;
					
					return;
				}
			}

			cout << endl << endl << "ERROR: " << ProcessID << " is not an ID of any process in the processList that MyShell manage!!!" << endl << endl;
		}
		else {
			cout << endl << "ERROR: " << id << " is not an integer!" << endl << endl;
		}
			
	}
	else if (userCommand.size() >= 9 && userCommand.substr(0, 8) == "suspend ") {
		string id = userCommand.substr(8);
		if (isInteger(id)) {
			int ProcessID = toInteger(id);
			for (int i = 0; i < *NUMBER_OF_PROCESS; ++i) {
				if (ProcessID == processList[i].dwProcessId) {
					ProcessInformation PI = ProcessInformations(processList[i].hProcess);

					for (int j = 0; j < PI.ThreadList.size(); ++j) {
						HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, PI.ThreadList[j].ID);
						SuspendThread(hThread);
					}
					return;
				}
			}

			cout << endl << endl << "ERROR: " << ProcessID << " is not an ID of any process in the processList that MyShell manage!!!" << endl << endl;
		}
		else {
			cout << endl << "ERROR: " << id << " is not an integer!" << endl << endl;
		}
	}
	else if (userCommand.size() >= 8 && userCommand.substr(0, 7) == "resume ") {
		string id = userCommand.substr(7);
		if (isInteger(id)) {
			int ProcessID = toInteger(id);
			for (int i = 0; i < *NUMBER_OF_PROCESS; ++i) {
				if (ProcessID == processList[i].dwProcessId) {
					ProcessInformation PI = ProcessInformations(processList[i].hProcess);

					for (int j = 0; j < PI.ThreadList.size(); ++j) {
						HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, PI.ThreadList[j].ID);
						ResumeThread(hThread);
					}
					return;
				}
			}

			cout << endl << endl << "ERROR: " << ProcessID << " is not an ID of any process in the processList that MyShell manage!!!" << endl << endl;
		}
		else {
			cout << endl << "ERROR: " << id << " is not an integer!" << endl << endl;
		}
	}
	else {
		cout << endl << "ERROR: Systax error!!! (utinity module) " << endl;
	}
}

vector<string> dir(string path, int *pivot)
{
	path += "\\*";
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	vector<string> List;
	TCHAR p[200] = {};
	for (int i = 0; i < path.size(); ++i)
		p[i] = path[i];

	hFind = FindFirstFile(p, &FindFileData);
	do
	{
		if (FindFileData.dwFileAttributes == 16) {
			List.push_back(FindFileData.cFileName);
		}
	} while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

	*pivot = (int)List.size() - 1;

	hFind = FindFirstFile(p, &FindFileData);
	do
	{
		if (FindFileData.dwFileAttributes == 32) {
			List.push_back(FindFileData.cFileName);
		}
	} while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

	return List;
}


ProcessInformation ProcessInformations(HANDLE hProcess)
{
	ProcessInformation PI;

	if (hProcess == NULL)
		return PI;

	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	HMODULE hMod;
	DWORD cbNeeded;

	if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
	{
		/******************************   FIND NAME AND ID    ***********************************/
		GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
		PI.ProcessName = szProcessName;
		PI.ID = GetProcessId(hProcess);
		/*****************************          END            ***********************************/



		/****************************   LIST THREAD AND STATUS    ********************************/
		HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
		THREADENTRY32 te32;

		// Take a snapshot of all running threads  
		hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (hThreadSnap == INVALID_HANDLE_VALUE)
			return PI;

		// Fill in the size of the structure before using it. 
		te32.dwSize = sizeof(THREADENTRY32);

		// Retrieve information about the first thread,
		// and exit if unsuccessful
		if (!Thread32First(hThreadSnap, &te32))
		{
			CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
			return PI;
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

				PI.ThreadList.push_back(ThreadInfo);
			}
		} while (Thread32Next(hThreadSnap, &te32));

		//  Don't forget to clean up the snapshot object.
		CloseHandle(hThreadSnap);
		
		return PI;
	}
}

string threadState(HANDLE hThread)
{
	DWORD result = WaitForSingleObject(hThread, 0);

	if (result == WAIT_OBJECT_0) {
		// the thread handle is signaled - the thread has terminated
		return "terminated";
	}
	else {
		// the thread handle is not signaled - the thread is still alive
		DWORD dwSuspendCount = SuspendThread(hThread);
		ResumeThread(hThread);
		if (dwSuspendCount == 0)
			return "running";
		else
			return "suspend";
	}
}
