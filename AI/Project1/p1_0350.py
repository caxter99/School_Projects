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

# Just a bunch of helpful functions
from random import randint # just for this class
class HelpfulFunctions:
    
    def __init__(self):
        # Empty, nothing to do
        i = 0
    
    # Compares four values and returns the largest value of the four
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
    def createRandomList(self):
        # Getting the starting value (any int from 0 to 8)
        startingVal = randint(0, 8)
        
        # Getting the incremental value (1 or 2)
        incrementVal = randint(1, 2)
        
        # Creating the new, random list
        #newList= [] # TEMP COMMENT
        #for x in range(NUM_OF_X_GRID * NUM_OF_Y_GRID): # TEMP COMMENT
            # They must be entered as strings, because if the user entered the
            # other grid, the other grid will be all strings. The rest of the
            # program assumes these values will be strings
            #newList.append(str((startingVal + (incrementVal * x)) % 9)) # TEMP COMMENT
        
        # TESTING SECTION
        if (incrementVal == 1):
            newList = [1, 2, 3, 5, 6, 0, 7, 8, 4]
        else:
            newList = [1, 2, 3, 5, 0, 6, 7, 8, 4]
        # END TESTING
        
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
        
        return newList


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
        
    # Resets the list to a new list (can also be used as a reset)
    def setList(self, newList = []):
        # If the list was not pregenerated or pregenerated incorrectly,
        # make a new list
        if (not self.helper.isValidList(newList)):
            self.state = self.helper.createRandomList()
        # The list is valid, set to the game state's list
        else:
            self.state = newList
        
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
            return True
        
        # If there's legit lists inside of it
        for y in range(len(previousLists)):
            for x in range(len(previousLists[y])):
                tempGameState = GameState(previousLists[y][x])
                
                # It matches a previous game state
                if (self.compare(tempGameState)):
                    return False
        
        # It doesn't match any previous game state
        return True
    
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
    def chooseBestState(self, previousState, state1, state2, state3, state4, goalState):
        nullState1 = False
        nullState2 = False
        nullState3 = False
        nullState4 = False
        if (state1 == NULL):
            nullState1 = True
        if (state2 == NULL):
            nullState2 = True
        if (state3 == NULL):
            nullState3 = True
        if (state4 == NULL):
            nullState4 = True
            
        step1 = MAX_STEPS
        step2 = MAX_STEPS
        step3 = MAX_STEPS
        step4 = MAX_STEPS
        
        if (not nullState1):
            step1 = state1.calcManhattenSteps(goalState)
        if (not nullState2):
            step2 = state2.calcManhattenSteps(goalState)
        if (not nullState3):
            step3 = state3.calcManhattenSteps(goalState)
        if (not nullState4):
            step4 = state4.calcManhattenSteps(goalState)
        
        if ((not nullState1) and (not state1.compare(previousState)) and self.helper.compareFourLoose(step1, step2, step3, step4)):
            return state1
        elif ((not nullState2) and (not state2.compare(previousState)) and self.helper.compareFourLoose(step2, step1, step3, step4)):
            return state2
        elif ((not nullState3) and (not state3.compare(previousState)) and self.helper.compareFourLoose(step3, step2, step1, step4)):
            return state3
        elif ((not nullState4) and (not state4.compare(previousState)) and self.helper.compareFourLoose(step4, step2, step3, step1)):
            return state4
        
        # At this point, there's not a clear best choice. This is where things get fun
        state1MatchesPrevious = False
        state2MatchesPrevious = False
        state3MatchesPrevious = False
        state4MatchesPrevious = False
        
        if ((not nullState1) and state1.compare(previousState)):
            state1MatchesPrevious = True
            step1 = MAX_STEPS
        if ((not nullState2) and state2.compare(previousState)):
            state2MatchesPrevious = True
            step2 = MAX_STEPS
        if ((not nullState3) and state3.compare(previousState)):
            state3MatchesPrevious = True
            step3 = MAX_STEPS
        if ((not nullState4) and state4.compare(previousState)):
            state4MatchesPrevious = True
            step4 = MAX_STEPS
        
        pos1 = True
        pos2 = True
        pos3 = True
        pos4 = True
        
        if (nullState1 or state1MatchesPrevious):
            pos1 = False
        if (nullState2 or state2MatchesPrevious):
            pos2 = False
        if (nullState3 or state3MatchesPrevious):
            pos3 = False
        if (nullState4 or state4MatchesPrevious):
            pos4 = False
        
        # Hopefully, at least one of them is an option
        if (pos1 or pos2 or pos3 or pos4):
            if (pos1):
                return state1
            elif (pos2):
                return state2
            elif (pos3):
                return state3
            else:
                return state4
        
        # They're all false and there's no options
        return NULL
    
    def lookAheadOneStep(self, previousState, state1, state2, state3, state4, goalState, timesThrough = 0):
        nullState1 = False
        nullState2 = False
        nullState3 = False
        nullState4 = False
        newState1 = GameState()
        newState2 = GameState()
        newState3 = GameState()
        newState4 = GameState()
        
        if (state1 == NULL):
            nullState1 = True
            newState1 = NULL
        if (state2 == NULL):
            nullState2 = True
            newState2 = NULL
        if (state3 == NULL):
            nullState3 = True
            newState3 = NULL
        if (state4 == NULL):
            nullState4 = True
            newState4 = NULL
        
        if (not nullState1):
            newState1, dud = self.makeBestMove(previousState, state1, goalState, timesThrough)
        if (not nullState2):
            newState2, dud = self.makeBestMove(previousState, state2, goalState, timesThrough)
        if (not nullState3):
            newState3, dud = self.makeBestMove(previousState, state3, goalState, timesThrough)
        if (not nullState4):
            newState4, dud = self.makeBestMove(previousState, state4, goalState, timesThrough)
        
        bestGameStateChoice = self.chooseBestState(previousState, newState1, newState2, newState3, newState4, goalState)
        
        if (bestGameStateChoice == NULL):
                return NULL
        
        if ((not nullState1) and bestGameStateChoice.compare(newState1)):
            return state1
        if ((not nullState2) and bestGameStateChoice.compare(newState2)):
            return state2
        if ((not nullState3) and bestGameStateChoice.compare(newState3)):
            return state3
        return state4
    
    # Calculates the best move and returns the new state
    def makeBestMove(self, previousState, currentState, goalState, timesThrough = 0):
        print("\n\n\n\n\n\n\nmake best function")
        # If the currentState matches the goal state, return it immediately (cause it's the best move)
        if (currentState.compare(goalState)):
            return currentState, timesThrough
        
        # Getting lists of each of the possible states
        leftStateList = currentState.moveLeft()
        rightStateList = currentState.moveRight()
        downStateList = currentState.moveDown()
        upStateList = currentState.moveUp()
        
        # Variables to possibly hold new states
        leftState = GameState()
        rightState = GameState()
        upState = GameState()
        downState = GameState()
        
        # Creating states out the lists, so long as they aren't null
        print("current state:")
        currentState.displayState()
        print("goal state:")
        goalState.displayState()
        if (not leftStateList == NULL):
            leftState.setList(leftStateList)
            print("left state:")
            print("steps: ", leftState.calcManhattenSteps(goalState))
            leftState.displayState()
        else:
            leftState = NULL
        if (not rightStateList == NULL):
            rightState.setList(rightStateList)
            print("right state:")
            print("steps: ", rightState.calcManhattenSteps(goalState))
            rightState.displayState()
        else:
            rightState = NULL
        if (not upStateList == NULL):
            upState.setList(upStateList)
            print("up state:")
            print("steps: ", upState.calcManhattenSteps(goalState))
            upState.displayState()
        else:
            upState = NULL
        if (not downStateList == NULL):
            downState.setList(downStateList)
            print("down state:")
            print("steps: ", downState.calcManhattenSteps(goalState))
            downState.displayState()
        else:
            downState = NULL
        
        # Creating variables to hold how many steps remain for each possible move. If the state
        # is null, then they won't be changed from MAX_STEPS
        leftSteps = MAX_STEPS
        rightSteps = MAX_STEPS
        upSteps = MAX_STEPS
        downSteps = MAX_STEPS
        
        # Seeing how many Manhattan steps each state has, making sure they're not null first
        if (not leftStateList == NULL):
            leftSteps = leftState.calcManhattenSteps(goalState)
        if (not rightStateList == NULL):
            rightSteps = rightState.calcManhattenSteps(goalState)
        if (not upStateList == NULL):
            upSteps = upState.calcManhattenSteps(goalState)
        if (not downStateList == NULL):
            downSteps = downState.calcManhattenSteps(goalState)
        
        # Creating variables for figuring out which move is the best move
        clearBestMove = False
        upMoveIsBest = False
        downMoveIsBest = False
        rightMoveIsBest = False
        leftMoveIsBest = False
        
        # Figuring out which move is the best move
        #if ((not previousState.compare(leftState)) and self.helper.compareFourTight(leftSteps, rightSteps, upSteps, downSteps)):
        if ((not leftState == NULL) and (not leftState.compare(previousState)) and self.helper.compareFourLoose(leftSteps, rightSteps, upSteps, downSteps)):
            clearBestMove = True
            leftMoveIsBest = True
        #elif ((not previousState.compare(rightState)) and self.helper.compareFourTight(rightSteps, leftSteps, upSteps, downSteps)):
        elif ((not rightState == NULL) and (not rightState.compare(previousState)) and self.helper.compareFourLoose(rightSteps, leftSteps, upSteps, downSteps)):
            clearBestMove = True
            rightMoveIsBest = True
        #elif ((not previousState.compare(upState)) and self.helper.compareFourTight(upSteps, leftSteps, rightSteps, downSteps)):
        elif ((not upState == NULL) and (not upState.compare(previousState)) and self.helper.compareFourLoose(upSteps, leftSteps, rightSteps, downSteps)):
            clearBestMove = True
            upMoveIsBest = True
        #elif ((not previousState.compare(downState)) and self.helper.compareFourTight(downSteps, leftSteps, upSteps, rightSteps)):
        elif ((not downState == NULL) and (not downState.compare(previousState)) and self.helper.compareFourLoose(downSteps, leftSteps, upSteps, rightSteps)):
            clearBestMove = True
            downMoveIsBest = True
        
        # If there's not a clear best move and it's the first time
        if ((not clearBestMove) and timesThrough == 0):
            #raise Exception("Shouldn't be here")
            # Getting the best move (the function also returns an integer, but that's not necesary for
            # what comes after this)
            bestMoveState = self.lookAheadOneStep(previousState, rightState, leftState, upState, downState, goalState, timesThrough + 1)
            
            if (bestMoveState == NULL):
                return NULL, timesThrough
            
            # Figuring out which move is the best move
            if ((not leftState == NULL) and bestMoveState.compare(leftState)):
                leftMoveIsBest = True
            elif ((not rightState == NULL) and bestMoveState.compare(rightState)):
                rightMoveIsBest = True
            elif ((not upState == NULL) and bestMoveState.compare(upState)):
                upMoveIsBest = True
            elif ((not downState == NULL) and bestMoveState.compare(downState)):
                downMoveIsBest = True
            
            if (bestMoveState == NULL):
                return NULL, timesThrough
        elif (not clearBestMove):
            bestMoveState = self.chooseBestState(previousState, rightState, leftState, upState, downState, goalState)
                        
            if (bestMoveState == NULL):
                return NULL, timesThrough
            
            # Figuring out which move is the best move
            if ((not leftState == NULL) and bestMoveState.compare(leftState)):
                leftMoveIsBest = True
            elif ((not rightState == NULL) and bestMoveState.compare(rightState)):
                rightMoveIsBest = True
            elif ((not upState == NULL) and bestMoveState.compare(upState)):
                upMoveIsBest = True
            elif ((not downState == NULL) and bestMoveState.compare(downState)):
                downMoveIsBest = True
        
        # Returning the best move
        if (leftMoveIsBest):
            print("move left")
            return leftState, timesThrough
        elif (rightMoveIsBest):
            print("move right")
            return rightState, timesThrough
        elif (upMoveIsBest):
            print("move up")
            return upState, timesThrough
        elif (downMoveIsBest):
            print("move down")
            return downState, timesThrough
        print("null")
        return NULL, timesThrough

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
        
        # This is the tempPreviousState
        tempPreviousState = GameState()
        
        # This will loop while the current and goal state do not match
        while(not self.currentState.compare(self.goalState)):
            tempPreviousState.setList(self.currentState.getState())
            self.currentState, dud = self.mover.makeBestMove(self.previousState, self.currentState, self.goalState)
            self.previousState.setList(tempPreviousState.getState())
        
        print("Game won!")
            

#def n_puzzle(): # Will use eventually, got tired of typing "n_puzzle()" every time to test
def s():
    # Creating and playing the game
    game = Game()
    game.playGame()
    
    
    
    
    