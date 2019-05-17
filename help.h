#include<iostream>
using namespace std;

void help(string userCommand)
{
	cout << endl << "My Shell includes 8 module:" << endl << endl;
	printf("	- Help\n");
	printf("	- New Process\n");
	printf("	- Set Current Directory\n");
	printf("	- Set Environment Variable\n");
	printf("	- Utinity\n");
	printf("	- Additional Function\n");
	printf("	- Ctrl-C\n");
	printf("	- Wrong input\n");

	cout << endl << "I. Help Module" << endl << endl;
	printf("	- Describe the structure of the Shell and all support command in Shell\n\n");
	printf("	help\n");

	cout << endl << "II. New Process Module" << endl << endl;
	printf("	- Create new process type .exe, .bat\n\n");
	printf("	1. Create back ground process: \n");
	printf("		back \"main.exe\"\n");
	printf("		back \"C:\\Users\\nghia.vt173284\\Desktop\\main.exe\"\n");
	printf("	2. Create fore ground process: \n");
	printf("		fore \"main.exe\"\n");
	printf("		fore \"C:\\Users\\nghia.vt173284\\Desktop\\main.exe\"\n");

	cout << endl << "III. Set Current irectory" << endl << endl;
	printf("	- Change current path\n\n");
	printf("	cd \"./..\"\n");
	printf("	cd \"main\"\n");
	printf("	cd \"C:\\Users\\nghia.vt173284\\Desktop\\main\"\n");

	cout << endl << "IIII. Set environment Variable" << endl << endl;
	printf("	- Change environment variable\n\n");
	printf("	env: \"VariablName\" \"Value\"\n");

	cout << endl << "V. Unitity Module" << endl << endl;
	printf("	- Some command to support Shell\n\n");
	printf("	date\n");
	printf("	dir\n");
	printf("	list\n");
	printf(" 	clear\n");
	printf("	exit\n");
	printf("	exitall\n");
	printf("	getenv\n");
	printf("	getenv \"VariableName\"\n");
	printf("	terminate ProcessID\n");
	printf("	resume ProcessID\n");
	printf("	suspend ProcessID\n");
	
	cout << endl << "VI. Additional Function" << endl << endl;
	printf("	- Allow Shell to manage all the processes in the computer\n\n");
	printf("	listall\n");
	printf("	listthread ProcessID\n");
	printf("	suspendadd ProcessID\n");
	printf("	resumeadd ProcessID\n");
	printf("	terminateadd Process ID\n");

	cout << endl << "VII. Ctrl-C Module" << endl << endl;
	printf("	- Handle Ctrl-C signal\n");
	printf("	- Terminate a foreground process\n\n");

	cout << endl << "VIII. Wrong Input Module" << endl << endl;
	printf("	- Print message error\n\n");
}