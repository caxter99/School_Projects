/*
COPYRIGHT (C) 2017 Devin Hopkins (4190250) All rights reserved.
CSI Assignment 4A
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 09.30.2017
Purpose: The purpose of this program is to have a rad game of rock, paper, scissors, lizard, spock
*/

// Importing necessary packages
#include <iostream>
#include <cstdlib>

// Importing necessary std functions
using std::cin;
using std::cout;
using std::endl;
using std::string;

// This function displays the menu
void displayMenu();

// This simply gets the computer's choice
int getComputerChoice();

// This function gets the user's input and also makes sure it's valid
int getUserChoice();

// This function takes an int, and converts it to the string version of the choice
string getToolChoice(int);

// Unfortunately, I had already done the program after discovering I needed
// to have my choices stored as ints. So, I had to make this function to take
// a chocie as a string and convert it back to an int
int convertToInt(string);

// This function determines if there's a winner or if there's a tie
string determineWinner(string, string);

// This method prints out the choice, given an int
void displayChoice(int);

int main()
{
    // Declaring and initializing variables
    int toolChoice, counter;
    string computerChoice, playerChoice, winner;
    counter = 1;

    // Entering into the do while loop that contains the main program
    do{
        counter += 1;

        // Computing what the computer will choose
        toolChoice = getComputerChoice();
        computerChoice = getToolChoice(toolChoice);

        // Figuring out what the player wants
        playerChoice = getToolChoice(getUserChoice());

        // Declaring the winner
        winner = determineWinner(computerChoice, playerChoice);

        // Printing out the winner
        if (winner != "tie")
        {
            cout << "\nComputer Choice: ";
            displayChoice(convertToInt(computerChoice));
            cout << "\n  Player Choice: ";
            displayChoice(convertToInt(playerChoice));
            cout << "\n         Winner: " << winner << endl;
        }
        else
        {
            cout << "\nIt was a tie! Both players chose " << computerChoice <<
                    "! Time for round " << counter << "!" << endl;
        }

    // If there was no winner (a tie, the loop will go again until there is a winner)
    }while(winner == "tie");

    return 0;
}

// This function displays the menu
void displayMenu()
{
    cout << "Select which item you want:" <<
        "\n1. Rock" <<
        "\n2. Paper" <<
        "\n3. Scissors" <<
        "\n4. Lizard" <<
        "\n5. Spock" << endl;
}

// This simply gets the computer's choice
int getComputerChoice()
{
    return rand() % 5 + 1;
}

// This function gets the user's input and also makes sure it's valid
int getUserChoice()
{
    int menuChoice;
    displayMenu();
    cin >> menuChoice;
    do{
        if (cin.fail() || menuChoice > 5 || menuChoice < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nThat was not a valid choice. Please enter again." << endl;
            displayMenu();
            cin >> menuChoice;
        }
    }while(cin.fail() || menuChoice > 5 || menuChoice < 1);
    return menuChoice;
}

// This function takes an int, and converts it to the string version of the choice
string getToolChoice(int toolChoice)
{
    string choice;
    switch(toolChoice)
    {
        case 1:
            choice = "rock";
            break;
        case 2:
            choice = "paper";
            break;
        case 3:
            choice = "scissors";
            break;
        case 4:
            choice = "lizard";
            break;
        default:
            choice = "spock";
    }
    return choice;
}

// Unfortunately, I had already done the program after discovering I needed
// to have my choices stored as ints. So, I had to make this function to take
// a chocie as a string and convert it back to an int
int convertToInt(string str)
{
    if (str == "rock")
    {
        return 1;
    }
    else if (str == "paper")
    {
        return 2;
    }
    else if (str == "scissors")
    {
        return 3;
    }
    else if (str == "lizard")
    {
        return 4;
    }
    return 5;
}

// This function determines if there's a winner or if there's a tie
string determineWinner(string computer, string player)
{
    switch(convertToInt(computer))
    {
        case 1:
            if(player == "scissors" || player == "lizard")
            {
                return "computer";
            }
            else if(player != "rock")
            {
                return "player";
            }
            break;

        case 2:
            if (player == "rock" || player == "spock")
            {
                return "computer";
            }
            else if (player != "paper")
            {
                return "player";
            }
            break;

        case 3:
            if (player == "paper" || player == "lizard")
            {
                return "computer";
            }
            else if (player != "scissors")
            {
                return "player";
            }
            break;

        case 4:
            if (player == "spock" || player == "paper")
            {
                return "computer";
            }
            else if (player != "lizard")
            {
                return "player";
            }
            break;

        default:
            if (player == "scissors" || player == "rock")
            {
                return "computer";
            }
            else if (player != "spock")
            {
                return "player";
            }
    }

    // Will reach here if there's a tie
    return "tie";
}

// This method prints out the choice, given an int
void displayChoice(int x)
{
    if (x == 1)
    {
        cout << "rock";
    }
    else if (x == 2)
    {
        cout << "paper";
    }
    else if (x == 3)
    {
        cout << "scissors";
    }
    else if (x == 4)
    {
        cout << "lizard";
    }
    else
    {
        cout << "spock";
    }
}
