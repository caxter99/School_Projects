
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
                                 
                                 # TESTING
                                 #print("point 1: (", x1, ", ", y1, ")")
                                 #print("point 2: (", x2, ", ", y2, ")")
                                 #print("distance: ", math.sqrt(math.pow(x1 - x2, 2)) + math.sqrt(math.pow(y1 - y2, 2)))
        
        # Getting the previous amount of Manhattan steps
        self.totalManhattanSteps = self.totalManhattanSteps + newDistance
        
        # TESTING
        #print("total distance: ", self.totalManhattanSteps)
        #print("")
        
        # Return the total new distance
        return newDistance
                

# Move Calculator class
class MoveCalc:
    
    # Variables
    helper = HelpfulFunctions()
    
    # Constructor
    def __init__(self):
        # Nothing now
        i = 0
    
    # Finds which of the four states is the best state and returns it. Note: The states can be null
    def goForwardToFindCurrentBestMove(self, previousState, stateOne, stateTwo, stateThree, stateFour, goalState, timesThrough = 0):
        print("go forward function")
        # Making copies of all of the states to know which one to send back
        stateOneCopy = stateOne
        stateTwoCopy = stateTwo
        stateThreeCopy = stateThree
        stateFourCopy = stateFour
        
        # Keeping track of how many times through each step has been
        oneTimesThrough = MAX_STEPS
        twoTimesThrough = MAX_STEPS
        threeTimesThrough = MAX_STEPS
        fourTimesThrough = MAX_STEPS
        
        # Finding out what the best move is
        if (not stateOne == NULL):
            print("display state")
            stateOne.displayState()
            stateOne, oneTimesThrough = self.makeBestMove(previousState, stateOne, goalState, timesThrough + 1)
        if (not stateTwo == NULL):
            stateTwo, twoTimesThrough = self.makeBestMove(previousState, stateTwo, goalState, timesThrough + 1)
        if (not stateThree == NULL):
            stateThree, threeTimesThrough = self.makeBestMove(previousState, stateThree, goalState, timesThrough + 1)
        if (not stateFour == NULL):
            stateFour, fourTimesThrough = self.makeBestMove(previousState, stateFour, goalState, timesThrough + 1)
        
        # Check here and make sure each state has gone through the same number of iterations before making
        # a decision on which state is best
        allEqual = False
        print("oneTimesThrough: ", oneTimesThrough)
        print("twoTimesThrough: ", twoTimesThrough)
        print("threeTimesThrough: ", threeTimesThrough)
        print("fourTimesThrough: ", fourTimesThrough)
        while(not allEqual):
            allEqual = True
            highestTimesThrough = self.helper.getLargest(oneTimesThrough, twoTimesThrough, threeTimesThrough, fourTimesThrough)
            if (not stateOne == NULL):
                while (oneTimesThrough < highestTimesThrough):
                    allEqual = False
                    stateOne, oneTimesThrough = self.makeBestMove(previousState, stateOne, goalState, oneTimesThrough + 1)
            if (not stateTwo == NULL):
                while (twoTimesThrough < highestTimesThrough):
                    allEqual = False
                    stateTwo, twoTimesThrough = self.makeBestMove(previousState, stateTwo, goalState, twoTimesThrough + 1)
            if (not stateThree == NULL):
                while (threeTimesThrough < highestTimesThrough):
                    allEqual = False
                    stateThree, threeTimesThrough = self.makeBestMove(previousState, stateThree, goalState, threeTimesThrough + 1)
            if (not stateFour == NULL):
                while (fourTimesThrough < highestTimesThrough):
                    allEqual = False
                    stateFour, fourTimesThrough = self.makeBestMove(previousState, stateFour, goalState, fourTimesThrough + 1)
        
        # Creating variables to hold how many steps remain for each possible move. If the state
        # is null, then they won't be changed from MAX_STEPS
        oneSteps = MAX_STEPS
        twoSteps = MAX_STEPS
        threeSteps = MAX_STEPS
        fourSteps = MAX_STEPS
        
        # Seeing how many Manhattan steps each state has, making sure they're not null first
        if (not stateOne == NULL):
            oneSteps = stateOne.calcManhattenSteps(goalState)
            stateOne.displayState()
        if (not stateTwo == NULL):
            twoSteps = stateTwo.calcManhattenSteps(goalState)
            stateTwo.displayState()
        if (not stateThree == NULL):
            threeSteps = stateThree.calcManhattenSteps(goalState)
            stateThree.displayState()
        if (not stateFour == NULL):
            fourSteps = stateFour.calcManhattenSteps(goalState)
            stateFour.displayState()
        
        # Creating variables for figuring out which move is the best move
        clearBestMove = False
        oneMoveIsBest = False
        twoMoveIsBest = False
        threeMoveIsBest = False
        fourMoveIsBest = False
        
        # Figuring out which move is the best move
        if (not stateOne == NULL):
            if (not previousState.compare(stateOne) and self.helper.compareFourTight(oneSteps, twoSteps, threeSteps, fourSteps)):
                print("one")
                clearBestMove = True
                oneMoveIsBest = True
        if (not stateTwo == NULL):
            if (not previousState.compare(stateTwo) and self.helper.compareFourTight(twoSteps, oneSteps, threeSteps, fourSteps)):
                print("two")
                clearBestMove = True
                twoMoveIsBest = True
        if (not stateThree == NULL):
            if (not previousState.compare(stateThree) and self.helper.compareFourTight(threeSteps, twoSteps, oneSteps, fourSteps)):
                print("three")
                clearBestMove = True
                threeMoveIsBest = True
        if (not stateFour == NULL):
            if (not previousState.compare(stateFour) and self.helper.compareFourTight(fourSteps, twoSteps, threeSteps, oneSteps)):
                print("four")
                clearBestMove = True
                fourMoveIsBest = True
        
        # There's no clear best move
        if (not clearBestMove):
            # More variables
            bestOfStateOne = GameState()
            bestOfStateTwo = GameState()
            bestOfStateThree = GameState()
            bestOfStateFour = GameState()
            tempStateOne = GameState()
            tempStateTwo = GameState()
            tempStateThree = GameState()
            tempStateFour = GameState()
            
            # Figuring out the true best state
            if (not stateOne == NULL):
                tempStateOneList = stateOneCopy.moveLeft()
                tempStateTwoList = stateOneCopy.moveRight()
                tempStateThreeList = stateOneCopy.moveUp()
                tempStateFourList = stateOneCopy.moveDown()
                if (tempStateOneList == NULL):
                    tempStateOne = NULL
                if (tempStateTwoList == NULL):
                    tempStateTwo = NULL
                if (tempStateThreeList == NULL):
                    tempStateThree = NULL
                if (tempStateFourList == NULL):
                    tempStateFour = NULL
                bestOfStateOne, oneTimesThrough = self.goForwardToFindCurrentBestMove(stateOneCopy, tempStateOne, tempStateTwo, tempStateThree, tempStateFour, goalState, timesThrough + 1)
            else:
                bestOfStateOne = NULL
                oneTimesThrough = MAX_STEPS
            if (not stateTwo == NULL):
                tempStateOneList = stateTwoCopy.moveLeft()
                tempStateTwoList = stateTwoCopy.moveRight()
                tempStateThreeList = stateTwoCopy.moveUp()
                tempStateFourList = stateTwoCopy.moveDown()
                if (tempStateOneList == NULL):
                    tempStateOne = NULL
                if (tempStateTwoList == NULL):
                    tempStateTwo = NULL
                if (tempStateThreeList == NULL):
                    tempStateThree = NULL
                if (tempStateFourList == NULL):
                    tempStateFour = NULL
                bestOfStateTwo, twoTimesThrough = self.goForwardToFindCurrentBestMove(stateTwoCopy, tempStateOne, tempStateTwo, tempStateThree, tempStateFour, goalState, timesThrough + 1)
            else:
                bestOfStateTwo = NULL
                twoTimesThrough = MAX_STEPS
            if (not stateThree == NULL):
                tempStateOneList = stateThreeCopy.moveLeft()
                tempStateTwoList = stateThreeCopy.moveRight()
                tempStateThreeList = stateThreeCopy.moveUp()
                tempStateFourList = stateThreeCopy.moveDown()
                if (tempStateOneList == NULL):
                    tempStateOne = NULL
                if (tempStateTwoList == NULL):
                    tempStateTwo = NULL
                if (tempStateThreeList == NULL):
                    tempStateThree = NULL
                if (tempStateFourList == NULL):
                    tempStateFour = NULL
                bestOfStateThree, threeTimesThrough = self.goForwardToFindCurrentBestMove(stateThreeCopy, tempStateOne, tempStateTwo, tempStateThree, tempStateFour, goalState, timesThrough + 1)
            else:
                bestOfStateThree = NULL
                threeTimesThrough = MAX_STEPS
            if (not stateFour == NULL):
                tempStateOneList = stateFourCopy.moveLeft()
                tempStateTwoList = stateFourCopy.moveRight()
                tempStateThreeList = stateFourCopy.moveUp()
                tempStateFourList = stateFourCopy.moveDown()
                if (tempStateOneList == NULL):
                    tempStateOne = NULL
                if (tempStateTwoList == NULL):
                    tempStateTwo = NULL
                if (tempStateThreeList == NULL):
                    tempStateThree = NULL
                if (tempStateFourList == NULL):
                    tempStateFour = NULL
                bestOfStateFour, fourTimesThrough = self.goForwardToFindCurrentBestMove(stateFourCopy, tempStateOne, tempStateTwo, tempStateThree, tempStateFour, goalState, timesThrough + 1)
            else:
                bestOfStateFour = NULL
                fourTimesThrough = MAX_STEPS
            
            # Returning the best option
            return self.goForwardToFindCurrentBestMove(previousState, bestOfStateOne, bestOfStateTwo, bestOfStateThree, bestOfStateFour, goalState, timesThrough + 1)
        
        # Returning the best move
        if (oneMoveIsBest):
            return stateOneCopy, timesThrough
        elif (twoMoveIsBest):
            return stateTwoCopy, timesThrough
        elif (threeMoveIsBest):
            return stateThreeCopy, timesThrough
        return stateFourCopy, timesThrough
    
    def lookAheadOneStep(self, previousState, state1, state2, state3, state4, goalState, timesThrough = 0):
        if (state1 == NULL and state2 == NULL and state3 == NULL and state4 == NULL):
            print("all null")
            return NULL
        
        newGameState1 = GameState()
        newGameState2 = GameState()
        newGameState3 = GameState()
        newGameState4 = GameState()
        
        if (not state1 == NULL):
            newGameState1, dud = self.makeBestMove(previousState, state1, goalState, timesThrough)
        else:
            newGameState1 = NULL
        if (not state2 == NULL):
            newGameState2, dud = self.makeBestMove(previousState, state2, goalState, timesThrough)
        else:
            newGameState2 = NULL
        if (not state3 == NULL):
            newGameState3, dud = self.makeBestMove(previousState, state3, goalState, timesThrough)
        else:
            newGameState3 = NULL
        if (not state4 == NULL):
            newGameState4, dud = self.makeBestMove(previousState, state4, goalState, timesThrough)
        else:
            newGameState4 = NULL
        
        while(True):        
            step1 = MAX_STEPS
            step2 = MAX_STEPS
            step3 = MAX_STEPS
            step4 = MAX_STEPS
            
            if (not newGameState1 == NULL):
                step1 = newGameState1.calcManhattenSteps(goalState)
            if (not newGameState2 == NULL):
                step2 = newGameState2.calcManhattenSteps(goalState)
            if (not newGameState3 == NULL):
                step3 = newGameState3.calcManhattenSteps(goalState)
            if (not newGameState4 == NULL):
                step4 = newGameState4.calcManhattenSteps(goalState)
        
            if ((not newGameState1 == NULL) and (not previousState.compare(newGameState1)) and self.helper.compareFourLoose(step1, step2, step3, step4)):
                return state1
            elif ((not newGameState2 == NULL) and (not previousState.compare(newGameState2)) and self.helper.compareFourLoose(step2, step1, step3, step4)):
                return state2
            elif ((not newGameState3 == NULL) and (not previousState.compare(newGameState3)) and self.helper.compareFourLoose(step3, step2, step1, step4)):
                return state3
            elif ((not newGameState4 == NULL) and (not previousState.compare(newGameState4)) and self.helper.compareFourLoose(step4, step2, step3, step1)):
                return state4
            
            tempGameStateLeft = GameState()
            tempGameStateRight = GameState()
            tempGameStateUp = GameState()
            tempGameStateDown = GameState()
        
            if (not newGameState1 == NULL):
                if (not newGameState1.moveLeft() == NULL):
                    tempGameStateLeft.setList(newGameState1.moveLeft())
                else:
                    tempGameStateLeft = NULL
                if (not newGameState1.moveRight() == NULL):
                    tempGameStateRight.setList(newGameState1.moveRight())
                else:
                    tempGameStateRight = NULL
                if (not newGameState1.moveUp() == NULL):
                    tempGameStateUp.setList(newGameState1.moveUp())
                else:
                    tempGameStateUp = NULL
                if (not newGameState1.moveDown() == NULL):
                    tempGameStateDown.setList(newGameState1.moveDown())
                else:
                    tempGameStateDown = NULL
                newGameState1 = self.lookAheadOneStep(newGameState1, tempGameStateLeft, tempGameStateRight, tempGameStateUp, tempGameStateDown, goalState, timesThrough + 1)
            if (not newGameState2 == NULL):
                if (not newGameState2.moveLeft() == NULL):
                    tempGameStateLeft.setList(newGameState2.moveLeft())
                else:
                    tempGameStateLeft = NULL
                if (not newGameState2.moveRight() == NULL):
                    tempGameStateRight.setList(newGameState2.moveRight())
                else:
                    tempGameStateRight = NULL
                if (not newGameState2.moveUp() == NULL):
                    tempGameStateUp.setList(newGameState2.moveUp())
                else:
                    tempGameStateUp = NULL
                if (not newGameState2.moveDown() == NULL):
                    tempGameStateDown.setList(newGameState2.moveDown())
                else:
                    tempGameStateDown = NULL
                newGameState2 = self.lookAheadOneStep(newGameState2, tempGameStateLeft, tempGameStateRight, tempGameStateUp, tempGameStateDown, goalState, timesThrough + 1)
            if (not newGameState3 == NULL):
                if (not newGameState3.moveLeft() == NULL):
                    tempGameStateLeft.setList(newGameState3.moveLeft())
                else:
                    tempGameStateLeft = NULL
                if (not newGameState3.moveRight() == NULL):
                    tempGameStateRight.setList(newGameState3.moveRight())
                else:
                    tempGameStateRight = NULL
                if (not newGameState3.moveUp() == NULL):
                    tempGameStateUp.setList(newGameState3.moveUp())
                else:
                    tempGameStateUp = NULL
                if (not newGameState3.moveDown() == NULL):
                    tempGameStateDown.setList(newGameState3.moveDown())
                else:
                    tempGameStateDown = NULL
                newGameState3 = self.lookAheadOneStep(newGameState3, tempGameStateLeft, tempGameStateRight, tempGameStateUp, tempGameStateDown, goalState, timesThrough + 1)
            if (not newGameState4 == NULL):
                if (not newGameState1.moveLeft() == NULL):
                    tempGameStateLeft.setList(newGameState4.moveLeft())
                else:
                    tempGameStateLeft = NULL
                if (not newGameState4.moveRight() == NULL):
                    tempGameStateRight.setList(newGameState4.moveRight())
                else:
                    tempGameStateRight = NULL
                if (not newGameState4.moveUp() == NULL):
                    tempGameStateUp.setList(newGameState4.moveUp())
                else:
                    tempGameStateUp = NULL
                if (not newGameState4.moveDown() == NULL):
                    tempGameStateDown.setList(newGameState4.moveDown())
                else:
                    tempGameStateDown = NULL
                newGameState4 = self.lookAheadOneStep(newGameState4, tempGameStateLeft, tempGameStateRight, tempGameStateUp, tempGameStateDown, goalState, timesThrough + 1)
    
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
        print("previous state:")
        previousState.displayState()
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
        if ((not leftState == NULL) and (not previousState.compare(leftState)) and self.helper.compareFourLoose(leftSteps, rightSteps, upSteps, downSteps)):
            print("move left")
            clearBestMove = True
            leftMoveIsBest = True
        #elif ((not previousState.compare(rightState)) and self.helper.compareFourTight(rightSteps, leftSteps, upSteps, downSteps)):
        elif ((not rightState == NULL) and (not previousState.compare(rightState)) and self.helper.compareFourLoose(rightSteps, leftSteps, upSteps, downSteps)):
            print("move right")
            clearBestMove = True
            rightMoveIsBest = True
        #elif ((not previousState.compare(upState)) and self.helper.compareFourTight(upSteps, leftSteps, rightSteps, downSteps)):
        elif ((not upState == NULL) and (not previousState.compare(upState)) and self.helper.compareFourLoose(upSteps, leftSteps, rightSteps, downSteps)):
            print("move up")
            clearBestMove = True
            upMoveIsBest = True
        #elif ((not previousState.compare(downState)) and self.helper.compareFourTight(downSteps, leftSteps, upSteps, rightSteps)):
        elif ((not downState == NULL) and (not previousState.compare(downState)) and self.helper.compareFourLoose(downSteps, leftSteps, upSteps, rightSteps)):
            print("move down")
            clearBestMove = True
            downMoveIsBest = True
        
        # If there's not a clear best move and it's the first time
        if ((not clearBestMove) and timesThrough < 1):
            #raise Exception("Shouldn't be here")
            print("none")
            # Getting the best move (the function also returns an integer, but that's not necesary for
            # what comes after this)
            #bestMoveState, dud = self.goForwardToFindCurrentBestMove(currentState, rightState, leftState, upState, downState, goalState, timesThrough + 1)
            bestMoveState = self.lookAheadOneStep(currentState, rightState, leftState, upState, downState, goalState, timesThrough + 1)
            
            # Figuring out which move is the best move
            if ((not leftState == NULL) and bestMoveState.compare(leftState)):
                leftMoveIsBest = True
            elif ((not rightState == NULL) and bestMoveState.compare(rightState)):
                rightMoveIsBest = True
            elif ((not upState == NULL) and bestMoveState.compare(upState)):
                upMoveIsBest = True
            elif ((not downState == NULL) and bestMoveState.compare(downState)):
                downMoveIsBest = True
        elif (not clearBestMove):
            if ((not leftState == NULL) and self.helper.compareFourLoose(leftSteps, rightSteps, upSteps, downSteps)):
                leftMoveIsBest = True
            elif ((not rightState == NULL) and self.helper.compareFourLoose(rightSteps, leftSteps, upSteps, downSteps)):
                rightMoveIsBest = True
            elif ((not upState == NULL) and self.helper.compareFourLoose(upSteps, rightSteps, leftSteps, downSteps)):
                upMoveIsBest = True
            elif ((not downState == NULL) and self.helper.compareFourLoose(downSteps, rightSteps, upSteps, leftSteps)):
                downMoveIsBest = True
        
        # Returning the best move
        if (leftMoveIsBest):
            return leftState, timesThrough
        elif (rightMoveIsBest):
            return rightState, timesThrough
        elif (upMoveIsBest):
            return upState, timesThrough
        elif (downMoveIsBest):
            return downState, timesThrough
        return downState, timesThrough

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
        
        # Setting up the previous state for the first round
        previousState = GameState()
        if (not self.currentState.calcManhattenSteps(self.goalState) == 1):
            previousState.setList(self.goalState.getState())
        else:
            while (self.currentState.calcManhattenSteps(self.goalState) == 1):
                previousState.setList([0, 1])
        
        # This will loop while the current and goal state do not match
        while(not self.currentState.compare(self.goalState)):
            tempPreviousState.setList(self.currentState.getState())
            self.currentState, dud = self.mover.makeBestMove(previousState, self.currentState, self.goalState)
            previousState.setList(tempPreviousState.getState())
        
        print("Game complete!")

#def n_puzzle(): # Will use eventually, got tired of typing "n_puzzle()" every time to test
def s():
    # Creating and playing the game
    game = Game()
    game.playGame()
    
    
    
    
    
    
    
    