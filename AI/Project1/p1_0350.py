
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
# Global (const) variables
NUM_OF_X_GRID = 3
NUM_OF_Y_GRID = 3

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
        for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
            # They must be entered as strings, because if the user entered the
            # other grid, the other grid will be all strings. The rest of the
            # program assumes these values will be strings
            newList.append(str((startingVal + (incrementVal * x)) % 9))
        
        # Returning the list
        return newList
    
    # Clears the screen by printing 100 new lines
    def clearScreen(self):
        for x in range(100):
            print("")
    
    # Returns true if it's a valid list in our case
    def isValidList(self, theList):
        # The list doesn't contain exactly 9 elements
        if (len(theList) != NUM_OF_X_GRID * NUM_OF_Y_GRID):
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
        for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
            found = False
            for y in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
                if (theList[y] == str(x)):
                    found = True
            if (not found):
                return False
            
        # If everything checks out, it's a valid list
        return True
    
    # Returns true if the string contains a digit that's allowed (0-8)
    def isThisStringAValidDigit(self, string):
        # Going through all of the possible numbers
        for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
            # If the string matches that of an appropriate number, return true
            if (string == str(x)):
                return True
    
        # Not a correct digit then
        return False


# Game State class
import math
class GameState:
    
    # Just some helper functions and variables
    helper = HelpfulFunctions()
    state = []
    totalManhattanSteps = 0
    totalHammingSteps = 0
    
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
            if ((count + 1) % NUM_OF_Y_GRID == 0):
                print("")
            count = count + 1
        
        # Just so the next thing that gets printed isn't on the same line
        print("")
        
    # Returns the list of the state
    def getState(self):
        return self.state
    
    # Compares this state to a different state. Returns true if they're the
    # same, false otherwise
    def compare(self, otherState):
        # Going through and comparing each space to each other
        for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
            # If any of them do not match, they are not equal
            if (self.state[x] != otherState.getState()[x]):
                return False
        
        # If they all match, they're equal
        return True
    
    # Returns the number of steps to the goal puzzle, the Manhatten way.
    # This assumes that the object executing this function is the current
    # state
    def calcManhattenSteps(self, goalState):
        # Initially, the total distance is 0
        totalDistance = 0
        
        # Looping through each point, calculating its distance
        for x1 in range(NUM_OF_X_GRID):
            for y1 in range(NUM_OF_Y_GRID):
                # Getting the number at the point in the current list
                numAtCurrentPoint = self.state[x1 + NUM_OF_Y_GRID * y1]
                
                # Making sure the number 0 isn't counted
                if (not (numAtCurrentPoint == 0)):
                     # Looping through the goal state to find out where that
                     # same number is in the goal state
                     for x2 in range(NUM_OF_X_GRID):
                         for y2 in range(NUM_OF_Y_GRID):
                             # Getting the number at the point in the goalt state's list
                             numAtGoalPoint = goalState.getState()[x2 + NUM_OF_Y_GRID * y2]
                             
                             # If they're the same (and not 0), calculate and add the distance
                             if (numAtCurrentPoint == numAtGoalPoint):
                                 # x distance
                                 totalDistance = totalDistance + math.sqrt(math.pow(x1 - x2, 2))
                                 
                                 # y dstance
                                 totalDistance = totalDistance + math.sqrt(math.pow(y1 - y2, 2))
        
        # Return the total distance
        return totalDistance
                

# Move Calculator class
class MoveCalc:
    
    # Constructor
    def __init__(self):
        # Nothing now
        i = 0
    
    # Calculates the best move and returns the new state
    def makeBestMove(self, currentState, goalState):
        # to do
        i = 0

# Game class
class Game:
    
    # Initializing the variables needed for the game
    helper = HelpfulFunctions()
    mover = MoveCalc()
    previousState = GameState()
    currentState = GameState()
    goalState = GameState()
    
    # Constructor
    def __init__(self):   
        # Set up the puzzle game
        self.setUp()
        
    # The set up for the game
    def setUp(self):
        # Initializing the start list
        startStateList = []
    
        # Gathering the numbers the user wants to start their puzzle
        #
        # This is telling the user what to expect
        print("Enter numbers for the 8 puzzle game (one at a time). This will be the starting state.")
        print("You may enter the numbers 0-8 (each once) to make your own or enter -1 and a starting state will be generated for you.")
        # Looping through to gather their input
        for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
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
        self.currentState = GameState(startStateList)
    
        # Making sure the formatting stays nice and neat
        print("")
    
        # Displaying the initial state
        print("Initial State:")
        self.currentState.displayState()
    
        # Initializing the start list
        goalStateList = []
    
        # Gathering the numbers the user wants to start their puzzle
        #
        # This is telling the user what to expect
        print("Enter numbers for the 8 puzzle game (one at a time). This will be the goal state.")
        print("You may enter the numbers 0-8 (each once) to make your own or enter -1 and a goal will be generated for you.")
        # Looping through to gather their input
        for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
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
        self.goalState = GameState(goalStateList)
    
        # Making sure the formatting stays nice and neat
        self.helper.clearScreen()
    
        # Displaying the initial state
        print("Initial State:")
        self.currentState.displayState()
    
        # Displaying the initial state
        print("Goal State:")
        self.goalState.displayState()
        
    def playGame(self):
        # Test line to know where the code is at
        print("Play the game!")
        print(self.currentState.calcManhattenSteps(self.goalState))
        
        # This will loop while the current and goal state do not match
        #while(not self.currentState.compare(self.goalState)):
            # this is the game here

#def n_puzzle(): # Will use eventually, got tired of typing "n_puzzle()" every time to test
def s():
    # Creating and playing the game
    game = Game()
    game.playGame()
    
    
    
    
    
    
    
    