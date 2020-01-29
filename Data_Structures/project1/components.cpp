// This is the components file for Project 1
// Devin Hopkins
// 4190350

// List of things that must be included
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

// Headers
void getData(std::string filename, std::vector<std::list<int>> &adjList);
void seeRoot(std::vector<std::list<int>> &adjList);
void printAdjList(std::list<int> &regList);
std::list<int>::iterator find_gt(std::list<int>::iterator start, std::list<int>::iterator stop, int x);
bool merge2(std::list<int> &shorterList, std::list<int> &longerList);

// These function headers are not part of the assignment, I just made them for myself
bool connComponent(const std::list<int> &listOne, const std::list<int> &listTwo);
int getASCIIValue(char character);
bool validateMergeListResponse(std::string response);
std::string removeWhitespace(std::string whitespace);


int main(int argc, char const *argv[])
{
    // Vector of integer lists called adjList for adjacency list
    std::vector<std::list<int>> adjList;

    // Getting the filename they would like to process
    std::cout << "Enter the graph filename to process: ";
    std::string filename = "";
    std::getline(std::cin, filename);

    // creating the FileManager object
    getData(filename, adjList);

    // Creating the input string
    std::string input = "";

    do {
        // Letting the user see the data
        seeRoot(adjList);

        // Getting the prompt from the user
        std::cout << "\nEnter two lists ids to potentially merge together or -1 to quit: ";
        std::getline(std::cin, input);

        // Cleaning up the user's response
        input = removeWhitespace(input);

        // This means they don't want to quit and their input was valid
        if(validateMergeListResponse(input) && input.compare("-1") != 0)
        {
            // Getting the numbers they input
            int spaceLoc = input.find(" ");
            int firstListInt = stoi(input.substr(0, spaceLoc));
            int secondListInt = stoi(input.substr(spaceLoc + 1));

            // Making sure that that they actually put in a list
            if (firstListInt > adjList.size() - 1 || secondListInt > adjList.size() - 1)
            {
                std::cout << "That is not a valid response." << std::endl;
            }
            // If both of their lists check out, then we're good to go
            else
            {
                // Checking to see if the two lists they put in can actually be merged
                if (merge2(adjList[firstListInt], adjList[secondListInt]))
                {
                    // Deleting the empty list
                    if (adjList[firstListInt].empty())
                    {
                        adjList.erase(adjList.begin() + firstListInt);
                    }
                    else
                    {
                        adjList.erase(adjList.begin() + secondListInt);
                    }

                    // Letting the user know the lists were merged
                    std::cout << "The lists are merged." << std::endl;
                }
                else
                {
                    std::cout << "The lists are not merged." << std::endl;
                }
            }
        }
        // This means their response wasn't valid but they didn't want to quit
        else if (!(validateMergeListResponse(input)))
        {
            std::cout << "That is not a valid response." << std::endl;
        }

    } while(input.compare("-1") != 0);

    return 0;
}

void getData(std::string filename, std::vector<std::list<int>> &adjList)
{
    // Creating the ifstream object
    std::ifstream infile;

    // Attempting to open the file
    infile.open(filename);

    // This checks to see if the file was successfully opened of not
    if (!infile)
    {
        // If not, the user is told
        std::cout << "The file, \"" << filename << "\", failed to open. Please make sure you entered the name correctly." << std::endl;
    }
    // This code will only execute if the file opened successfully
    else
    {
        // This is the line reading variable
        std::string line = "";

        // This is the integer holding variable
        int data = 0;

        // This is to keep track of what vector we're on
        // Starts at -1 because the first thing we do is increment it
        int vectorNum = -1;

        // Reading the file line by line
        while (std::getline(infile, line))
        {

            // Creating the list of integers
            // List for all the integers
            std::list<int> intList;

            // Adding the new list to the vector and incrementing the vectorNum by 1
            ++vectorNum;
            adjList.push_back(intList);

            while(line.find(" ") != -1)
            {
                // Getting the first number
                data = stoi(line.substr(0, line.find(" ")));

                // Checking to see if the list is empty
                if (adjList[vectorNum].empty())
                {
                    // If it's empty, just push it into the list
                    adjList[vectorNum].push_back(data);
                }
                // If it's not, then find out where it needs to go and put it there
                else
                {
                    // Getting the iterator to know where to insert the data
                    std::list<int>::iterator newInsert = find_gt(adjList[vectorNum].begin(), adjList[vectorNum].end(), data);

                    // If the new pointer points to the end of the list, then just push the data in
                    if (newInsert == intList.end())
                    {
                        adjList[vectorNum].push_back(data);
                    }
                    // If it doesn't, then insert it
                    else
                    {
                        adjList[vectorNum].insert(newInsert, data);
                    }
                }

                // This cuts out the number that was just added
                line = line.substr(line.find(" ") + 1);
            }

            // This gets the last piece of data in the line
            data = stoi(line);

            // Getting the iterator to know where to insert the data
            std::list<int>::iterator newInsert = find_gt(adjList[vectorNum].begin(), adjList[vectorNum].end(), data);

            // If the new pointer points to the end of the list, then just push the data in
            if (newInsert == intList.end())
            {
                adjList[vectorNum].push_back(data);
            }
            // If it doesn't, then insert it
            else
            {
                adjList[vectorNum].insert(newInsert, data);
            }
        }
    }

    // Closing the file
    infile.close();
}

