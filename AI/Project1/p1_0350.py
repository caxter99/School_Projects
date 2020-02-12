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
NUM_OF_X_GRID = 3 # The width of the grid
NUM_OF_Y_GRID = 3 # The height of the grid
NULL = "null" # The null value
MAX_STEPS = float('inf') # This is used for states that have no way of finishing (or other error methods for
                # checking steps remaining)
TRUE_RANDOM = False # This is to say if the created states (if not created by the user)
                # will be randomly made or not
SHUFFLE_TIMES = 500 # The number of times the goal state will be shuffled to create
                # the starting state (if applicable)
MAX_RECURSION = (9 * 8 * 7 * 6 * 5 * 4 * 3 * 2) + 2 # The maximum number of times recursion can occur
                
from random import randint # just for this class
import sys

# Just a bunch of helpful functions
class HelpfulFunctions:
    
    def __init__(self):
        # Empty, nothing to do
        i = 0
    
    # Set the recursion limit
    def setRecursionLimit(self, limit):
        sys.setrecursionlimit(limit)
    
    # Compares four values and returns the largest value of the four (does not
    # count values equal to MAX_STEPS)
    def getLargest(self, first, second, third, fourth):
        # Making sure none of the values are infinite, otherwise that'll screw up the calculations
        if (first == MAX_STEPS):
            first = 0
        if (second == MAX_STEPS):
            second = 0
        if (third == MAX_STEPS):
            third = 0
        if (fourth == MAX_STEPS):
            fourth = 0
        
        # Comparing the first value to all of the others
        if (first <= second and first <= third and first <= fourth):
            return first
        elif (second <= first and second <= third and fourth <= fourth):
            return second
        elif (third <= first and third <= second and third <= fourth):
            return third
        return fourth
    
    # Compares four values and returns true if the first value is the smallest
    def compareFourTight(self, first, second, third, fourth):
        # Comparing all of the values against the first value
        if (first < second and first < third and first < fourth):
            return True
        
        # It's not the smallest value
        return False
    
    # Compares four values and returns true if the first value is the smallest or tied smallest
    def compareFourLoose(self, first, second, third, fourth):
        # Comparing all of the values against the first value
        if (first <= second and first <= third and first <= fourth):
            return True
        
        # It's not the smallest value
        return False
    
    # Creates a random, valid list and returns it
    def createRandomList(self, trueRandom = True):
        # Creating the new, random list
        newList= []
        
        # Seeing if it's truly a 100% random list
        if (trueRandom):
            # Getting the starting value (any int from 0 to 8)
            startingVal = randint(0, 8)
        
            # Getting the incremental value (1 or 2)
            incrementVal = randint(1, 2)
        
            # Looping through all of the number
            for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
                # They must be entered as strings, because if the user entered the
                # other grid, the other grid will be all strings. The rest of the
                # program assumes these values will be strings
                newList.append(str((startingVal + (incrementVal * x)) % 9))
       # Not truly random
        else:
            # Creating a straight up normal list
            newList = ["0", "1", "2", "3", "4", "5", "6", "7", "8"]
        
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
    
    # Returns true if the position is on the left of the grid
    def posIsOnLeft(self, position):
        for x in range(NUM_OF_X_GRID):
            if (str(x * NUM_OF_X_GRID) == str(position)):
                return True
        
        # Not on the left
        return False
    
    # Returns true if the position is on the right of the grid
    def posIsOnRight(self, position):
        for x in range(NUM_OF_X_GRID):
            if (str((x * NUM_OF_X_GRID) + (NUM_OF_X_GRID - 1)) == str(position)):
                return True
        
        # Not on the right
        return False
    
    # Returns true if the position is on the top of the grid
    def posIsOnTop(self, position):
        for x in range(NUM_OF_X_GRID):
            if (str(x) == str(position)):
                return True
        
        # Not on the top
        return False
    
    # Returns true if the position is on the top of the grid
    def posIsOnBottom(self, position):
        for x in range(NUM_OF_X_GRID):
            if (str((NUM_OF_X_GRID * NUM_OF_Y_GRID) - NUM_OF_X_GRID + x) == str(position)):
                return True
        
        # Not on the top
        return False
    
    # Creates a copy of the list sent in
    def createDuplicateList(self, theList):
        # Creating the new list
        newList = []
        
        # Looping through and copying the list
        for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID):
            newList.append(theList[x])
        
        # Returning the new list
        return newList


