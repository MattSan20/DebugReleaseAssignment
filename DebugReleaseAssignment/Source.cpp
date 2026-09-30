#include <iostream>  // for cout
#include <fstream>   // for ifstream, reading files
#include <sstream>   // for stringstream, splitting a string apart
#include <vector>    // for vector, a resizable list
#include <string>
#define PRE_RELEASE
using namespace std;

//Groups a student's first and last name together into a single string, since they belong to the same person
struct STUDENT_DATA
{
	string firstName;
	string lastName;
	string email; //Stays empty unless Pre-Release mode fills it in
};


int main()
{
	vector<STUDENT_DATA> students; // Vector to hold student data

	ifstream inputFile("StudentData.txt"); // Open the input file"
	string line;

	// reads one line at a time until the end of the file is reached
	while (getline(inputFile, line))
	{
		stringstream ss(line); //lets us pull pieces out of this one line
		STUDENT_DATA temp;

		getline(ss, temp.firstName, ','); //Everything before the comma
		getline(ss, temp.lastName); //Everything after the comma

		students.push_back(temp); // Add the student data to the vector
	}

	inputFile.close(); // Close the input file

	// _DEBUG only exists in Debug builds, so this whole block gets
	// left out entirely when compiled as Release
    #ifdef _DEBUG
	cout << "----- DEBUG MODE: Student List -----" << endl;
	for (int i = 0; i < students.size(); i++) // walk through every student
	{
		cout << students[i].firstName << " " << students[i].lastName << endl;
	}
    #endif

	return 1;

	//Reports what version is runnbing - only possible since we defined it
    #ifdef PRE_RELEASE
	cout << "Running PRE-RELEASE version" << endl;
    #else
	cout << "Running STANDARD version" << endl;
    #endif

    #ifdef PRE_RELEASE
	ifstream emailFile("StudentData_Emails.txt");
	string emailLine;
	int index = 0; //Tracks which student we're matching it with
	//matches emails to each students by line position
	//assuming both files list students in the same order
	while (getline(emailFile, emailLine) && index < students.size())
	{
		students[index].email = emailLine;
		index++;
	}

	emailFile.close();
    #endif // PRE_RELEASE




	//_Debug only exists in Debug builds, so the whole block gets left out when compiled as Release. 
    #ifdef _DEBUG
	cout << "----- Debug Mode: List of Students -----" << endl;
	for (int i = 0; i < students.size(); i++) //Walk through every student in the list
	{
		cout << students[i].firstName << "" << students[i].lastName;
		
		//only prints an email if there actually is one loaded (PRE RELEASE MODE)
		if (!students[i].email.empty())
		{
			cout << " - " << students[i].email;
		}
		cout << endl;
	}
    #endif // _DEBUG

	
	return 1;
}