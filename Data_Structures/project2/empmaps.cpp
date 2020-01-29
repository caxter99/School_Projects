// This is the empmaps.cpp file for Project 2
// Devin Hopkins
// 4190350

#include "empmaps.h"

vector<Employee> employees()
{
    // Creating the ifstream object to collect the data, the vector of employees, and the filename
    ifstream inFile;
    vector<Employee> employeeVector;
    string filename = "";

    // Getting the filename from the user
    cout << "Enter the filename you would like to process: ";
    getline(cin, filename);

    // Removing the whitespace from the filename since there shouldn't be any
    filename = removeWhitespace(filename);

    // Opening the file
    inFile.open(filename);

    // If the file couldn't be opened, then the user is told and the program throws an exception
    if (!inFile)
    {
        cout << "The file " << filename << " could not be opened.\nAn excpetion will now be thrown to end the program.\n" << endl;
        throw exception();
    }
    // If the file was open, then the program starts it's magic
    else
    {
        // Creating the line that will be used to gather each line of the file
        string line = "";

        // This loop gathers each line of the file, one at a time
        while (getline(inFile, line))
        {
            // This is making sure the length of the line is long enough to actually hold all of the data required.
            // If it's not, then the program doesn't try and gather anything from the line
            if (line.length() > 13)
            {
                // Getting the identifier
                int identifier = stoi(line.substr(0, line.find("\t")));

                // Getting the lastname
                line = line.substr(line.find("\t") + 1);
                string lastname = line.substr(0, line.find("\t"));

                // Getting the salary
                line = line.substr(line.find("\t") + 1);
                int salary = stoi(line);

                // Creating the new employee and pushing it onto the vector
                Employee newEmp{identifier, lastname, salary};
                employeeVector.push_back(newEmp);
            }
        }
    }

    // Closing the file
    inFile.close();

    // Saying how many employees there are
    cout << "Number of employees are: " << employeeVector.size() << endl;

    // Returning the employee vector
    return employeeVector;
}

map<int,vector<Employee>> mapEmpDept(vector<Employee>& emp)
{
    // Declaring the clock
    clock_t start = clock();
    cout << "ORDERED Map creation with department as key clock ticks: " << double(start) << endl;

    // Declaring the map
    map<int, vector<Employee>> departmentMap;

    // This loop will go through the entire employee vecotr and put them into the dapertment map
    for (vector<Employee>::iterator vIter = emp.begin(); vIter != emp.end(); ++vIter)
    {
        // Getting the department (the key for the map)
        int firstFour = (*vIter).id() / 100;

        // Adding the employee into the map
        departmentMap[firstFour].push_back(*vIter);
    }

    // Showing how much time was taken in terms of clock ticks to perform this function
    clock_t stop = clock();
    cout << "ORDERED Map number of departments: " << double(stop - start) << endl;

    // Returning the map
    return departmentMap;
}

map<int,vector<Employee>> mapSalRange(vector<Employee>& emp)
{
    // Declaring the clock
    clock_t start = clock();
    cout << "ORDERED Map creation with salary as key clock ticks: " << double(start) << endl;

    // Declaring the map
    map<int, vector<Employee>> salaryMap;

    // This loop will go through the entire employee vector and put them into the salary map
    for (vector<Employee>::iterator vIter = emp.begin(); vIter != emp.end(); ++vIter)
    {
        // Getting the department (the key for the map)
        int salary = (*vIter).sal();

        // Setting the key to be in increments of 10,000
        // < 10,000
        if (salary < 10000)
        {
            salary = 0;
        }
        // < 20,000
        else if (salary < 20000)
        {
            salary = 10000;
        }
        // < 30,000
        else if (salary < 30000)
        {
            salary = 20000;
        }
        // < 40,000
        else if (salary < 40000)
        {
            salary = 30000;
        }
        // < 50,000
        else if (salary < 50000)
        {
            salary = 40000;
        }
        // < 60,000
        else if (salary < 60000)
        {
            salary = 50000;
        }
        // < 70,000
        else if (salary < 70000)
        {
            salary = 60000;
        }
        // < 80,000
        else if (salary < 80000)
        {
            salary = 70000;
        }
        // < 90,000
        else if (salary < 90000)
        {
            salary = 80000;
        }
        // < 100,000
        else if (salary < 100000)
        {
            salary = 90000;
        }
        // < 110,000
        else if (salary < 110000)
        {
            salary = 100000;
        }
        // < 120,000
        else if (salary < 120000)
        {
            salary = 110000;
        }
        // < 130,000
        else if (salary < 130000)
        {
            salary = 120000;
        }
        // < 140,000
        else if (salary < 140000)
        {
            salary = 130000;
        }
        // < 150,000
        else if (salary < 150000)
        {
            salary = 140000;
        }
        // < 160,000
        else if (salary < 160000)
        {
            salary = 150000;
        }
        // < 170,000
        else if (salary < 170000)
        {
            salary = 160000;
        }
        // < 180,000
        else if (salary < 180000)
        {
            salary = 170000;
        }
        // < 190,000
        else if (salary < 190000)
        {
            salary = 180000;
        }
        // < 200,000
        else if (salary < 200000)
        {
            salary = 190000;
        }
        // > 200,000
        else
        {
            salary = 200000;
        }

        // Adding the employee into the map
        salaryMap[salary].push_back(*vIter);
    }

    // Showing how much time was taken in terms of clock ticks to perform this function
    clock_t stop = clock();
    cout << "ORDERED Map number of salary ranges: " << double(stop - start) << endl;

    // Returning the map
    return salaryMap;
}

