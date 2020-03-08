#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar  6 13:30:12 2020

@author: devin hopkins
4190350
"""

# Imports
import pandas as pd
import numpy as np
from math import sqrt
#from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB

# Constants
NULL = "null" # Null value

#
# The following functions are for the general use
#

# Returns true if the input is a valid selection for the menu
def isValidMenuInput(selection):
    # Looping through all of the valid inputs
    for x in range(1, 6):
        # If the user's input matches a valid input, return true
        if (str(x) == selection):
            return True
    
    # If it doesn't match anything, return false
    return False

# Returns the menu string
def getMenuString():
    # Creating the string and returning it
    menuString = "1. Learn a Naive Bayes classifier from categorical data\n"
    menuString = menuString + "2. Save a model\n"
    menuString = menuString + "3. Load a model and test its accuracy\n"
    menuString = menuString + "4. Apply a Naive Bayesian classifier to cases"
    menuString = menuString + " interactively\n"
    menuString = menuString + "5. Quit\n"
    menuString = menuString + "Enter the number you would like to do: "
    return menuString

# This displays the menu and returns the input as an integer
def displayMenu():
    # Displaying the menu and getting what the user wants to do
    selection = input(getMenuString())
    
    # Making sure it's a valid input
    while(not isValidMenuInput(selection)):
        # Displaying the menu and getting what the user wants to do
        print("\nThat was not a valid selection. Please select a valid option.")
        selection = input(getMenuString())
    
    # Returning the selection
    return selection

# This returns a copy of the dataframe sent in
def copyDataFrame(df):
    return df.copy()


#
# The following functions are for part 1
#

# Gets the name of a data file and returns the data after reading it in
def getData():
    # Variables
    df = NULL
    gotValidData = False
    
    # Getting the data from the user
    while(not gotValidData):
        # Prompting the user
        filename = input("What is the name of the csv file? Enter the ENTIRE filename or \"Q\" to quit.\n")
        
        # Filename not equal to "Q"
        if (not (filename == "Q")):
            # In case the user entered the filename wrong
            try:
                # Reading in the file
                df = pd.read_csv(filename)
                
                # If it gets here, they entered in correct data
                gotValidData = True
            except:
                # They entered invalid data
                print("\nThat was an invalid filename. Try again or type \"Q\" to quit.")
        # Filename equal to "Q"
        else:
            gotValidData = True
    
    # Keeping the formatting nice
    print()
    
    # Returning the data frame or null
    return df

# Returns true if the dataframe is valid, false otherwise
def isValidDataFrame(df):
    # If there's any errors
    try:
        # Seeing if it's a valid data frame
        if (len(df.columns) > 0):
            # If it makes it here, it's a valid data frame
            return True
    except:
        # It;s not a data frame
        return False
    
    # It's a data frame, but has 0 attributes, so it isn't valid
    return False

# Returns the name of the target column and the new data frame without the
# target column
def getTarget(df):
    # Variables
    target = NULL
    gotValidData = False
    
    while (not gotValidData):
        # Displaying the options
        print("Column options: (column names DO NOT include the \",\")")
        for col in df.columns:
            print(str(col), end=", ")
        print()
        
        # Getting which one the user wants
        target = input("Which column would you like to be the target? Enter it EXACTLY as it appears.\n")
        
        # Checking to see if the user input is valid
        for col in df.columns:
            # The user's input matches one of the column names
            if (str(col) == target):
                gotValidData = True
        
        # The user's input did not match any of the column names
        if (not gotValidData):
            print("\nYou did not enter a valid column name. Please enter it EXACTLY as it appears.")
    
    # Getting the correct target column
    for col in df.columns:
        if (str(col) == target):
            target = col
            break
    
    # Dropping the target column from the dataframe
    df = df.drop(target, axis='columns')
    
    # Returning the target
    return target, df

# Converts a column of non-integer values into a column of integer values
def convertColumnToNumbers(col):
    # Variables
    keywordDict = {}
    uniqueEntries = col.unique()
    numberOfUniqueEntries = len(uniqueEntries)
    
    # Creating integers based on how many entries there are, each integer
    # corresponding to one integer
    for x in range(numberOfUniqueEntries):
        keywordDict[uniqueEntries[x]] = x
    
    # Converting the column from the original values into integers
    for x in range(len(col)):
        col[x] = keywordDict[col[x]]

    # Returning the column
    return col

# Converts the dataframe to integers
def convertDataFrameToNumbers(df):
    # Creating a copy so the original isn't changed
    dfCopy = copyDataFrame(df)
    
    # Getting all of the column names into a list
    columnNames = []
    for col in df.columns:
        columnNames.append(str(col))
    
    # Looping through each column to convert it to a number
    limit = len(dfCopy.columns)
    for x in range(limit):
        dfCopy[columnNames[x]] = convertColumnToNumbers(dfCopy[columnNames[x]])
    
    # Returning the dataframe
    return dfCopy

# Generates a naive bayesian classifier
def generateNaiveBayesianClassifier(df):
    # Getting the target column and the modified dataframe
    target, df = getTarget(df)
    
    # Getting the user's input for the test to train ration
    gotValidData = False
    testToTrainRatio = 0
    while (not gotValidData):
        # Getting the user's input
        inputStr = "What would you like the test to train ratio to be? "
        inputStr = inputStr + "This number is representative of what percent "
        inputStr = inputStr + "of data will be taken out of the training data "
        inputStr = inputStr + "and put into the testing data. It must be a number "
        inputStr = inputStr + "between 0 and 1, non-inclusive.\n"
        testToTrainRatio = input(inputStr)
        
        # Making sure the user entered properly
        try:
            # If this is true, they entered an in range number
            if (float(testToTrainRatio) > 0 and float(testToTrainRatio) < 1):
                gotValidData = True
        except:
            i = 0
        
        # They entered an out of range number
        if (not gotValidData):
            print("That was an invalid answer. Please enter a number between 0 and 1.")
    
    # Making sure testToTrainRatio is a float
    testToTrainRatio = float(testToTrainRatio)
    
    # Splitting the training and the test data
    #x_train, x_test, y_train, y_test = train_test_split(convertDataFrameToNumbers(df), target, test_size=testToTrainRatio)
    
    print(df)
    print("-----")
    print(convertDataFrameToNumbers(df))
    
    # Return the model
    return 0

#
# The following function is the driver function
#
    
# Driver function
def py_nb():
    # Variables
    selection = "1" # The user's selection
    currentModel = NULL # The current NB Classification model that's loaded
    
    # Keep going until the user wants to quit
    while(not selection == "5"):
        # Getting what the user wants to do
        selection = displayMenu()
        
        # Perform the action the user wants
        if (selection == "1"):
            # Get the data from the user
            df = getData()
            
            # If the user entered valid data
            if (isValidDataFrame(df)):
                # Generating an NB Classification model
                currentModel = generateNaiveBayesianClassifier(df)
        elif (selection == "2"):
            # to do
            i = 0
        elif (selection == "3"):
            # to do
            i = 0
        elif (selection == "4"):
            # to do
            i = 0
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
