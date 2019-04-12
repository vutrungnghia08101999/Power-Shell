#pragma once
#include<iostream>
using namespace std;

/*Pre: a string describes what user want to know
    - help
    - help exit 
    - help dir
    - help date
    - help list
    - help cd
    - help getenv
	- help setenv
	- help kill
	- help createprocess
Post: Show the information for each accquirement */
void help(string userCommand)
{
	if (userCommand == "help") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "help" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "Displays information about MyShell commands and concepts." << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>help" << endl;
		cout << "SUPPORT COMMAND" << endl;
		cout << "    " << " help" << endl;
		cout << "    " << " help exit" << endl;
		cout << "    " << " help dir" << endl;
		cout << "    " << " help date" << endl;
		cout << "    " << " help list" << endl;
		cout << "    " << " help cd" << endl;
		cout << "    " << " help getenv" << endl;
		cout << "    " << " help setenv" << endl;
		cout << "    " << " help kill" << endl;
		cout << "    " << " help createprocess" << endl;
		cout << endl << endl;
	}

	else if (userCommand == "help exit") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "exit" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "Terminate all the process that MyShell manage and MyShell itself" << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>exit" << endl;
		cout << endl << endl;
	}

	else if (userCommand == "help dir") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "dir" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "List all the items in the current working location" << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>dir" << endl;
		cout << "RESULT" << endl;
		cout << "                        " << "main.exe" << endl;
		cout << "                        " << "main.cpp" << endl;
		cout << "                        " << "main.o" << endl;
		cout << "                        " << "date.txt" << endl;
		cout << endl << endl;
	}

	else if (userCommand == "help date") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "date" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "return date and time" << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>date" << endl;
		cout << "RESULT" << endl;
		cout << "                        " << "Friday, March 29, 2019 1:25:49 AM" << endl;
		cout << endl << endl;
	}

	else if (userCommand == "help list") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "list" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "return all the process that is running" << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>list" << endl;
		cout << "RESULT" << endl;
		cout << "                   Index  " << "         Name       " << " ID " << "    Status   " << endl;
		cout << "                       1  " << "       VLC.exe      " << " 111" << "    Running  " << endl;
		cout << "                       2  " << "       chrome.exe   " << " 121" << "    Running  " << endl;
		cout << "                       1  " << "       explorer.exe " << " 311" << "    Running  " << endl;
		cout << endl << endl;
	}

	else if (userCommand == "help cd") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "cd: change direction" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "change direction of the current working direction" << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>cd \"C:\\Users\\nghia.vt173284\\Desktop\"" << endl;
		cout << "RESULT" << endl;
		cout << "    " << "MyShell>C:\\Users\\nghia.vt173284\\Desktop>" << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>C:\\Users\\nghia.vt173284\\Desktop>cd \"C++\"" << endl;
		cout << "RESULT" << endl;
		cout << "    " << "MyShell>C:\\Users\\nghia.vt173284\\Desktop\\C++>" << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>C:\\Users\\nghia.vt173284\\Desktop\\C++>cd ./.." << endl;
		cout << "RESULT" << endl;
		cout << "    " << "MyShell>C:\\Users\\nghia.vt173284\\Desktop>" << endl;
		cout << endl << endl;
	}

	else if (userCommand == "help getenv") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "Get Environment Variable" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "Show information about Environment Variable such as windows, path,..." << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>getenv" << endl;
		cout << "RESULT" << endl;
		cout << "		Windows                     " << "Education" << endl;
		cout << "		USERNAME                    " << "nghia.vt173284" << endl;
		cout << "		NUMBER_OF_PROCESSOR         " << "4" << endl;
		cout << endl << endl;
	}

	else if (userCommand == "help setenv") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "Set Environment Variable" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "Set Environment Variable such as path,..." << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>env:Path = env:Path + \"C:\\Users\\nghia.vt173284\\Desktop" << endl;
		cout << "RESULT" << endl;
		cout << "                   " << "A new path was added in to Environment Variable, Now you can work directly with file in this path" << endl;
		cout << endl << endl;
	}

	else if (userCommand == "help kill") {
	cout << endl << endl;
	cout << "NAME" << endl;
	cout << "    " << "kill" << endl;
	cout << "SYNOPSIS" << endl;
	cout << "    " << "Set Environment Variable such as path,..." << endl;
	cout << "CATEGORIES" << endl;
	cout << "    " << "kill ID" << endl;
	cout << "    " << "kill name" << endl;
	cout << "EXAMPLE" << endl;
	cout << "    " << "kill ID \"12324\"" << endl;
	cout << "    " << "kill name \"C:\\Users\\nghia.vt173284\\Desktop\\main.exe\"" << endl;
	cout << "RESULT" << endl;
	cout << "                   " << "C:\\Users\\vlc.exe was terminated!!" << endl;
	cout << "                   " << "C:\\Users\\nghia.vt173284\\Desktop\\main.exe was terminated!!" << endl;
	cout << endl << endl;
	}

	else if (userCommand == "help createprocess") {
		cout << endl << endl;
		cout << "NAME" << endl;
		cout << "    " << "Create Process" << endl;
		cout << "SYNOPSIS" << endl;
		cout << "    " << "Create a new process and run" << endl;
		cout << "CATEGORIES" << endl;
		cout << "    " << "fore \"path\"   : run a foreground process (.exe, .bat)" << endl;
		cout << "    " << "back \"path\"   : run a background process (.exe, .bat)" << endl;
		cout << "    " << "mysh \"path\"   : run arbitrary process such as .mp4,... but we can't manage this process" << endl;
		cout << "EXAMPLE" << endl;
		cout << "    " << "MyShell>fore \"./main.exe\" " << endl;
		cout << "    " << "MyShell>back \"C:\\Users\\nghia.vt173284\\Desktop\\main.exe\" "<< endl;
		cout << "    " << "MyShell>mysh \"C:\\users\\nghia.vt173284\\Desktop\\ignite.mp4\" " << endl;
		cout << endl << endl;
	}

	else {
	cout << endl << endl;
	cout << "This is not a internal command" << endl;
	cout << endl << endl;
	}
}