void printSalRange(map<int,vector<Employee>>& salRange)
{
    /*
    // Keeps track of the key for the largest amount of people
    int largestKey = 0;

    // Loops through the map and shows the total number of people and detects the largest group
    for (auto mapItem : salRange)
    {
        // Prints out the data
        cout << "ORDERED: Map Salary Range " << mapItem.first << " contains " << mapItem.second.size() << endl;
        // ORDERED Map Salary Range 150000 contains 6241

        // Checks to see if the current vector size is greater than the current largest
        if (salRange[largestKey].size() < mapItem.second.size())
        {
            largestKey = mapItem.first;
        }
    }

    // Printing out the largest range
    cout << "ORDERED: Map Salary Range with most employees: " << largestKey << " containing " << salRange[largestKey].size() << " employees." << endl;
    */

    // Iterator with the largest value
    map<int,vector<Employee>>::iterator largestIter = salRange.begin();

    // This loop will go through the entire map and print everything out, along with finding the largest vector in the map
    for (map<int,vector<Employee>>::iterator mIter = salRange.begin(); mIter != salRange.end(); ++mIter)
    {
        // Prints out the data
        cout << "ORDERED: Map Salary Range " << (*mIter).first << " contains " << (*mIter).second.size() << endl;

        // Seeing if the current iterator contain the largest amount of people
        if ((*largestIter).second.size() < (*mIter).second.size())
        {
            largestIter = mIter;
        }
    }

    // Printing out the largest range
    cout << "ORDERED: Map Salary Range with most employees: " << (*largestIter).first << " containing " << (*largestIter).second.size() << " employees." << endl;
}

unordered_map<int,vector<Employee>> umapEmpDept(vector<Employee>& emp)
{
    // Declaring the clock
    clock_t start = clock();
    cout << "UNORDERED Map creation with department as key clock ticks: " << double(start) << endl;
    
    // Declaring the unordered map
    unordered_map<int, vector<Employee>> departmentMap;

    // This loop will go through the entire employee vecotr and put them into the unordered dapertment map
    for (vector<Employee>::iterator vIter = emp.begin(); vIter != emp.end(); ++vIter)
    {
        // Getting the department (the key for the map)
        int firstFour = (*vIter).id() / 100;

        // Adding the employee into the unordered map
        departmentMap[firstFour].push_back(*vIter);
    }

    // Showing how much time was taken in terms of clock ticks to perform this function
    clock_t stop = clock();
    cout << "UNORDERED Map number of departments: " << double(stop - start) << endl;

    // Returning the unordered map
    return departmentMap;
}