# Game State class
import math
class GameState:
    
    from random import randint # just for this class
    
    # Just some helper functions and variables
    helper = HelpfulFunctions()
    state = []
    totalManhattanSteps = 0
    totalHammingSteps = 0
    
    # Constructor, can take nothing or a pre-generated list
    def __init__(self, initialList = [], trueRandom = True):
        # If the list was not pregenerated or pregenerated incorrectly,
        # make a new list
        if (not self.helper.isValidList(initialList)):
            # Make a new list
            self.state = self.helper.createRandomList(trueRandom)
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
        
    # Resets the list to a new list (can also be used as a reset)
    def setList(self, newList = []):
        # If the list was not pregenerated or pregenerated incorrectly,
        # make a new list
        if (not self.helper.isValidList(newList)):
            self.state = self.helper.createRandomList()
        # The list is valid, set to the game state's list
        else:
            self.state = newList
        
    # Shuffles the state based on the number sent in
    def shuffle(self, numOfShuffles):
        for x in range(numOfShuffles):
            randomInt = randint(1, 4) # From 1 to 4 inclusive
            if (randomInt == 1):
                posList = self.moveLeft()
                if (not (posList == NULL)):
                    self.setList(self.moveLeft())
            elif (randomInt == 2):
                posList = self.moveRight()
                if (not (posList == NULL)):
                    self.setList(self.moveRight())
            elif (randomInt == 3):
                posList = self.moveUp()
                if (not (posList == NULL)):
                    self.setList(self.moveUp())
            else:
                posList = self.moveDown()
                if (not (posList == NULL)):
                    self.setList(self.moveDown())
    
    # Creates a list for a state that would look like as though a move to the left was made
    def moveLeft(self):
        # Creating the left state
        leftStateList = NULL
        
        # Looping through to find the 0 in the puzzle
        for x1 in range(NUM_OF_X_GRID):
            for y1 in range(NUM_OF_Y_GRID):
                # Just in case we need this position several times later
                position = x1 + NUM_OF_Y_GRID * y1
                
                # The 0 has been found
                if (self.state[position] == "0"):
                    # If the 0 is not on the left of the grid
                    if (not self.helper.posIsOnLeft(position)):
                        # Copying the old list to the new one
                        leftStateList = self.helper.createDuplicateList(self.state)
                        
                        # Switching the positions of the 0 and the spot to the left
                        leftStateList[position - 1], leftStateList[position] = leftStateList[position], leftStateList[position - 1]
                        
        # Returning the left state (as null or a new state)
        return leftStateList
    
    # Creates a list for a state that would look like as though a move to the right was made
    def moveRight(self):
        # Creating the right state
        rightStateList = NULL
        
        # Looping through to find the 0 in the puzzle
        for x1 in range(NUM_OF_X_GRID):
            for y1 in range(NUM_OF_Y_GRID):
                # Just in case we need this position several times later
                position = x1 + NUM_OF_Y_GRID * y1
                
                # The 0 has been found
                if (self.state[position] == "0"):
                    # If the 0 is not on the left of the grid
                    if (not self.helper.posIsOnRight(position)):
                        # Copying the old list to the new one
                        rightStateList = self.helper.createDuplicateList(self.state)
                        
                        # Switching the positions of the 0 and the spot to the right
                        rightStateList[position], rightStateList[position + 1] = rightStateList[position + 1], rightStateList[position]
                        
        # Returning the left state (as null or a new state)
        return rightStateList
    
    # Creates a list for a state that would look like as though a move up was made
    def moveUp(self):
        # Creating the up state
        upStateList = NULL
        
        # Looping through to find the 0 in the puzzle
        for x1 in range(NUM_OF_X_GRID):
            for y1 in range(NUM_OF_Y_GRID):
                # Just in case we need this position several times later
                position = x1 + NUM_OF_Y_GRID * y1
                
                # The 0 has been found
                if (self.state[position] == "0"):
                    # If the 0 is not on the left of the grid
                    if (not self.helper.posIsOnTop(position)):
                        # Copying the old list to the new one
                        upStateList = self.helper.createDuplicateList(self.state)
                        
                        # Switching the positions of the 0 and the spot up one
                        upStateList[position], upStateList[position - NUM_OF_X_GRID] = upStateList[position - NUM_OF_X_GRID], upStateList[position]
                        
        # Returning the left state (as null or a new state)
        return upStateList
    
    # Creates a list for a state that would look like as though a move down was made
    def moveDown(self):
        # Creating the down state
        downStateList = NULL
        
        # Looping through to find the 0 in the puzzle
        for x1 in range(NUM_OF_X_GRID):
            for y1 in range(NUM_OF_Y_GRID):
                # Just in case we need this position several times later
                position = x1 + NUM_OF_Y_GRID * y1
                
                # The 0 has been found
                if (self.state[position] == "0"):
                    # If the 0 is not on the bottom of the grid
                    if (not self.helper.posIsOnBottom(position)):
                        # Copying the old list to the new one
                        downStateList = self.helper.createDuplicateList(self.state)
                        
                        # Switching the positions of the 0 and the spot down one
                        downStateList[position], downStateList[position + NUM_OF_X_GRID] = downStateList[position + NUM_OF_X_GRID], downStateList[position]
                        
        # Returning the left state (as null or a new state)
        return downStateList
    
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
        newDistance = 0
        
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
                                 newDistance = newDistance + math.sqrt(math.pow(x1 - x2, 2))
                                 
                                 # y distance
                                 newDistance = newDistance + math.sqrt(math.pow(y1 - y2, 2))
        
        # Getting the previous amount of Manhattan steps
        self.totalManhattanSteps = self.totalManhattanSteps + newDistance
        
        # Return the total new distance
        return self.totalManhattanSteps
    
    # Takes in a lists of lists with the previous game states stored inside of them.
    # Returns true if the current state matches none of the state found inside
    # the list of lists
    def comparePrevious(self, previousLists):
        # Making sure it's not empty
        if (len(previousLists) == 0):
            return False
        
        # If there's legit lists inside of it
        for y in range(len(previousLists)):
            tempGameState = GameState(previousLists[y])
                
            # It matches a previous game state
            if (self.compare(tempGameState)):
                return True
        
        # It doesn't match any previous game state
        return False
    
    # Removes the state from the list of previous states
    def removeSelfFromPrevious(self, previousLists):
        if (not len(previousLists) == 0):
            try:
                previousLists.remove(self.state)
            except:
                # Caught an error
                print("not in the list")
                

