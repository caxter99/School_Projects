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
FILENAME = "8puzzlelog.txt" # The name of the file the game is written to
MAX_STEPS = float('inf') # This is used for states that have no way of finishing
# (or other error methods for checking steps remaining)
TRUE_RANDOM = False # This is to say if the created states (if not created by
# the user) will be randomly made or not
ALWAYS_BE_SMART = False # If true, it will ask the user before running the
# uninformed search (because that could take an extremely long time)
RANDOM_SELECT_INT = 0 # The integer to signify that it should do random selection
SMART_SELECT_INT = RANDOM_SELECT_INT + 1 # The integer to signify that it should
# do smart selection
SHOULD_SHUFFLE = False # If the game should shuffle the states before the game
# starts
SHUFFLE_TIMES = 30 # The number of times the goal state will be shuffled to
# create the starting state (if applicable)
MAX_RECURSION = (9 * 8 * 7 * 6 * 5 * 4 * 3 * 2) + 2 # The maximum number of times
# recursion can occur
RECURSION_SAFETY_NET = MAX_RECURSION * 0.1 # The number away from MAX_RECURSION
# that the program will stop the program from trying to spawn a new state from
# the current one
ORGINAL_DEPTH_CAP = 0 # This is the depth cap
                
# All imports
from random import randint
import sys
import time
import math

