#include"CtrlC.h"
#include"commonFunction.h"
#include"EnvironmentVariable.h"
using namespace std;

void newProcess(string userInput, string userCommand, STARTUPINFO *startUpInfor, PROCESS_INFORMATION *processList, EnvironmentVariable *Env, int *NUMBER_OF_PROCESS)
{
	int n = userCommand.size();
	if (userCommand.size() >= 9 && userCommand.find_first_of('\"') == 5 && userCommand.find_last_of('\"') == userCommand.size() - 1) {

		/******************************************************************************************************/
		string path = userCommand.substr(6, n - 7);
		string correctPath;

		bool checkPathExist = false;
		if (checkPath(path)) 		//		C:\Users\nghia.vt173284\Desktop\main.exe
			correctPath = path;
		else {						//		./main.exe
			path = path.substr(2);
			string checkCurrentPath = Env->currentPath + "\\" + path;
			if (checkPath(checkCurrentPath))
				correctPath = checkCurrentPath;

			else {
				string checkPathEnv;
				for (int i = 0; i < Env->Path.size(); ++i) {
					checkPathEnv = Env->Path[i] + "\\" + path;
					if (checkPath(checkPathEnv)) {
						correctPath = checkPathEnv;
						checkPathExist = true;
						break;
					}
				}

				if (checkPathExist == false) {
					cout << endl << endl << "[ERROR]: " << path << " is not exist!!!" << endl << endl;
					return;
				}
			}
		}
		/*********************************************************************************************************/

		string Categories = path.substr(path.size() - 3);

		correctPath = correctPath;
		string appPath;

		bool checkSucceed = false;
		if (Categories == "exe" || Categories == "bat") {
			//Do nothing
		}
		else if (Categories == "mp4") {
			appPath = "C:\\Program Files\\VideoLAN\\VLC\\vlc.exe";
			correctPath = "/c " + correctPath;
		}
		else if (Categories == "pdf") {
			appPath = "C:\\Program Files (x86)\\Foxit Software\\Foxit Reader\\foxitreader.exe";
			correctPath = "/c " + correctPath;
		}
		else if (Categories == "doc") {
			appPath = "C:\\Program Files\\Microsoft Office\\root\\Office16\\winword.exe";
			correctPath = "/c " + correctPath;
		}
		else if (Categories == "png" || Categories == "jpg") {
			appPath = "C:\\Program Files\\Windows Media Player\\wmplayer.exe";
			correctPath = "/c " + correctPath;
		}
		else {
			//There are some problem with this module. Shell can't open cpp, txt, ... file by subtime text
			appPath = "C:\\Program Files\\Sublime Text 3\\sublime_text.exe";
			correctPath = "/c " + correctPath;
		}

		TCHAR p1[200] = {};
		stringToTCHAR(p1, correctPath);
		TCHAR p2[200] = {};
		stringToTCHAR(p2, appPath);

		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);

		if (appPath.size() == 0) {
			if (!CreateProcess(NULL, p1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
				cout << endl << endl << "[ERROR]: " << path << " is not exist!!!" << endl << endl;
				return;
			}
		}
		else {
			if (!CreateProcess(p2, p1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
				cout << endl << endl << "[ERROR]: " << path << " is not exist1111!!!" << endl << endl;
				return;
			}
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
		cout << endl << "Systex Error: " << userInput << " is not recognized as the name of a cmdlet, function, script file, oroperable program.Check the spelling of the name, or if a path was included, verify that the path is correct and try again." << endl;
	}
}
	