unordered_map<int,vector<Employee>> umapSalRange(vector<Employee>& emp)
{
    // Declaring the clock
    clock_t start = clock();
    cout << "UNORDERED Map creation with salary as key clock ticks: " << double(start) << endl;
    
    // Declaring the unordered map
    unordered_map<int, vector<Employee>> salaryMap;

    // This loop will go through the entire employee vector and put them into the salary unordered map
    for (vector<Employee>::iterator vIter = emp.begin(); vIter != emp.end(); ++vIter)
    {
        // Getting the department (the key for the unordered map)
        int salary = (*vIter).sal();

        // Setting the key to be in increments of 10,000
        // < 10,000
        if (salary < 10000)
        {
            salary = 0;
        }
        // < 20,000
        else if (salary < 20000)
        {
            salary = 10000;
        }
        // < 30,000
        else if (salary < 30000)
        {
            salary = 20000;
        }
        // < 40,000
        else if (salary < 40000)
        {
            salary = 30000;
        }
        // < 50,000
        else if (salary < 50000)
        {
            salary = 40000;
        }
        // < 60,000
        else if (salary < 60000)
        {
            salary = 50000;
        }
        // < 70,000
        else if (salary < 70000)
        {
            salary = 60000;
        }
        // < 80,000
        else if (salary < 80000)
        {
            salary = 70000;
        }
        // < 90,000
        else if (salary < 90000)
        {
            salary = 80000;
        }
        // < 100,000
        else if (salary < 100000)
        {
            salary = 90000;
        }
        // < 110,000
        else if (salary < 110000)
        {
            salary = 100000;
        }
        // < 120,000
        else if (salary < 120000)
        {
            salary = 110000;
        }
        // < 130,000
        else if (salary < 130000)
        {
            salary = 120000;
        }
        // < 140,000
        else if (salary < 140000)
        {
            salary = 130000;
        }
        // < 150,000
        else if (salary < 150000)
        {
            salary = 140000;
        }
        // < 160,000
        else if (salary < 160000)
        {
            salary = 150000;
        }
        // < 170,000
        else if (salary < 170000)
        {
            salary = 160000;
        }
        // < 180,000
        else if (salary < 180000)
        {
            salary = 170000;
        }
        // < 190,000
        else if (salary < 190000)
        {
            salary = 180000;
        }
        // < 200,000
        else if (salary < 200000)
        {
            salary = 190000;
        }
        // > 200,000
        else
        {
            salary = 200000;
        }

        // Adding the employee into the unordered map
        salaryMap[salary].push_back(*vIter);
    }

    // Showing how much time was taken in terms of clock ticks to perform this function
    clock_t stop = clock();
    cout << "UNORDERED Map number of salary ranges: " << double(stop - start) << endl;

    // Returning the unordered map
    return salaryMap;
}

void uprintSalRange(unordered_map<int,vector<Employee>>& salRange)
{
    /*
    // Keeps track of the key for the largest amount of people
    int largestKey = 0;

    // Loops through the map and shows the total number of people and detects the largest group
    for (auto mapItem : salRange)
    {
        // Prints out the data
        cout << "UNORDERED: Map Salary Range " << mapItem.first << " contains " << mapItem.second.size() << endl;
        // UNORDERED Map Salary Range 150000 contains 6241

        // Checks to see if the current vector size is greater than the current largest
        if (salRange[largestKey].size() < mapItem.second.size())
        {
            largestKey = mapItem.first;
        }
    }

    // Printing out the largest range
    cout << "UNORDERED: Map Salary Range with most employees: " << largestKey << " containing " << salRange[largestKey].size() << " employees." << endl;
    */

    // Iterator with the largest value
    unordered_map<int,vector<Employee>>::iterator largestIter = salRange.begin();

    // This loop will go through the entire unordered map and print everything out, along with finding the largest vector in the unordered map
    for (unordered_map<int,vector<Employee>>::iterator mIter = salRange.begin(); mIter != salRange.end(); ++mIter)
    {
        // Prints out the data
        cout << "UNORDERED: Map Salary Range " << (*mIter).first << " contains " << (*mIter).second.size() << endl;

        // Seeing if the current iterator contain the largest amount of people
        if ((*largestIter).second.size() < (*mIter).second.size())
        {
            largestIter = mIter;
        }
    }

    // Printing out the largest range
    cout << "UNORDERED: Map Salary Range with most employees: " << (*largestIter).first << " containing " << (*largestIter).second.size() << " employees." << endl;
}

// PLEASE NOTE
// The following functions are not a part of the project requirements. I put them in because I wanted to. Their affects on the program
// can be commented out and the program's effectiveness will not change. If you would like to comment them out, they are used in line 19

string removeWhitespace(string whitespace)
{
    // Declaring all the variables needed
    string toReturn = "";
    bool complete = false;
    int spot = 0;

    // This loop goes until each of the characters of the string whitespace have been looked at
    while (!complete)
    {
        // Checking to make sure that the character is a legit acharacter and isn't a space
        if (!(getASCIIValue(whitespace.at(spot)) == 32) && getASCIIValue(whitespace.at(spot)) < 127)
        {
            toReturn += whitespace.at(spot);
        }

        // Incrementing the spot
        ++spot;

        // Making sure the spot is still valid
        if (spot >= whitespace.length())
        {
            complete = true;
        }
    }

    // Returning the string without any whitepsace
    return toReturn;
}

int getASCIIValue(char character)
{
    return (int)character;
}