# Just a bunch of helpful functions
class HelpfulFunctions:
    
    # Set the recursion limit
    def setRecursionLimit(self, limit):
        sys.setrecursionlimit(limit)
    
    # Compares four values and returns the largest value of the four (does not
    # count values equal to MAX_STEPS)
    def getLargest(self, first, second, third, fourth):
        # Making sure none of the values are infinite, otherwise that'll screw
        # up the calculations
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
    
    # Compares four values and returns true if the first value is the smallest
    # or tied smallest
    def compareFourLoose(self, first, second, third, fourth):
        # Comparing all of the values against the first value
        if (first <= second and first <= third and first <= fourth):
            return True
        
        # It's not the smallest value or tied with the smallest value
        return False
    
    # Creates a random, valid list and returns it
    def createRandomList(self, trueRandom = False):
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
                # They must be entered as strings, because if the user entered
                # the other grid, the other grid will be all strings. The rest
                # of the program assumes these values will be strings
                newList.append(str((startingVal + (incrementVal * x)) % (NUM_OF_X_GRID * NUM_OF_Y_GRID)))
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
class GameState:
    
    # Just some helper functions and variables
    helper = HelpfulFunctions()
    state = []
    
    # Constructor, can take nothing or a pre-generated list
    def __init__(self, initialList = [], trueRandom = False):
        # If the list was not pregenerated or pregenerated incorrectly,
        # make a new list
        if (not self.helper.isValidList(initialList)):
            # Make a new list
            self.state = self.helper.createRandomList(trueRandom)
        # Otherwise, the list is good to go
        else:
            # The list has laready been made
            self.state = initialList
    
    # Writes the state to the given file as though it were being printed out
    def writeState(self, file):
        # This is to keep track of what element the list is on
        count = 0
        
        # Looping through and grabbing all of the values in the list
        for x in self.state:
            file.write(str(x) + " ")
            # Prints a newline every 3 outputs, to keep in touch with the game
            if ((count + 1) % NUM_OF_Y_GRID == 0):
                file.write("\n")
            count = count + 1
    
    # Returns a tring of the state
    def getStringState(self):
        # This is to keep track of what element the list is on
        count = 0
        string = ""
        
        # Looping through and grabbing all of the values in the list
        for x in self.state:
            string = string + str(x) + " "
            # Prints a newline every 3 outputs, to keep in touch with the game
            if ((count + 1) % NUM_OF_Y_GRID == 0):
                string = string + "\n"
            count = count + 1
        
        # Return the string
        return string
    
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
            # Picks a random way to shuffle
            randomInt = randint(1, 4) # From 1 to 4 inclusive
            
            # Left (if possible)
            if (randomInt == 1):
                posList = self.moveLeft()
                if (not (posList == NULL)):
                    self.setList(self.moveLeft())
            # Right (if possible)
            elif (randomInt == 2):
                posList = self.moveRight()
                if (not (posList == NULL)):
                    self.setList(self.moveRight())
            # Up (if possible)
            elif (randomInt == 3):
                posList = self.moveUp()
                if (not (posList == NULL)):
                    self.setList(self.moveUp())
            # Down (if possible)
            else:
                posList = self.moveDown()
                if (not (posList == NULL)):
                    self.setList(self.moveDown())
    
    # Creates a list for a state that would look like as though a move to the
    # left was made
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
                        
                        # Switching the positions of the 0 and the spot to the
                        # left
                        leftStateList[position - 1], leftStateList[position] = leftStateList[position], leftStateList[position - 1]
                        
        # Returning the left state (as null or a new state)
        return leftStateList
    
    # Creates a list for a state that would look like as though a move to the
    #right was made
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
                        
                        # Switching the positions of the 0 and the spot to the
                        # right
                        rightStateList[position], rightStateList[position + 1] = rightStateList[position + 1], rightStateList[position]
                        
        # Returning the left state (as null or a new state)
        return rightStateList
    
    # Creates a list for a state that would look like as though a move up was
    # made
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
    
    # Creates a list for a state that would look like as though a move down was
    # made
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
                        
                        # Switching the positions of the 0 and the spot down
                        # one
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
                if (not (str(numAtCurrentPoint) == "0")):
                     # Looping through the goal state to find out where that
                     # same number is in the goal state
                     for x2 in range(NUM_OF_X_GRID):
                         for y2 in range(NUM_OF_Y_GRID):
                             # Getting the number at the point in the goalt
                             # state's list
                             numAtGoalPoint = goalState.getState()[x2 + NUM_OF_Y_GRID * y2]
                             
                             # If they're the same (and not 0), calculate and
                             # add the distance
                             if (numAtCurrentPoint == numAtGoalPoint):
                                 # x distance
                                 newDistance = newDistance + math.sqrt(math.pow(x1 - x2, 2))
                                 
                                 # y distance
                                 newDistance = newDistance + math.sqrt(math.pow(y1 - y2, 2))
        
        # Return the total new distance as an integer
        return int(newDistance)
    
    # Returns the number of steps to the goal puzzle, the Hamming way.
    # This assumes that the object executing this function is the current
    # state
    def calcHammingSteps(self, goalState):
        # Initially, the total distance is 0
        newDistance = 0
        
        # Looping through each point, calculating its distance
        for x1 in range(NUM_OF_X_GRID):
            for y1 in range(NUM_OF_Y_GRID):
                # Getting the number at the point in the current list
                numAtCurrentPoint = self.state[x1 + NUM_OF_Y_GRID * y1]
                
                # Making sure the number 0 isn't counted
                if (not (str(numAtCurrentPoint) == "0")):
                    # Getting the number at the point in the goalt state's list
                    numAtGoalPoint = goalState.getState()[x1 + NUM_OF_Y_GRID * y1]
                             
                    # If they're the same (and not 0), add one to the distance
                    if (not numAtCurrentPoint == numAtGoalPoint):
                        # Adding one to the distance
                        newDistance = newDistance + 1
        
        # Return the total new distance as an integer
        return int(newDistance)
    
    # Takes in a lists of lists with the previous game states stored inside of
    # them. Returns true if the current state matches none of the state found
    # inside the list of lists
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
    
    # Receives the previous state, 4 possible new states, and the goal state
    # and returns the best
    def goDeeper(self, previousStates, statesOnTheWay, state1, state2, state3, state4, goalState, selectionType, depth, depthCap):
        # Making sure the depth cap hasn't been reached before it dives deeper
        if (depth >= depthCap):
            return False
        
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
        
        # Checking to see if state1 is null
        if (state1 == NULL):
            isNull1 = True
        else:
            # Making sure state1 isn't a dusplicate of the previous state
            if (state1.comparePrevious(previousStates)):
                duplicateOfPreviousState1 = True
            else:
                # If it checks out, get the Manhatten steps
                step1 = state1.calcManhattenSteps(goalState)
        
        # Checking to see if state2 is null
        if (state2 == NULL):
            isNull2 = True
        else:
            # Making sure state2 isn't a dusplicate of the previous state
            if (state2.comparePrevious(previousStates)):
                duplicateOfPreviousState2 = True
            else:
                # If it checks out, get the Manhatten steps
                step2 = state2.calcManhattenSteps(goalState)
        
        # Checking to see if state3 is null
        if (state3 == NULL):
            isNull3 = True
        else:
            # Making sure state3 isn't a dusplicate of the previous state
            if (state3.comparePrevious(previousStates)):
                duplicateOfPreviousState3 = True
            else:
                # If it checks out, get the Manhatten steps
                step3 = state3.calcManhattenSteps(goalState)
        
        # Checking to see if state4 is null
        if (state4 == NULL):
            isNull4 = True
        else:
            # Making sure state4 isn't a dusplicate of the previous state
            if (state4.comparePrevious(previousStates)):
                duplicateOfPreviousState4 = True
            else:
                # If it checks out, get the Manhatten steps
                step4 = state4.calcManhattenSteps(goalState)
        
        # Checking the viability of each state to the be the next state. If
        # anything doesn't check out, it's ruled out as a possiblity
        if (isNull1 or duplicateOfPreviousState1 or step1 == MAX_STEPS):
            pos1 = False
        if (isNull2 or duplicateOfPreviousState2 or step2 == MAX_STEPS):
            pos2 = False
        if (isNull3 or duplicateOfPreviousState3 or step3 == MAX_STEPS):
            pos3 = False
        if (isNull4 or duplicateOfPreviousState4 or step4 == MAX_STEPS):
            pos4 = False
        
        # The selection type is random
        if (selectionType == RANDOM_SELECT_INT):
            if (pos1):
                # Adding state1 to the list of states on the way
                statesOnTheWay.append(state1.getState())
            
                # Checking to see if state1 will lead to the goal state
                if (self.solve(previousStates, statesOnTheWay, state1, goalState, selectionType, depth, depthCap)):
                    # It lead to the goal state
                    return True
                else:
                    # Removing state1 because it wasn't on the way
                    statesOnTheWay.remove(state1.getState())
            if (pos2):
                # Adding state2 to the list of states on the way
                statesOnTheWay.append(state2.getState())
            
                # Checking to see if state2 will lead to the goal state
                if (self.solve(previousStates, statesOnTheWay, state2, goalState, selectionType, depth, depthCap)):
                    # It lead to the goal state
                    return True
                else:
                    # Removing state2 because it wasn't on the way
                    statesOnTheWay.remove(state2.getState())
            if (pos3):
                # Adding state3 to the list of states on the way
                statesOnTheWay.append(state3.getState())
                
                # Checking to see if state3 will lead to the goal state
                if (self.solve(previousStates, statesOnTheWay, state3, goalState, selectionType, depth, depthCap)):
                    # It lead to the goal state
                    return True
                else:
                    # Removing state3 because it wasn't on the way
                    statesOnTheWay.remove(state3.getState())
            if (pos4):
                # Adding state4 to the list of states on the way
                statesOnTheWay.append(state4.getState())
            
                # Checking to see if state4 will lead to the goal state
                if (self.solve(previousStates, statesOnTheWay, state4, goalState, selectionType, depth, depthCap)):
                    # It lead to the goal state
                    return True
                else:
                    # Removing state4 because it wasn't on the way
                    statesOnTheWay.remove(state4.getState())
        # The selection type is smart
        elif (selectionType == SMART_SELECT_INT):
            # Gathering if there are still options left
            optionsLeftToTry = ((pos1 or pos2) or (pos3 or pos4))
            
            # Looping while there are still options to try
            while(optionsLeftToTry):
                    
                if (pos1 and self.helper.compareFourLoose(step1, step2, step3, step4)):
                    # Adding state1 to the list of states on the way
                    statesOnTheWay.append(state1.getState())
            
                    # Checking to see if state1 will lead to the goal state
                    if (self.solve(previousStates, statesOnTheWay, state1, goalState, selectionType, depth, depthCap)):
                        # It lead to the goal state
                        return True
                    else:
                        # Removing state1 because it wasn't on the way
                        statesOnTheWay.remove(state1.getState())
                        
                        # Making sure the number of steps doesn't mess up any
                        # future calculations and that state1 is no longer an
                        # option to pick
                        step1 = MAX_STEPS
                        pos1 = False
                if (pos2 and self.helper.compareFourLoose(step2, step1, step3, step4)):
                    # Adding state2 to the list of states on the way
                    statesOnTheWay.append(state2.getState())
            
                    # Checking to see if state2 will lead to the goal state
                    if (self.solve(previousStates, statesOnTheWay, state2, goalState, selectionType, depth, depthCap)):
                        # It lead to the goal state
                        return True
                    else:
                        # Removing state2 because it wasn't on the way
                        statesOnTheWay.remove(state2.getState())
                        
                        # Making sure the number of steps doesn't mess up any
                        # future calculations and that state2 is no longer an
                        # option to pick
                        step2 = MAX_STEPS
                        pos2 = False
                if (pos3 and self.helper.compareFourLoose(step3, step2, step1, step4)):
                    # Adding state3 to the list of states on the way
                    statesOnTheWay.append(state3.getState())
                
                    # Checking to see if state3 will lead to the goal state
                    if (self.solve(previousStates, statesOnTheWay, state3, goalState, selectionType, depth, depthCap)):
                        # It lead to the goal state
                        return True
                    else:
                        # Removing state3 because it wasn't on the way
                        statesOnTheWay.remove(state3.getState())
                        
                        # Making sure the number of steps doesn't mess up any
                        # future calculations and that state3 is no longer an
                        # option to pick
                        step3 = MAX_STEPS
                        pos3 = False
                if (pos4 and self.helper.compareFourLoose(step4, step2, step3, step1)):
                    # Adding state4 to the list of states on the way
                    statesOnTheWay.append(state4.getState())
            
                    # Checking to see if state4 will lead to the goal state
                    if (self.solve(previousStates, statesOnTheWay, state4, goalState, selectionType, depth, depthCap)):
                        # It lead to the goal state
                        return True
                    else:
                        # Removing state4 because it wasn't on the way
                        statesOnTheWay.remove(state4.getState())
                        
                        # Making sure the number of steps doesn't mess up any
                        # future calculations and that state4 is no longer an
                        # option to pick
                        step4 = MAX_STEPS
                        pos4 = False
                        
                # Gathering if there are still options left
                optionsLeftToTry = ((pos1 or pos2) or (pos3 or pos4))
        
        # No state led to the goal state
        return False
    
    # Calculates the best move and returns the new state
    def solve(self, previousStates, statesOnTheWay, currentState, goalState, selectionType, depth, depthCap):
        # Checking to see if the current state matches the goal state
        if (currentState.compare(goalState)):
            return True
        
        # Adding the current state to the list of previous states
        previousStates.append(currentState.getState())
        
        # Making sure the program isn't near the limit for recursion
        if (depth * 2 >= MAX_RECURSION - RECURSION_SAFETY_NET):
            # If it is, can't go on any longer or risk crashing
            print("gone too far, could max recursion")
            return False
        
        # All of new vriables to hold the new game states
        leftState = GameState()
        rightState = GameState()
        upState = GameState()
        downState = GameState()
        
        # Figuring out what moves are possible and which aren't (and are
        # therefore null)
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
        return self.goDeeper(previousStates, statesOnTheWay, leftState, rightState, upState, downState, goalState, selectionType, depth + 1, depthCap)

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
        
    # Views and writes the steps of the puzzle
    def viewAndWriteSteps(self, selectionType, writeType = "w"):
        # Writing all of the steps to the file
        self.writeGameToFile(selectionType, writeType)
        
        # Viewing all of the steps
        self.viewAllSteps()
    
    # Writes the entire content to the file
    def writeGameToFile(self, selectionType, writeType = "w"):
        # Creating the file
        file = open(FILENAME, writeType)
        
        # Writing what type of selection was used (and keeping the formatting
        # nice)
        file.write("Puzzle solved using ")
        if (selectionType == SMART_SELECT_INT):
            file.write("Progressive Deepening Search:")
        elif (selectionType == RANDOM_SELECT_INT):
            file.write("Uninformed Search:")
        else:
            file.write("an unknown method for selection:")
        file.write("\n\n")
            
        # Writing the initial state
        file.write("Initial State (Step 0)\n")
        extraString = "Manhatten Steps: " + str(self.currentState.calcManhattenSteps(self.goalState)) + "\n"
        file.write(extraString)
        extraString = "Hamming Steps: " + str(self.currentState.calcHammingSteps(self.goalState)) + "\n"
        file.write(extraString)
        self.currentState.writeState(file)
        file.write("\n")
        
        # Getting all of the middle steps in a string, as well as the total
        # Manhatten and Hamming distances
        extraString, manhattenSteps, hammingSteps = self.createMiddleStepsString(self.currentState.calcManhattenSteps(self.goalState), self.currentState.calcHammingSteps(self.goalState))
        file.write(extraString)
        
        # Writing the goal state
        extraString = "Goal State (Step " + str(len(self.statesOnTheWay)) + ")\n"
        file.write(extraString)
        extraString = "Manhatten Steps: " + str(manhattenSteps) + "\n"
        file.write(extraString)
        extraString = "Hamming Steps: " + str(hammingSteps) + "\n"
        file.write(extraString)
        self.goalState.writeState(file)
        file.write("\n")
        
        # Closing the file
        file.close()
    
    # Displays every single step taken, including the initial and goal states
    def viewAllSteps(self):
        # Displaying the current state
        print("Initial State (Step 0)")
        print("Manhatten Steps:", self.currentState.calcManhattenSteps(self.goalState))
        print("Hamming Steps:", self.currentState.calcHammingSteps(self.goalState))
        self.currentState.displayState()
        print("")
        
        # Displaying every step
        middleString, manhattenSteps, hammingSteps = self.createMiddleStepsString(self.currentState.calcManhattenSteps(self.goalState), self.currentState.calcHammingSteps(self.goalState))
        print(middleString, end="")
        
        # Displaying the goal state
        print("Goal State (Step ", len(self.statesOnTheWay), ")", sep = "")
        print("Manhatten Steps:", manhattenSteps)
        print("Hamming Steps:", hammingSteps)
        self.goalState.displayState()
        print("")
    
    # Returns a string with all of the middle states in a nice string as well
    # as the Manhatten and Hamming steps
    def createMiddleStepsString(self, manhattenSteps = 0, hammingSteps = 0):
        # Keeping track of what step they're on
        count = 0
        string = ""
        
        # Looping forwards through the previous states
        for x in range(0, len(self.statesOnTheWay) - 1):
            # Creating a temporary state with the list
            tempState = GameState(self.statesOnTheWay[x])
            
            # Getting the total Manhatten and Hamming steps
            manhattenSteps = manhattenSteps + tempState.calcManhattenSteps(self.goalState)
            hammingSteps = hammingSteps + tempState.calcHammingSteps(self.goalState)
            
            # Incrementing count
            count = count + 1
            
            # Creating the string for this state and adding it to the current
            # string
            string = string + "Step " + str(count) + "\n"
            string = string + "Manhatten Steps: " + str(manhattenSteps) + "\n"
            string = string + "Hamming Steps: " + str(hammingSteps) + "\n"
            string = string + tempState.getStringState() + "\n"
        
        # Returning the total number of Manhatten and Hamming steps
        return string, manhattenSteps, hammingSteps
        
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
            # They entered something other than a "-1", append it and keep
            # going
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
            # They entered something other than a "-1", append it and keep
            # going
            if (val != "-1"):
                goalStateList.append(val)
            # They entered a "-1", so quit
            else:
                break;
        
        # Making sure the output stays somewhat nice and organized
        self.helper.clearScreen()
            
        # Creating the end (goal) state
        self.goalState = GameState(goalStateList, TRUE_RANDOM)
        
        # If it's not true random, shuffle both states
        if (SHOULD_SHUFFLE):
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
        # Creating variables to store each of the game's total time
        smartSelectTime = 0
        uninformedSelectTime = 0
        
        # Part 1: Smart Selection
        # Letting the user know the AI is currently trying to solve the puzzle
        print("Currently trying to solve the puzzle by using the Progressive Deepening Method...")
        
        # Keeping track of whether or not it was solved
        solved = False
        
        # Setting the depth cap to the original
        depthCap = ORGINAL_DEPTH_CAP
        
        # Getting the original time the program started
        startTime = time.time()
        
        # Trying to solve the puzzle
        while (not solved):
            if (self.mover.solve(self.previousStates, self.statesOnTheWay, self.currentState, self.goalState, SMART_SELECT_INT, 0, depthCap)):
                # Getting the end time
                endTime = time.time()
                
                # Let the user know the puzzle is solved
                print("Puzzle solved!")
                print("")
                
                # Set solved to true
                solved = True
                
                # Saving the time it took
                smartSelectTime = endTime - startTime
                
                # Display and write the steps to a file, then write the time to
                # the same file
                timeString = "Time it took to solve the puzzle: " + str(smartSelectTime) + " seconds\n\n"
                self.viewAndWriteSteps(SMART_SELECT_INT)
                print(timeString)
                file = open(FILENAME, "a")
                file.write(timeString)
                file.close()
                
                # Reset the previous states and states on the way in case the
                # random select method is going next
                self.previousStates = []
                self.statesOnTheWay = []
            else:
                # Increase the depth cap
                depthCap = depthCap + 1
                
                # Reset the previous states and the states on the way
                self.previousStates = []
                self.statesOnTheWay = []
        
        # Asking the user if they would like to try the uninformed search
        overrideAlwaysBeSmart = False
        if (ALWAYS_BE_SMART):
            answer = input("Would you like to try the Uninformed Search?\nWARNING: It may take a LONG time! (y/n): ")
            
            # If the user would like to try the Uninformed Search
            if (answer == "y" or answer == "Y"):
                overrideAlwaysBeSmart = True
        
        # Part 2: Random Selection
        # Making sure we actually want to try and take on this adventure
        if (overrideAlwaysBeSmart or (not ALWAYS_BE_SMART)):
            # Letting the user know the AI is currently trying to solve the
            # puzzle
            print("Currently trying to solve the puzzle by using Uninformed Search...")
        
            # Keeping track of whether or not it was solved
            solved = False
            
            # Setting the depth cap to the original
            depthCap = ORGINAL_DEPTH_CAP
        
            # Getting the original time the program started
            startTime = time.time()
        
            # Trying to solve the puzzle
            while (not solved):
                if (self.mover.solve(self.previousStates, self.statesOnTheWay, self.currentState, self.goalState, RANDOM_SELECT_INT, 0, depthCap)):
                    # Getting the end time
                    endTime = time.time()
                
                    # Let the user know the puzzle is solved
                    print("Puzzle solved!")
                    print("")
                
                    # Set solved to true
                    solved = True
                
                    # Saving the time it took
                    uninformedSelectTime = endTime - startTime
                
                    # Display and write the steps to a file, then write the
                    # time to the same file
                    timeString = "Time it took to solve the puzzle: " + str(uninformedSelectTime) + " seconds\n\n"
                    self.viewAndWriteSteps(RANDOM_SELECT_INT, "a")
                    print(timeString)
                    file = open(FILENAME, "a")
                    file.write(timeString)
                    file.close()
                
                    # Reset the previous states and states on the way in case
                    # the random select method is going next
                    self.previousStates = []
                    self.statesOnTheWay = []
                else:
                    # Increase the depth cap
                    depthCap = depthCap + 1
                
                    # Reset the previous states and the states on the way
                    self.previousStates = []
                    self.statesOnTheWay = []
        
        # Part 3: Comparing the times
        # Making sure that both tests were actually performed
        if (overrideAlwaysBeSmart or (not ALWAYS_BE_SMART)):
            # Getting the difference in the time
            timeDifference = uninformedSelectTime - smartSelectTime
            
            # Creating an string to store what is going to be displayed and
            # written to the file
            extraString = "It took the Uninformed Search " + str(timeDifference) + " seconds longer to complete than the Progressive Deepening Method."
            
            # Displaying to the user the difference in the times
            print(extraString)
            
            # Writing the same thing that was displayed to the file
            file = open(FILENAME, "a")
            file.write(extraString)
            file.close()

# This function starts the entire thing
def n_puzzle():
    # Creating and playing the game
    game = Game()
    game.playGame()
    
    
    
    
    