# Move Calculator class
class MoveCalc:
    
    # Variables
    helper = HelpfulFunctions()
    
    # Constructor
    def __init__(self):
        # Nothing now
        i = 0
    
    # Receives the previous state, 4 possible new states, and the goal state and returns the best
    def goDeeper(self, previousStates, statesOnTheWay, state1, state2, state3, state4, goalState, timesThrough = 0):
        # Variables for state 1
        step1 = MAX_STEPS
        pos1 = True
        isNull1 = False
        duplicateOfPreviousState1 = False
        
        # Variables for state 2
        step2 = MAX_STEPS
        pos2 = True
        isNull2 = False
        duplicateOfPreviousState2 = False
        
        # Variables for state 3
        step3 = MAX_STEPS
        pos3= True
        isNull3 = False
        duplicateOfPreviousState3 = False
        
        # Variables for state 4
        step4 = MAX_STEPS
        pos4 = True
        isNull4 = False
        duplicateOfPreviousState4 = False
        
        if (state1 == NULL):
            isNull1 = True
        else:
            if (state1.comparePrevious(previousStates)):
                duplicateOfPreviousState1 = True
            else:
                step1 = state1.calcManhattenSteps(goalState)
        if (state2 == NULL):
            isNull2 = True
        else:
            if (state2.comparePrevious(previousStates)):
                duplicateOfPreviousState2 = True
            else:
                step2 = state2.calcManhattenSteps(goalState)
        if (state3 == NULL):
            isNull3 = True
        else:
            if (state3.comparePrevious(previousStates)):
                duplicateOfPreviousState3 = True
            else:
                step3 = state3.calcManhattenSteps(goalState)
        if (state4 == NULL):
            isNull4 = True
        else:
            if (state4.comparePrevious(previousStates)):
                duplicateOfPreviousState4 = True
            else:
                step4 = state4.calcManhattenSteps(goalState)
        
        if (isNull1 or duplicateOfPreviousState1 or step1 == MAX_STEPS):
            pos1 = False
        if (isNull2 or duplicateOfPreviousState2 or step2 == MAX_STEPS):
            pos2 = False
        if (isNull3 or duplicateOfPreviousState3 or step3 == MAX_STEPS):
            pos3 = False
        if (isNull4 or duplicateOfPreviousState4 or step4 == MAX_STEPS):
            pos4 = False
        
        #print("state 1 steps:", step1)
        #print("state 2 steps:", step2)
        #print("state 3 steps:", step3)
        #print("state 4 steps:", step4)
        
        if (pos1):
            # Adding state1 to the list of states on the way
            statesOnTheWay.append(state1.getState())
            
            # Checking to see if state1 will lead to the goal state
            if (self.solve(previousStates, statesOnTheWay, state1, goalState, timesThrough + 1)):
                # It lead to the goal state
                return True
            else:
                # Removing state1 because it wasn't on the way
                statesOnTheWay.remove(state1.getState())
        if (pos2):
            # Adding state2 to the list of states on the way
            statesOnTheWay.append(state2.getState())
            
            # Checking to see if state2 will lead to the goal state
            if (self.solve(previousStates, statesOnTheWay, state2, goalState, timesThrough + 1)):
                # It lead to the goal state
                return True
            else:
                # Removing state2 because it wasn't on the way
                statesOnTheWay.remove(state2.getState())
        if (pos3):
            # Adding state3 to the list of states on the way
            statesOnTheWay.append(state3.getState())
            
            # Checking to see if state3 will lead to the goal state
            if (self.solve(previousStates, statesOnTheWay, state3, goalState, timesThrough + 1)):
                # It lead to the goal state
                return True
            else:
                # Removing state3 because it wasn't on the way
                statesOnTheWay.remove(state3.getState())
        if (pos4):
            # Adding state4 to the list of states on the way
            statesOnTheWay.append(state4.getState())
            
            # Checking to see if state4 will lead to the goal state
            if (self.solve(previousStates, statesOnTheWay, state4, goalState, timesThrough + 1)):
                # It lead to the goal state
                return True
            else:
                # Removing state4 because it wasn't on the way
                statesOnTheWay.remove(state4.getState())
        
        # No state led to the goal state
        return False
    
    # Calculates the best move and returns the new state
    def solve(self, previousStates, statesOnTheWay, currentState, goalState, timesThrough = 0):
        # TESTING
        #print("Current State:")
        #currentState.displayState()
        #print("")
        # Checking to see if the current state matches the goal state
        if (currentState.compare(goalState)):
            return True
        
        # Adding the current state to the list of previous states
        previousStates.append(currentState.getState())
        
        # Making sure the program isn't near the limit for recursion
        if (timesThrough >= MAX_RECURSION - RECURSION_SAFETY_NET):
            # If it is, can't go on any longer or risk crashing
            return False
        
        # All of new vriables to hold the new game states
        leftState = GameState()
        rightState = GameState()
        upState = GameState()
        downState = GameState()
        
        # Figuring out
        if (not currentState.moveLeft() == NULL):
            leftState.setList(currentState.moveLeft())
        else:
            leftState = NULL
        if (not currentState.moveRight() == NULL):
            rightState.setList(currentState.moveRight())
        else:
            rightState = NULL
        if (not currentState.moveUp() == NULL):
            upState.setList(currentState.moveUp())
        else:
            upState = NULL
        if (not currentState.moveDown() == NULL):
            downState.setList(currentState.moveDown())
        else:
            downState = NULL
        
        # Returning the best state to step to
        return self.goDeeper(previousStates, statesOnTheWay, leftState, rightState, upState, downState, goalState, timesThrough + 1)

