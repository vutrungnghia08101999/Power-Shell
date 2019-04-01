#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
using namespace std;

struct ThreadAndStatus
{
	int ID;
	string ThreadStatus;
};

struct ProcessInformation
{
	string ProcessName;
	int ID;
	vector<ThreadAndStatus> ThreadList;
};

class EnvironmentVariable{
public:
    vector<string> Path;
    string currentPath;
    string USERNAME;// = "nghia.vt173284";
    string CommonProgramFiles;// = "C:\Program Files\Common Files";
    string CommonProgramFiles_x86;// = "C:\Program Files (x86)\Common Files";
    string COMPUTERNAME;// = "DESKTOP-A6CCJ7I";
    int NUMBER_OF_PROCESSORS;// = 8;
    string OS;// = "Windows_NT";

    EnvironmentVariable();
    void print();
};

void EnvironmentVariable::print()
{
	cout << endl << endl;
    printf("%-30s%-30s\n", "Name", "Value");
    printf("%-30s%-30s\n", "----", "----");
    printf("%-30s%-30s\n", "USERNAME", USERNAME.c_str());
    printf("%-30s%-30s\n", "CommonProgramFiles", CommonProgramFiles.c_str());
    printf("%-30s%-30s\n", "CommonProgramFiles_x86", CommonProgramFiles_x86.c_str());
    printf("%-30s%-30s\n", "COMPUTERNAME", COMPUTERNAME.c_str());
    printf("%-30s%-30s\n", "USENAME", USERNAME.c_str());
    printf("%-30s%-30d\n", "NUMBER_OF_PROCESSORS", NUMBER_OF_PROCESSORS);
    printf("%-30s%-30s\n", "OS", OS.c_str());
    printf("%-30s%-30s\n", "Path", Path[0].c_str());
    for(int i = 1; i < Path.size(); ++i){
        printf("%-30s%-30s\n", " ",Path[i].c_str());
    }
    printf("%-30s%-30s\n", "Current Path", currentPath.c_str());
	cout << endl << endl;
}

EnvironmentVariable::EnvironmentVariable()
{
    Path.push_back("C:\\Windows\\system32");
    Path.push_back("C:\\Windows");
    Path.push_back("C:\\Windows\\System32\\Wbem");
    Path.push_back("C:\\Windows\\System32\\WindowsPowerShell\\v1.0");
    Path.push_back("C:\\Windows\\System32\\OpenSSH");
    Path.push_back("C:\\Program Files (x86)\\Dev-Cpp\\MinGW64\\bin");
    Path.push_back("C:\\Program Files\\Java\\jdk-11.0.2\\bin");
    Path.push_back("C:\\Program Files\\Git\\cmd");
    Path.push_back("C:\\Program Files\\Microsoft SQL Server\\130\\Tools\\Binn");
    Path.push_back("C:\\Users\\nghia.vt173284\\AppData\\Local\\Programs\\Python\\Python37-32\\Scripts");
    Path.push_back("C:\\Users\\nghia.vt173284\\AppData\\Local\\Programs\\Python\\Python37-32");
    Path.push_back("C:\\Users\\nghia.vt173284\\AppData\\Local\\Microsoft\\WindowsApps");
    Path.push_back("C:\\Users\\nghia.vt173284\\AppData\\Local\\Programs\\Microsoft VS Code\\bin");
    Path.push_back("C:\\Users\\nghia.vt173284\\AppData\\Local\\Programs\\MiKTeX 2.9\\miktex\\bin\\x64");
	Path.push_back("C:\\Program Files (x86)\\Google\\Chrome\\Application");
    Path.push_back("C:\\Users\\nghia.vt173284\\Desktop");
    currentPath = "C:\\Users\\nghia.vt173284\\Desktop";
    USERNAME = "nghia.vt173284";
    CommonProgramFiles = "C:\\Program Files\\Common Files";
    CommonProgramFiles_x86 = "C:\\Program Files (x86)\\Common Files";
	COMPUTERNAME = "DESKTOP-A6CCJ7I";
    NUMBER_OF_PROCESSORS = 8;
    OS = "Windows_NT";
}




