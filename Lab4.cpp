/*
Natalia Kellerman 
C++ 2021
Due: Wednesday, October 13th
Lab 4 Temperature Output 
Design and write a C++ program that inputs a series of hourly temperature from a file, 
and outputs a bar chart (using stars) of the temperatures.
Pg. 300
*/


#include <iostream>
#include <fstream> //File I/O
#include <string> //c++ string method to store stars in a string
#include <iomanip> //Formating graph
#include <cctype> //Used for error checking

using namespace std;

//Function Prototypes.

int ErrorCheck(ifstream& inFile);
//Precondition: File name that user types in able to be found.
//Postcondition: All data in the input file is error free (correct data type) and can be used to print the graph.

void PrintGraph(ifstream& inFile, string fileName);
//Precondition: Input file has appropriate data.
//Postcondition: Print bar graph representing temperatures over 24 hours.

int main()
{
	ifstream inFile;
	string fileName;

	//Following do-while prompts user for filename.
	do
	{
		cout << "Enter the name of your input file: ";
		cin >> fileName;
		inFile.open(fileName.c_str());

		if (!inFile)
		{
			cout << "Input file failed to open. Make sure you typed its name correctly and that the input file exists.\n";
			cout << "Try again or press 'Q' to quit: ";
			cin >> fileName;
			cout << endl << endl << endl;

			if (fileName == "Q" || fileName == "q") //User terminates program. 
			{
				cout << "Program Closing" << endl;
				return 1; //User terminates program.
			}
			inFile.open(fileName.c_str());
		}
	} while (!inFile);


	/*
	ErrorCheck is a value returning integer function.
	It returns 1 if an error is present, so the if statement terminates the program if the call is equal to 1
	*/
	if (ErrorCheck(inFile) == 1)
	{
		return 1;
	}

	//Print graph reads data in from the input file, determines how many stars are needed, and then prints the graph to the screen.
	PrintGraph(inFile, fileName);

	return 0;
}


//This function makes sure all the characters in the input file are valid
int ErrorCheck(ifstream& inFile)
{
	char errorCheck;
	//Priming read for vetting values in input file
	inFile >> errorCheck;

	//While loop will run through all the data and make sure all data types are valid
	while (inFile)
	{
		if (isalpha(errorCheck)) //isalpha checks if value is alphabetical.
		{
			
			cout << "The input stream has encountered an invalid input type " << "'" << errorCheck << "'" << " in the input stream." << endl;
			cout << "Make sure the input file only includes integers or float values" << endl;
		
			return 1;
		}
		inFile >> errorCheck;
	}
	inFile.close();
	return 0;
}

void PrintGraph(ifstream& inFile, string fileName)
{
	float temp;


	//Makes the Graph title
	cout << endl << endl << "Temperatures for 24 hours: " << endl;
	cout << setw(8) << "-30" << setw(8) << "0" << setw(10) << "30" << setw(10) << "60" << setw(10) << "90" << setw(10) << "120" << endl;

	inFile.open(fileName.c_str());
	inFile >> temp;

	while (inFile)
	{
		temp = ceil(temp); //Ceil rounds decimals to whole numbers 

		string starOutput; //Stores stars
		starOutput = ""; //Resets the string

		//takes out any temperatures out of range
		if (temp < -30 || temp > 120) 
		{ 
			inFile >> temp;
			continue; //Tells compiler to skip body of loop and return to loop condition of first for loop.

		}
		else { //temp in range
			cout << temp << ":";
		}

		//makes the right amount of stars
		for (int i = 1; i <= (abs(temp) / 3.0); ++i) //abs() is used to calculate values for negative inputs.
		{
			starOutput.append("*"); //Appends a star to a string called starOutput every time the loop iterates.
		}

		//Following if else ladder prints the corressponding temperature and number of stars associated with that value
		if (temp == -30) {
			cout << setw(12) << starOutput + "|";
		}
		else if (temp > -30 && temp <= -10) {
			cout << setw(12) << starOutput + "|";
		}
		else if (temp > -10 && temp < 0) {
			cout << setw(13) << starOutput + "|";
		}
		else if (temp >= 0 && temp < 10) {
			cout << setw(14) << "|" << starOutput;
		}
		else if (temp >= 10 && temp < 100) {
			cout << setw(13) << "|" << starOutput;
		}
		else if (temp >= 100 && temp <= 120) {
			cout << setw(12) << "|" << starOutput;
		}

		cout << endl;
		inFile >> temp;
	}

	cout << "* = 3 degrees";
	
	inFile.close();
}







