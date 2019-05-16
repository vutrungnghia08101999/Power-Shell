#include"commonFunction.h"

bool checkSyntax(string userCommand);		//Ensure there are only 2 (") in userCommand, s[last] = ", find_of(") < last_of(")		
		
//env: "variableName" "value"
void setEnv(string userCommand)
{
	if (!checkSyntax)
        return; 
	int index[4], count = 0;
	for(int i = 0; i < userCommand.size(); ++i){
		if(userCommand[i] == '\"'){
			index[count] = i;
			++count;
		}
	}
	string variableName = userCommand.substr(index[0] + 1, index[1] - index[0] - 1);
    string value = userCommand.substr(index[2] + 1, index[3] - index[2] - 1);

    if(!SetEnvironmentVariable(variableName.c_str(), value.c_str()))
		cout << "[ERROR: ] Can't set Environment Variable" << endl;
}


bool checkSyntax(string userCommand)
{
	int n = 0;
	for (int i = 0; i < userCommand.size(); ++i) {
		if (userCommand[i] == '\"')
			++n;
	}
	if (n != 4)
		return false;
	
	if (userCommand[(int)userCommand.size() - 1] != '\"')
		return false;

	if (userCommand.find_first_of('\"') <= 3)
		return false;
	return true;
}