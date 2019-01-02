/***
    Datical document scrubber

	File Name: datical_log_scrubber.cpp

	Purpose: A tool for customers that generate "scrubbed" versions of their their datical troubleshooting files

    @author Steve Zandany

instructions (example): 
	g++ datical_log_scrubber.cpp -o scrubberApp
	./scrubberApp jdbc: port daticaldb.log
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void findAndClean(string, string);
void removeAndRename(string);

int main(int argc, char** argv)
{
    //String to search.  string or part of string you would like to remove from your log file
	//(hint! string like 'host' or 'localhost' will remove the whole string, ie: jdbc:oracle:thin:@//localhost:####/orcl')
	string daticalDB_log = argv[argc-1];
	string originalName = "1bcfg52u#@t&6.log"; //"1bcfg56u#@t&6.log" is for security in case user didn't input file name and hit the enter key
    //Currently the keyword/s being looked for are entered manually in the sourcecode to simplify customer use experience
	//int* a = NULL;   // Pointer to int, initialize to nothing. - dynamic array during execution time

	//string strReplace[3] = {"jdbc:", "JDBC", "Development"};
	//cout << "How many strings would you like to enter? ";
    //int numNames = argc;
    //cin >> numNames;
    //string *strReplace = new string[numNames];
    //cout <<"\n(hint! string like 'host' or 'localhost' \n will remove the whole string, ie: jdbc:oracle:thin:@//localhost:####/orcl')";
    //for (int num = 0; num < numNames; ++num) {
        //cout << "\nEnter name #" << num + 1 << ": ";
        //cin >> strReplace[num];
        //cout << argv[num] << "\n";
        //strReplace[num] = argv[num];
    //}

	//cin.ignore();
	//string originalName;
    //cout << "Please enter the name of your log file: ";
    //getline (cin, daticalDB_log);
    originalName = daticalDB_log;


	//***************Here we enter the function findAndClean
	findAndClean(argv[0], daticalDB_log);
    for(int i = 1; i < argc-1; i++)
    {
    	findAndClean(argv[i],"scrubbed_" + daticalDB_log);
    	removeAndRename(originalName);
	}
    //*******************************************

    //cout << "The sensitive data had been removed from your new 'scrubbed_" <<originalName<< "' file.\n\n";
    return 0;
}


void findAndClean(string strReplace, string daticalDB_log)
{
	string line,scrubbed = "scrubbed.log", word;
	bool logFile = false;
    int line_number = 0, size = daticalDB_log.size();
    scrubbed = "scrubbed_" + daticalDB_log;
    
	if(daticalDB_log.substr(size-4) == ".log" && size > 4)
    	logFile = true;
    
	ifstream filein(daticalDB_log.c_str()); //File to read from

    if(!filein) //if file is not available
	{
        cout << "Error opening files!" << endl;
        throw exception();
    }

    ofstream fileout(scrubbed.c_str()); //create "scrubbed" file for output


	while (getline(filein, line))  //check line from datical .log file
	{
    	++line_number;
    	// put the line in an istringstream buffer
    	istringstream buffer(line);
    	// read the words from the line
    	while (buffer >> word)
    	{
    		size_t found = word.find(strReplace);
        	if((found!=string::npos && logFile == false) || (word == strReplace && logFile == true))//if your word found then replace
        	{
        		if(logFile)
        		{
        			buffer >> word;	
					fileout << "'***redacted***' ";	
			    }
        		else
             		fileout << "'***redacted***' ";//output '***redacted***' string substitution to fileout
            }
        	else
				fileout << word + " ";//output everything to fileout
    	}
    	fileout <<'\n';
	}
}

void removeAndRename(string originalName)//a function to replace previous file with current one
{
	string newName = "scrubbed_" + originalName;
	remove(newName.c_str());
	originalName = "scrubbed_" + newName;
    rename(originalName.c_str(),newName.c_str());
}

