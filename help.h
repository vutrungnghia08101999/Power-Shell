#include<iostream>
using namespace std;

void help(string userCommand)
{
	cout << endl << "My Shell includes 8 module:" << endl << endl;
	printf("	- Help\n");
	printf("	- New Process\n");
	printf("	- Change Current Working Direction\n");
	printf("	- Change Environment Variable\n");
	printf("	- Utinity\n");
	printf("	- Additional Function\n");
	printf("	- Ctrl-C\n");
	printf("	- Wrong input\n");

	cout << endl << "I. Help Module" << endl << endl;
	printf("	- Describe the structure of the Shell and all support command in Shell\n\n");
	printf("	help\n");

	cout << endl << "II. New Process Module" << endl << endl;
	printf("	- Create new process type .exe, .bat, .mp4, .png,...\n\n");
	printf("	1. Create back ground process: \n");
	printf("		back \"./main.exe\"\n");
	printf("		back \"C:\\Users\\nghia.vt173284\\Desktop\\main.exe\"\n");
	printf("	2. Create fore ground process: \n");
	printf("		fore \"./main.exe\"\n");
	printf("		fore \"C:\\Users\\nghia.vt173284\\Desktop\\main.exe\"\n");

	cout << endl << "III. Change Current Working Direction" << endl << endl;
	printf("	- Change current path\n\n");
	printf("	cd ./..\n");
	printf("	cd \"main\"\n");
	printf("	cd \"C:\\Users\\nghia.vt173284\\Desktop\\main\"\n");

	cout << endl << "IIII. Change environment Variable" << endl << endl;
	printf("	- Change environment variable\n\n");
	printf("	env: [variable name] = [\"new value\"]\n");
	printf("	env: path += [\"new path\"]\n");
	printf("	end: path -= [\"an element in path\"]\n");
	printf("	env: number_of_processors = 10\n");

	cout << endl << "V. Unitity Module" << endl << endl;
	printf("	- Some command to support Shell\n\n");
	printf("	date\n");
	printf("	dir\n");
	printf("	list\n");
	printf(" 	clear\n");
	printf("	exit\n");
	printf("	exitall\n");
	printf("	getenv\n");
	printf("	terminate [Process ID]\n");
	printf("	resume [Process ID]\n");
	printf("	suspend [Process ID]\n");
	
	cout << endl << "VI. Additional Function" << endl << endl;
	printf("	- Allow Shell to manage all the processes in the computer\n\n");
	printf("	listall\n");
	printf("	listthread [Process ID]\n");
	printf("	suspendadd [Process ID]\n");
	printf("	resumeadd [Process ID]\n");
	printf("	terminateadd [Process ID]\n");

	cout << endl << "VII. Ctrl-C Module" << endl << endl;
	printf("	- Handle Ctrl-C signal\n\n");

	cout << endl << "VIII. Wrong Input Module" << endl << endl;
	printf("	- print message error\n\n");
}