void seeRoot(std::vector<std::list<int>> &adjList)
{
    // This is the heading required
    std::cout << "The adjacency list for your graph is:" << std::endl;

    // Viewing the vector's Node's
    int counter = 0;
    for (std::vector<std::list<int>>::iterator vIter = adjList.begin(); vIter < adjList.end(); ++vIter)
    {
        std::cout << "list" << counter++ << " ";
        printAdjList(*vIter);
    }
}

void printAdjList(std::list<int> &regList)
{
    // Printing out each of the list's values
    for (std::list<int>::iterator Liter = regList.begin(); Liter != regList.end(); ++Liter)
    {
        std::cout << *Liter << " ";
    }

    // Making sure it looks nice and neat
    std::cout << std::endl;
}

bool merge2(std::list<int> &shorterList, std::list<int> &longerList)
{
    // Making sure that they can be merged
    if (!connComponent(shorterList, longerList))
    {
        return false;
    }

    // Making sure shorterList is actually the shorter list
    if (shorterList.size() > longerList.size())
    {
        return merge2(longerList, shorterList);
    }

    // Creating the iterators
    std::list<int>::iterator sIter = shorterList.begin();
    std::list<int>::iterator placeIter;

    while (sIter != shorterList.end())
    {
        // Finding the appropriate place to insert the value and inserting it
        placeIter = find_gt(longerList.begin(), longerList.end(), (*sIter));
        longerList.insert(placeIter, (*sIter));

        // Incrementing the shorterList iterator
        ++sIter;
    }

    // Making sure no duplicate values are entered
    sIter = longerList.begin();
    ++sIter;
    placeIter = longerList.begin();

    while (sIter != longerList.end())
    {
        if ((*placeIter) == (*sIter))
        {
            // If there is, removing it and reset the iterators
            longerList.erase(placeIter);
            sIter = longerList.begin();
            ++sIter;
            placeIter = longerList.begin();
        }
        else
        {
            // If there's not, then increment the iterators
            ++placeIter;
            ++sIter;
        }
    }

    // Clearing the shorter list so it's primed for deletion
    shorterList.clear();

    // Returning true that the lists were merged
    return true;
}

std::list<int>::iterator find_gt(std::list<int>::iterator start, std::list<int>::iterator stop, int x)
{
    // Scanning through and seeing where the integer would fit
    while ((*start) <= x && start != stop)
    {
        ++start;
    }

    // Returning the iterator that points to where the integer should go
    return start;
}

//if there is a common element in both lists, return true otherwise false
// assumes lists are sorted in ascending order and elements are unique
bool connComponent(const std::list<int> &listOne, const std::list<int> &listTwo)
{
    // Declaring two const_iterators to scan the lists
    std::list<int>::const_iterator l1iter = listOne.begin();
    std::list<int>::const_iterator l2iter = listTwo.begin();

    while (l1iter != listOne.end() && l2iter != listTwo.end())
    {
        // Checks to see if one value is greater than the other or if they're equal.
        // The smaller one is incremented.
        // If they're the same, then true is returned
        if ((*l1iter) > (*l2iter))
        {
            ++l2iter;
        }
        else if ((*l2iter) > (*l1iter))
        {
            ++l1iter;
        }
        else
        {
            return true;
        }
    }

    // If the code has made it to here, then the lists don't have any vertices together
    return false;
}

