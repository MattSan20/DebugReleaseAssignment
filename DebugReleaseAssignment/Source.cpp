#include <iostream>  // for cout
#include <fstream>   // for ifstream, reading files
#include <sstream>   // for stringstream, splitting a string apart
#include <vector>    // for vector, a resizable list
#include <string>
using namespace std;

// Groups a student's first and last name together, since they belong
// to the same person
struct STUDENT_DATA
{
    string firstName;
    string lastName;
};

int main()
{
    vector<STUDENT_DATA> students; // Vector to hold student data

    ifstream inputFile("StudentData.txt"); // Open the input file
    string line;

    // reads one line at a time until the end of the file is reached
    while (getline(inputFile, line))
    {
        stringstream ss(line); // lets us pull pieces out of this one line
        STUDENT_DATA temp;

        getline(ss, temp.firstName, ','); // everything before the comma
        getline(ss, temp.lastName);       // everything after the comma

        students.push_back(temp); // add the student data to the vector
    }

    inputFile.close(); // close the input file

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
}