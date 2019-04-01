#include <windows.h> 
#include <stdio.h> 
#include <iostream>
using namespace std;

PROCESS_INFORMATION *hForegroundProcess = new PROCESS_INFORMATION;	//Contain information abut current foreProcess (There are only 1 foreground process at a time)

BOOL WINAPI consoleHandler(DWORD signal) {

	hForegroundProcess->hProcess= INVALID_HANDLE_VALUE;
	if (signal == CTRL_C_EVENT) {
		if (hForegroundProcess->hProcess != INVALID_HANDLE_VALUE) {
			TerminateProcess(hForegroundProcess->hProcess, 1);
			hForegroundProcess->hProcess = INVALID_HANDLE_VALUE;
		}
	}
	return TRUE;
}
