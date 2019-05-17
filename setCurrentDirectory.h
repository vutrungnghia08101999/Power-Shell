#include"commonFunction.h"
#include<ctype.h>	
                                                               
void changeCurrentDirection(string userInput, string userCommand)
{
	//cd "     "
	if (userCommand.size() >= 6 && userCommand.find_first_of('\"') == 3 && userCommand.find_last_of('\"') == userCommand.size() - 1) {
		//cd "C:\Users\nghia.vt173284\Desktop" 
		//cd "./.."
		//cd "main"
		string path = userCommand.substr(4, userCommand.size() - 5);
		if(!SetCurrentDirectory(path.c_str()))
			printError("SetCurrentDirectory Fail");
	}
	//wrong input
	else {
		printError("Systex Error: " + userInput + " is not recognized as the name of a cmdlet, function, script file, oroperable program.Check the spelling of the name, or if a path was included, verify that the path is correct and try again.");
	}
}