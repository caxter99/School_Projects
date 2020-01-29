
// Devin Hopkins
// 4190350
// djh155@zips.uakron.edu

#include "maze.h"

maze::maze(int r, int c) // constructor
{
    // Setting the rows and columns
    row = r;
    col = c;

    // Pushing back the starting cell
    theMaze.push_back(*new mazeCell{false, true, false, true});

    // This pushes back all the remaining cells (excluding the exit cell)
    for (int x = 1; x < r * c - 1; ++x)
    {
        theMaze.push_back(*new mazeCell{});
    }

    // Pushing back the exit cell
    theMaze.push_back(*new mazeCell{true, false, true, false});
}

// returns true if neigh is cell's neighbor
//(i.e. in position left, right, top or bot
// with respect to cell)
bool maze::neighbors(int cell, int neigh) const
{
    // For this funciton, cell must be the smaller int
    if (cell > neigh)
    {
        return neighbors(neigh, cell);
    }
    // Detecting if one of the inputs is out of range
    else if (neigh > theMaze.size() - 1)
    {
        std::cout << "Error. Input (" << cell << ", " << neigh << ") is out of range.\n";
        return false;
    }
    // Detecting if they're the same number
    else if (cell == neigh)
    {
        std::cout << "Error. Input (" << cell << ", " << neigh << ") are the same number.\n";
        return false;
    }

    // This detects to see if the cells are next to each other horizontally
    if (cell + 1 == neigh && (cell % col) + 1 == neigh % col)
    {
        return true;
    }
    // This detects to see if the cells are next to each other vertically
    else if (cell % col == neigh % col)
    {
        return true;
    }

    // If nothing checks out, then the cells must not be neighbors
    return false;
}

// get rid of cell's wall between cell and neighbor
// Note: this method should be invoked twice from the driver
// code to smashWall(a,b) and to smashWall(b,a)
void maze::smashWall (int cell, int neigh)
{
    // Detecting if they're vertical neighbors
    if (cell % col == neigh % col)
    {
        // Cell is on the top
        if (cell > neigh)
        {
            theMaze[cell].setTop(false);
            theMaze[neigh].setBot(false);
        }
        // Neigh is on the top
        else
        {
            theMaze[neigh].setTop(false);
            theMaze[cell].setBot(false);
        }
    }
    // If not vertical neighbors, then they must be horizontal neighbors
    else
    {
        // Cell is on the right
        if (cell > neigh)
        {
            theMaze[cell].setLeft(false);
            theMaze[neigh].setRight(false);
        }
        // Neigh is on the left
        else
        {
            theMaze[neigh].setLeft(false);
            theMaze[cell].setRight(false);
        }
    }
}

// Print the maze
void maze::printMaze()
{
    // Making sure the maze starts on a new line so nothing is messed up
    std::cout << "\n";
    
    // This prints out the top row of the maze
    for (int x = 0; x < col * 2; ++x)
    {
        // If it's an even x and it's beyond the first two spots, then it must be a space
        if (x < 2 || x % 2 == 0)
        {
            std::cout << " ";
        }
        // Otherwise, it must be a wall
        else
        {
            std::cout << "_";
        }
    }

    // This is just to make sure the rest of the maze starts at the next line
    std::cout << "\n";

    // This prints out the the rest of the maze
    for (int x = 0; x < theMaze.size(); ++x)
    {
        // If the cell is the very end of the row, we need to go to a new line before
        // we display anything else
        if (x != 0 && x % col == 0)
        {
            std::cout << "\n";
        }

        // If this is any cell but the first and last cell
        if (x != 0 && x != theMaze.size() - 1)
        {
            // This is if the wall is the left most cell in the row
            if (x % col == 0)
            {
                // Printing out the left wall since there's no cell to the left, thus
                // meaning there's always a wall over there
                std::cout << "|";
            }

            // Figuring out if the floor has been destroyed or not and correctly
            // displaying it
            if (theMaze[x].getBot())
            {
                std::cout << "_";
            }
            else
            {
                std::cout << " ";
            }

            // Figuring out if the right wall has been destroyed or not and
            // correctly displaying it
            if (theMaze[x].getRight())
            {
                std::cout << "|";
            }
            else
            {
                std::cout << " ";
            }

            // The top doesn't need printed as the top was printed before.
            // Therefore, we're done
        }
        // If this is the first cell
        else if (x == 0)
        {
            // Prints the intial space
            std::cout << " ";

            // Figuring out if the floor has been destroyed or not and correctly
            // displaying it
            if (theMaze[x].getBot())
            {
                std::cout << "_";
            }
            else
            {
                std::cout << " ";
            }

            // Figuring out if the right wall has been destroyed or not and
            // correctly displaying it
            if (theMaze[x].getRight())
            {
                std::cout << "|";
            }
            else
            {
                std::cout << " ";
            }

            // The top and left wall don't need printed as the top was printed
            // before and the left wall doesn't need printed.
            // Therefore, we're done
        }
        // If this is the last cell
        else
        {
            // Nothing needs to be done since printing it won't matter. A newline
            // is printed just to make it look nice
            std::cout << "\n";
        }
    }

    // This just makes sure the next output isn't touching the bottom of the maze
    std::cout << "\n";
}