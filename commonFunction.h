#pragma once
#include "DataStructure.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <ctype.h>
using namespace std;



string toLower(string s);
bool isInteger(string s);
int toInteger(string s);
void stringToTCHAR(TCHAR *p, string s);
string TCHARToString(TCHAR *p);
bool checkPath(string path);		//Given a path. Check it exits or not
string threadState(HANDLE hThread); //Determine state of a thread given its handle

ProcessInformation ProcessInformations(HANDLE hProcess);	  //return a struct that contains all information about the process such as name, ID, Thread list and state for each thread
string ProcessName(HANDLE hProcess);						  //Given a Handle return its name
vector<ThreadAndStatus> getThreadIDAndState(HANDLE hProcess); //Given a Process Handle return a vector contain all its threadID and state for each state

vector<FileInformation> dir(string path); //return all files and folder in this path
vector<string> getenv();
string getCurrentDirectory();
void printError(string s);

//Vu Trung Nghia => vu trung nghia
string toLower(string s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (isalpha(s[i]))
			s[i] = tolower(s[i]);
	}

	return s;
}

bool isInteger(string s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (!isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}

int toInteger(string s)
{
	int number;
	istringstream iss(s);
	iss >> number;
	return number;
}

void stringToTCHAR(TCHAR *p, string s)
{
	for (int i = 0; i < s.size(); ++i)
		p[i] = s[i];
}

vector<FileInformation> dir(string path)
{

	WIN32_FIND_DATA FindFileData;
	_FILETIME timeLastWrite;
	_SYSTEMTIME convertTime;
	HANDLE hFind;
	vector<FileInformation> List;

	path += "\\*";
	TCHAR p[200] = {};
	for (int i = 0; i < path.size(); ++i)
		p[i] = path[i];

	hFind = FindFirstFile(p, &FindFileData);
	do
	{
		if (FindFileData.dwFileAttributes == 16)
		{
			timeLastWrite = FindFileData.ftLastWriteTime;
			FileTimeToSystemTime(&timeLastWrite, &convertTime);
			string date = to_string(convertTime.wDay) + '/' + to_string(convertTime.wMonth) + '/' + to_string(convertTime.wYear);
			string time = to_string(convertTime.wHour) + ':' + to_string(convertTime.wMinute) + ':' + to_string(convertTime.wSecond);
			FileInformation Folder = FileInformation(FindFileData.cFileName, "FOLDER", date, time);
			List.push_back(Folder);
		}
	} while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

	hFind = FindFirstFile(p, &FindFileData);
	do
	{
		if (FindFileData.dwFileAttributes == 32)
		{
			timeLastWrite = FindFileData.ftLastWriteTime;
			FileTimeToSystemTime(&timeLastWrite, &convertTime);
			string date = to_string(convertTime.wDay) + '/' + to_string(convertTime.wMonth) + '/' + to_string(convertTime.wYear);
			string time = to_string(convertTime.wHour) + ':' + to_string(convertTime.wMinute) + ':' + to_string(convertTime.wSecond);
			FileInformation File = FileInformation(FindFileData.cFileName, "FILE", date, time);
			List.push_back(File);
		}
	} while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

	return List;
}

string threadState(HANDLE hThread)
{
	DWORD result = WaitForSingleObject(hThread, 0);

	if (result == WAIT_OBJECT_0)
	{
		// the thread handle is signaled - the thread has terminated
		return "terminated";
	}
	else
	{
		// the thread handle is not signaled - the thread is still alive
		DWORD dwSuspendCount = SuspendThread(hThread);
		ResumeThread(hThread);
		if (dwSuspendCount == 0)
			return "running";
		else
			return "suspend";
	}
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
			CloseHandle(hThreadSnap); // Must clean up the snapshot object!
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
		CloseHandle(hThreadSnap); // Must clean up the snapshot object!
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

vector<string> getenv()
{
	vector<string> Env;
	const char *pointer = (char *)GetEnvironmentStrings();
	if (pointer == NULL)
		return Env;

	int start = 0;
	int i = 0;
	while (pointer[i] != '\0' || pointer[i + 1] != 0)
	{
		vector<string> Env;
		string s;
		LPTSTR lpszVariable;
		LPVOID lpvEnv;
		// Get a pointer to the environment block.

		lpvEnv = GetEnvironmentStrings();

		// If the returned pointer is NULL, exit.
		// Variable strings are separated by NULL byte, and the block is terminated by a NULL byte.

		for (lpszVariable = (LPTSTR)lpvEnv; *lpszVariable; lpszVariable++)
		{
			s = "";
			while (*lpszVariable)
				s.push_back(*lpszVariable++);
			Env.push_back(s);
		}

		return Env;
	}
}

string getCurrentDirectory()
{
	TCHAR NPath[MAX_PATH];
	int x = GetCurrentDirectory(MAX_PATH, NPath);
	string s = "";

	for (int i = 0; i < x; ++i)
		s.push_back(NPath[i]);
	return s;
}

void printError(string s)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	cout << endl << s << endl;
	SetConsoleTextAttribute(hConsole, 15);
}