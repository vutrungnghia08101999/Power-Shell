#include"commonFunction.h"
#include"EnvironmentVariable.h"

bool checkSyntax(string userCommand);		//Ensure there are only 2 (") in userCommand, s[last] = ", find_of(") < last_of(")		
		
void changeEnv(string userCommand, EnvironmentVariable *Env)
{
	if (checkSyntax) {

		//Take the first of command EX: env:path += "C:\Users\nghia.vt173284\Desktop" => variable = "env:path+="
		string variable;
		int start = userCommand.find_first_of('\"');
		int last = (int)userCommand.size() - 1;
		for (int i = 0; i < start; ++i) {
			if (userCommand[i] != ' ')
				variable.push_back(userCommand[i]);
		}

		string s = userCommand.substr(start + 1, last - start - 1);

		if (variable == "env:path-=") {
			for (int i = 0; i < Env->Path.size(); ++i) {
				if (toLower(Env->Path[i]) == toLower(s)) {
					Env->Path[i] = Env->Path[(int)Env->Path.size() - 1];
					Env->Path.pop_back();
					return;
				}
			}

			cout << endl << s << " is not exist in path!!!" << endl;
			return;
		}
		if (variable == "env:path+="){
			if(checkPath(s))
				Env->Path.push_back(s);
			else
				cout << s << " is not exist!!!" << endl;
		}
		else if (variable == "env:currentpath="){
			if(checkPath(s))
				Env->Path.push_back(s);
			else
				cout << s << " is not exist!!!" << endl;
		}
		else if (variable == "env:username=")
			Env->USERNAME = s;
		else if (variable == "env:programfiles=")
			Env->CommonProgramFiles = s;
		else if (variable == "env:programfiles_x86=")
			Env->CommonProgramFiles_x86 = s;
		else if (variable == "env:computername=")
			Env->COMPUTERNAME = s;
		else if (variable == "env:os=")
			Env->OS = s;
		else {
			cout << endl << "ERROR: Syntax error!!! (Environment Variable1)" << endl;
		}
	}
	else {
		cout << endl << "ERROR: Syntax error!!! (Environment Variable2)" << endl;
	}
}


bool checkSyntax(string userCommand)
{
	int n = 0;
	for (int i = 0; i < userCommand.size(); ++i) {
		if (userCommand[i] == '\"')
			++n;
	}
	if (n != 2)
		return false;

	if (userCommand[(int)userCommand.size() - 1] != '\"')
		return false;

	int start = userCommand.find_first_of('\"');

	if (start >= (int)userCommand.size() - 2)
		return false;
	return true;
}

