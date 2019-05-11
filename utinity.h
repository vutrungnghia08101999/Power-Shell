#include"commonFunction.h"
#include"EnvironmentVariable.h"
#include<ctime>
#include<tlhelp32.h>
#include<tchar.h>
#include<psapi.h>
#include<ctype.h>

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
		vector<FileInformation> List = dir(Env->currentPath);
		cout << endl << endl;
		printf("%-15s%-15s%-15s%-30s\n", "Categories", "Date", "Time", "Name");
		printf("%-15s%-15s%-15s%-30s\n", "-----------", "-------", "------", "---------");

		for (int i = 0; i < List.size(); ++i)
			printf("%-15s%-15s%-15s%-30s\n", List[i].categories.c_str(), List[i].dateLastWrite.c_str(), List[i].timeLastWrite.c_str(), List[i].name.c_str());
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
