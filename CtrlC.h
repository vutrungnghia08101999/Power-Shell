#pragma once
#include <windows.h> 
#include <stdio.h> 
#include <iostream>
using namespace std;

HANDLE hForeProcess = NULL;			//hForeProcess is the unique global variable in my program. 
									//When you type Ctrl-C. The program will create a thread run consoleHandler function 
									//and kill this process if it is possible
BOOL WINAPI consoleHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT) {
		if (hForeProcess != NULL && hForeProcess != INVALID_HANDLE_VALUE) {
			TerminateProcess(hForeProcess, 1);
		}
		hForeProcess = NULL;
		cout << "\n";
		cin.clear();
	}
	return TRUE;
}
