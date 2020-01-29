
// Devin Hopkins
// 4190350
// djh155@zips.uakron.edu

#include <limits>
#include <string>

#include "maze.h"
#include "mazeCell.h"
#include "disjSets.h"

// Function headers
//
// Returns an int between the two specified regions (inclusive)
int getIntFromCin(int lowerBound, int upperBound, std::string prompt, std::string errorMessage);

int main(int argc, char const *argv[])
{
    // Getting the number of rows and columns the user wants
    int rowNum = getIntFromCin(2, std::numeric_limits<int>::max(), "How many rows in your maze (greater than 1)? ", "Error. Please enter a single integer greater than 1.");
    int colNum = getIntFromCin(2, std::numeric_limits<int>::max(), "How many columns in your maze (greater than 1)? ", "Error. Please enter a single integer greater than 1.");

    // Creating the maze and disjSets objects
    maze myMaze = maze{rowNum, colNum};
    DisjSets dSet = DisjSets{rowNum * colNum};

    // This loop keeps going until the starting cell is connected to the exit cell
    while (!dSet.isConnected(0, rowNum * colNum - 1))
    {
        // Showing the user the maze
        myMaze.printMaze();

        // This is the error message the user sees
        std::string errorMessage = "Error. Please enter a single integer between the numbers 0 and " + std::to_string(rowNum * colNum - 1) + ".";

        // Getting the two cells the user wants to smash a wall between
        int cell1 = getIntFromCin(0, rowNum * colNum - 1, "Enter first neighbor: ", errorMessage);
        int cell2 = getIntFromCin(0, rowNum * colNum - 1, "Enter second neighbor: ", errorMessage);

        // If the two cells the user entered are neighbors
        if (myMaze.neighbors(cell1, cell2))
        {
            // Smashing the wall in between them
            myMaze.smashWall(cell1, cell2);
            myMaze.smashWall(cell2, cell1);

            // Making the two sets come together if they're not already
            if (!dSet.isConnected(cell1, cell2))
            {
                dSet.unionSets(dSet.find(cell1), dSet.find(cell2));
            }

            // Telling the user that the wall was smashed
            std::cout << "Smashing wall between " << cell1 << " and " << cell2 << "\n";
        }
        // If the two cells aren't neighbors
        else
        {
            // Telling the user that no wall was smashed
            std::cout << cell1 << " and " << cell2 << " are not neighbors. No wall smashed.\n";
        }
    }

    // Displaying the maze one last time and letting the user know the maze is finished
    myMaze.printMaze();
    std::cout << "The maze is built. Finished!\n";

}

// Returns an int between the two specified regions inclusive
int getIntFromCin(int lowerBound, int upperBound, std::string prompt, std::string errorMessage)
{
    // This variable keeps track of whether or not the user put in a valid input
    bool properInput = false;

    // This is what the user enters
    int numToReturn = 0;

    // Getting the input for the number of rows
    while(!properInput)
    {
        // This assumes we got proper input
        properInput = true;

        // Asking and getting the user's response to the number of rows they want
        std::cout << prompt;
        std::cin >> numToReturn;

        // Making sure what they entered was valid
        try{
            // If it wasn't, an exception is thrown
            if (cin.fail())
            {
                throw 1;
            }

            // If the user entered a number that was too small, an exception is thrown as well
            if (numToReturn < lowerBound)
            {
                throw 1;
            }
            // If the user enters a number that was too big, an exception is thrown.
            else if (numToReturn > upperBound)
            {
                throw 1;
            }
        // The exception is caught and the user is told what they must do to correct their mistake
        }catch(int errorCatcher){
            // Displaying their error message
            std::cout << errorMessage << "\n";

            // Makes sure they must re-enter the number
            properInput = false;

            // This clears cin so it's ready to go again
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }

    // Returning their integer
    return numToReturn;
}