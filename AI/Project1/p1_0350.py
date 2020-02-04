
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Feb  3 19:54:20 2020

@author: devin

Devin Hopkins
4190350

Project 1 for AI

Main class:
"""
# Just a bunch of helpful functions
from random import randint # just for this class
class HelpfulFunctions:
    
    def __init__(self):
        # Empty, nothing to do
        i = 0
    
    # Creates a random, valid list and returns it
    def createRandomList(self):
        # Getting the starting value (any int from 0 to 8)
        startingVal = randint(0, 8)
        
        # Getting the incremental value (1 or 2)
        incrementVal = randint(1, 2)
        
        # Creating the new, random list
        newList= []
        for x in range(9):
            newList.append((startingVal + (incrementVal * x)) % 9)
        
        # Returning the list
        return newList
    
    # Clears the screen by printing 100 new lines
    def clearScreen(self):
        for x in range(100):
            print("")
    
    # Returns true if it's a valid list in our case
    def isValidList(self, theList):
        # The list doesn't contain exactly 9 elements
        if (len(theList) != 9):
            return False
        
        # Making sure the list has the correct values in it
        if (not self.hasCorrectValues(theList)):
            return False
        
        # It is in fact a valid list
        return True

    # Returns true if each number is in the list once and only once
    def hasCorrectValues(self, theList):
        # The element isn't a correct digit
        for x in theList:
            if (not self.isThisStringAValidDigit(x)):
                return False
        
        # Making sure one of each value is included in the list
        for x in range(9):
            found = False
            for y in range(9):
                if (theList[y] == str(x)):
                    found = True
            if (not found):
                return False
            
        # If everything checks out, it's a valid list
        return True
    
    # Returns true if the string contains a digit that's allowed (0-8)
    def isThisStringAValidDigit(self, string):
        # 0
        if (string == "0"):
            return True
    
        # 1
        if (string == "1"):
            return True
    
        # 2
        if (string == "2"):
            return True
        
        # 3
        if (string == "3"):
            return True
    
        # 4
        if (string == "4"):
            return True
    
        # 5
        if (string == "5"):
            return True
    
        # 6
        if (string == "6"):
            return True
    
        # 7
        if (string == "7"):
            return True
    
        # 8
        if (string == "8"):
            return True
    
        # Not a correct digit then
        return False


# Game State class
class GameState:
    
    # Just some helper functions
    helper = HelpfulFunctions()
    state = []
    
    # Constructor, can take nothing or a pre-generated list
    def __init__(self, initialList = []):
        # If the list was not pregenerated or pregenerated incorrectly,
        # make a new list
        if (not self.helper.isValidList(initialList)):
            # Make a new list
            self.state = self.helper.createRandomList()
        # Otherwise, the list is good to go
        else:
            # The list has laready been made
            self.state = initialList
    
    # Displays the state
    def displayState(self):
        # This is to keep track of what element the list is on
        count = 0
        
        # Looping through and grabbing all of the values in the list
        for x in self.state:
            print(x, end=" ")
            # Prints a newline every 3 outputs, to keep in touch with the game
            if ((count + 1) % 3 == 0):
                print("")
            count = count + 1
        
        # Just so the next thing that gets printed isn't on the same line
        print("")

#def n_puzzle():
def s():
    # Initializing the help functions
    helper = HelpfulFunctions()
    
    # Initializing the start list
    startStateList = []
    
    # Gathering the numbers the user wants to start their puzzle
    #
    # This is telling the user what to expect
    print("Enter numbers for the 8 puzzle game (one at a time). This will be the starting state.")
    print("You may enter the numbers 0-8 (each once) to make your own or enter -1 and a starting state will be generated for you.")
    # Looping through to gather their input
    for x in range(9):
        # Displaying what number they're on
        inputStr = "Number " + str(x + 1) + ": "
        val = input(inputStr)
        # They entered something other than a "-1", append it and keep going
        if (val != "-1"):
            startStateList.append(val)
        # They entered a "-1", so quit
        else:
            break;
    
    # Creating the current (initial) state
    currentState = GameState(startStateList)
    
    # Making sure the formatting stays nice and neat
    print("")
    
    # Displaying the initial state
    print("Initial State:")
    currentState.displayState()
    
    # Initializing the start list
    goalStateList = []
    
    # Gathering the numbers the user wants to start their puzzle
    #
    # This is telling the user what to expect
    print("Enter numbers for the 8 puzzle game (one at a time). This will be the goal state.")
    print("You may enter the numbers 0-8 (each once) to make your own or enter -1 and a goal will be generated for you.")
    # Looping through to gather their input
    for x in range(9):
        # Displaying what number they're on
        inputStr = "Number " + str(x + 1) + ": "
        val = input(inputStr)
        # They entered something other than a "-1", append it and keep going
        if (val != "-1"):
            goalStateList.append(val)
        # They entered a "-1", so quit
        else:
            break;
            
    # Creating the end (goal) state
    goalState = GameState(goalStateList)
    
    # Making sure the formatting stays nice and neat
    helper.clearScreen()
    
    # Displaying the initial state
    print("Initial State:")
    currentState.displayState()
    
    # Displaying the initial state
    print("Goal State:")
    goalState.displayState()
    
    
    
    
    
    
    
    