# Game class
class Game:
    
    # Initializing the variables needed for the game
    helper = HelpfulFunctions()
    mover = MoveCalc()
    statesOnTheWay = []
    previousStates = []
    currentState = GameState()
    goalState = GameState()
    
    # Constructor
    def __init__(self):   
        # Set up the puzzle game
        self.setUp()
        
    # Displays every single step taken, including the initial and goal states
    def viewAllSteps(self):
        # Displaying the current state
        print("Initial State (Step 0)")
        self.currentState.displayState()
        print("")
        
        # Displaying every step
        self.viewPreviousSteps()
        
        # Displaying the goal state
        print("Goal State (Step ", len(self.statesOnTheWay) - 1, ")", sep = "")
        self.goalState.displayState()
        print("")
    
    # Displays all of the game states in previousStates in reverse order
    def viewPreviousSteps(self):
        count = 0
        # Looping backwards through the previous states
        #for x in range(len(self.statesOnTheWay) - 1, -1, -1):
        for x in range(1, len(self.statesOnTheWay) - 1):
            tempState = GameState(self.statesOnTheWay[x])
            count = count + 1
            print("Step Number", count)
            tempState.displayState()
            print("")
        
    # The set up for the game
    def setUp(self):
        # Setting the recursion limit
        self.helper.setRecursionLimit(MAX_RECURSION)
        
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
        self.currentState = GameState(startStateList, TRUE_RANDOM)
    
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
        
        # Making sure the output stays somewhat nice and organized
        self.helper.clearScreen()
            
        # Creating the end (goal) state
        self.goalState = GameState(goalStateList, TRUE_RANDOM)
        
        # If it's not true random, shuffel both states
        if (not TRUE_RANDOM):
            self.currentState.shuffle(SHUFFLE_TIMES - 1)
            self.goalState.shuffle(SHUFFLE_TIMES - 1)
        
        # Adding the initial state to the list of states on the way
        self.statesOnTheWay.append(self.currentState.getState())
    
        # Displaying the initial state
        print("Initial State:")
        self.currentState.displayState()
        print("")
    
        # Displaying the initial state
        print("Goal State:")
        self.goalState.displayState()
        print("")
        
    def playGame(self):
        # Letting the user know the AI is currently trying to solve the puzzle
        print("Currently trying to solve the puzzle...")
        
        # Keeping track of whether or not it was solved
        solved = False
        
        # Trying to solve the puzzle
        while (not solved):
            if (self.mover.solve(self.previousStates, self.statesOnTheWay, self.currentState, self.goalState)):
                print("Puzzle solved!")
                print("")
                solved = True
                self.viewAllSteps()
            else:
                solved = True # TEMP LINE
                print("Unsolvable puzzle.")
            

#def n_puzzle(): # Will use eventually, got tired of typing "n_puzzle()" every time to test
def s():
    # Creating and playing the game
    game = Game()
    game.playGame()
    
    
    
    
    