// These functions are not part of the assignment, I just made them for myself

bool validateMergeListResponse(std::string response)
{
    // Making sure they at least put something
    if (response.length() == 0)
    {
        return false;
    }

    // This removes the whitespace while leaving a space in between the numbers
    response = removeWhitespace(response);

    // Seeing if a negative sign is present
    if (response.find("-") != -1)
    {
        // If the string is longer than 2 characters or shorter than 2 characters, then it can't be -1
        if (response.length() != 2)
        {
            return false;
        }

        // Checking to see if they put something other than -1
        if (!(getASCIIValue(response.at(0)) == 45 && getASCIIValue(response.at(1)) == 49))
        {
            return false;
        }
    }
    // No negative sign
    else
    {
        int spaceLoc = response.find(" ");

        // If there is no space, then the response is not a valid response
        if (spaceLoc == -1)
        {
            return false;
        }

        // Otherwise, check to see if the contents of the response are good to go
        int counter = 0;
        while (counter < response.length())
        {
            if (counter == spaceLoc)
            {
                // Nothing, just to make sure the other statements aren't executed
            }
            // Makes sure the inputs are all numbers
            else if (!(getASCIIValue(response.at(counter)) >= 48 && getASCIIValue(response.at(counter)) <= 57))
            {
                return false;
            }

            // Increments counter
            ++counter;
        }
    }

    // If their input passed all the tests, then it must be a valid input
    return true;
}

std::string removeWhitespace(std::string whitespace)
{
    // Setting up the variables
    std::string toReturn = "";
    bool foundNumber = false;
    int x = 0;

    // This loop finds the first number
    while (!foundNumber)
    {
        // Checks to see if the value is a space or not. If not, then it's true
        if (!(getASCIIValue(whitespace.at(x)) == 32))
        {
            // That means the number has been found, and so the variable to be true
            foundNumber = true;

            // Get the number into toReturn
            toReturn += whitespace.at(x);
            ++x;

            // If x is greater than the length of the string, then return what we've got
            if (x >= whitespace.length())
            {
                return toReturn;
            }

            // Now, just because we don't know how many digits the string is, we need to
            // keep iterating until we find out (adding the numbers to toReturn as we go)
            while (!(getASCIIValue(whitespace.at(x)) == 32))
            {
                // Adding the digit to toReturn
                toReturn += whitespace.at(x);
                ++x;

                // If x is greater then the length of the string, return what we've got
                if (x >= whitespace.length())
                {
                    return toReturn;
                }
            }
        }
        // If there was a space, we need to incremenet x
        else
        {
            ++x;
            // If x is greater then the length of the string, return what we've got
            if (x >= whitespace.length())
            {
                return toReturn;
            }
        }
    }

    // Adding a space to separate the two numbers
    toReturn += " ";

    // Setting the foundNumber variable back to false
    foundNumber = false;

    // going through the whole loop again to find the second number, but not the whole thing
    while (!foundNumber)
    {
        // Starting where we left off
        if (!(getASCIIValue(whitespace.at(x)) == 32))
        {
            // found the second number, so set the foundNumber variable to true
            foundNumber = true;

            // Add it to toReturn
            toReturn += whitespace.at(x);
            ++x;

            // Make sure x isn't greater than the length of the string
            if (x >= whitespace.length())
            {
                return toReturn;
            }

            // go through the loop again to find out how many digits the second number is
            while (!(getASCIIValue(whitespace.at(x)) == 32))
            {
                // Adding each digit to toReturn
                toReturn += whitespace.at(x);
                ++x;

                // Making sure that x isn't greater than the length of the string
                if (x >= whitespace.length())
                {
                    return toReturn;
                }
            }
        }
        // If there was a space, we need to incremenet x
        else
        {
            ++x;
            // If x is greater then the length of the string, than we must break out of the loop
            if (x >= whitespace.length())
            {
                break;
            }
        }
    }

    // If no second number was found, then the space must be removed
    if (!foundNumber)
    {
        return toReturn.substr(0, toReturn.length() - 1);
    }

    // Finally returning toReturn in it's proper form
    return toReturn;
}

int getASCIIValue(char character)
{
    return (int)character;
}
