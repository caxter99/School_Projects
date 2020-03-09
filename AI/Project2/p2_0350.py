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
import pickle

# Constants
NULL = "null" # Null value
TURN_OFF_ALL_WARNINGS = True # If true, all possible code warnings are turned
    # off
MODEL_FILENAME_PREFIX = "Models/" # The prefix for where all models are saved
MODEL_FILENAME_POSTFIX = ".bin" # The postfix for where all models are saved
EXTRA_DATA_MODEL_FILENAME_PREFIX = "Extra_Model_Info/" # The prefix for all of
    # the extra information that must be stored with the models
EXTRA_DATA_MODEL_FILENAME_POSTFIX = ".txt" # The postfix for all of the extra
    # information that must be stored with the models
TEST_DATAFRAME_FILENAME_PREFIX = EXTRA_DATA_MODEL_FILENAME_PREFIX # The
    # prefix for all of the test cases for a model
TEST_DATAFRAME_FILENAME_POSTFIX = ".csv" # The postfix for all of the test
    # cases that must be stored with the models

# Global, non-constant variables
currentModel = NULL
currentModelFilename = NULL
currentTargetVariable = NULL
currentTargetVariableOptions = NULL
currentInputVariables = NULL
currentInputVariableOptions = NULL
X_TEST = NULL
Y_TEST = NULL

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

# Returns a list with all of the possible options for the column
def getColumnsPossibilities(col):
    # Variables
    possibilities = []
    # Checks to make sure there's at least one value in the column
    if (len(col) == 0):
        return possibilities
    
    # Checks to see if it's numeric
    if (np.issubdtype(col.dtype, np.number)):
        return possibilities
    
    # Return all of the possibilities
    return col.unique()

# Returns a list of all columns in the model
def getColumnsNames(df):
    # Variables
    colNames = []
    
    # If it's not a valid dataframe, return with an empty list
    if (not isValidDataFrame(df)):
        return colNames
    
    # Get all of the names from the columns
    for col in df.columns:
        colNames.append(str(col))
    
    # Return a list of all of the column names
    return colNames

# Returns a matrix of all possible options
def getOptionsForColumns(df):
    # Variables
    options = [[]]
    
    # If it's not a valid dataframe, return with an empty matrix
    if (not isValidDataFrame(df)):
        return options
    
    # Get all of options for each column
    x = 0
    for col in df.columns:
        if (x == 0):
            options[0] = getColumnsPossibilities(df[col])
        else:
            options.append(getColumnsPossibilities(df[col]))
        x = x + 1
    
    # Return a matrix of all of the option names
    return options

#
# The following functions are for part 1
#

# Gets the name of a data file and returns the data after reading it in
def getData():
    # Variables
    global currentModelFilename
    df = NULL
    gotValidData = False
    
    # Getting the data from the user
    while(not gotValidData):
        # Prompting the user
        filename = input("What is the name of the csv file? Enter the ENTIRE filename (excluding the .csv extension) or \"Q\" to quit.\n")
        
        # Filename not equal to "Q"
        if (not (filename == "Q")):
            # In case the user entered the filename wrong
            try:
                # Reading in the file
                df = pd.read_csv(filename + ".csv")
                
                # If it gets here, they entered in correct data
                gotValidData = True
                
                # Keeping track of the filename
                currentModelFilename = filename
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

# Returns the name of the target column and the new data frame without the
# target column
def getTarget(df):
    # Variables
    target = NULL
    gotValidData = False
    global currentTargetVariable
    global currentInputVariables
    global currentInputVariableOptions
    global currentTargetVariableOptions
    
    while (not gotValidData):
        # Displaying the options
        print("Column options: (column names DO NOT include the \",\")")
        for col in df.columns:
            print(str(col), end=", ")
        
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
            
    # Creating a copy of the dataframe
    dfCopy = copyDataFrame(df)
    
    # Setting the target to the globa target variable
    currentTargetVariable = target
    
    # Dropping every column but the target column
    x = 0
    while(x < len(dfCopy.columns)):
        if (not (dfCopy.columns[x] == target)):
            dfCopy = dfCopy.drop(dfCopy.columns[x], axis='columns')
        else:
            x = x + 1
    target = dfCopy
    
    # Dropping the target column from the dataframe
    df = df.drop(target, axis='columns')
    
    # Getting all of the remaining columns (inputs)
    currentInputVariables = getColumnsNames(df)
    
    # Getting all of the possible options for the columns (inputs)
    currentInputVariableOptions = getOptionsForColumns(df)
    
    # Getting the target's options
    currentTargetVariableOptions = getOptionsForColumns(target)
    
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

    # Making sure the column is of type 'int'
    col = col.astype('int')
    
    # Returning the column
    return col

# Converts the dataframe to integers
def convertDataFrameToNumbers(df):    
    # Getting all of the column names into a list
    columnNames = []
    for col in df.columns:
        columnNames.append(str(col))
    
    # Looping through each column to convert it to a number
    limit = len(df.columns)
    for x in range(limit):
        df[columnNames[x]] = convertColumnToNumbers(df[columnNames[x]])
    
    # Returning the dataframe
    return df

# Returns a 1D array that was a single column dataframe
def convertOneColumnDataFrameToSeries(df):
    # Making sure it's a valid, single column dataframe
    if (not (isValidDataFrame(df)) and len(df.columns) > 1 ):
        return df
    
    # Converting the first column to a series and returning it
    return df[df.columns[0]]

# Generates a naive bayesian classifier
def generateNaiveBayesianClassifier(df):
    # Variables
    global X_TEST
    global Y_TEST
    
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
            # Do nothing
            uselessVariable = 0
        
        # They entered an out of range number
        if (not gotValidData):
            print("That was an invalid answer. Please enter a number between 0 and 1.")
    
    # Making sure testToTrainRatio is a float
    testToTrainRatio = float(testToTrainRatio)
    
    # Making it easier to understand
    inputsForTest = convertDataFrameToNumbers(copyDataFrame(df))
    targetForTest = convertOneColumnDataFrameToSeries(convertDataFrameToNumbers(copyDataFrame(target)))
    
    # Splitting the training and the test data
    x_train2, x_test2, y_train2, y_test2 = train_test_split(inputsForTest, targetForTest, test_size=testToTrainRatio)
    
    # Creating and fitting the model
    model = GaussianNB()
    model.fit(x_train2, y_train2)
    
    # Setting the global testing variables
    X_TEST = x_test2
    Y_TEST = y_test2
    
    # Telling the user the model was successfully created
    print("\nThe model was succesfully created!")
    
    # Return the model
    return model

#
# The following functions are for part 2
#

# Saves a model
def saveModel(model):
    # Variables
    global currentModelFilename
    global currentTargetVariable
    global currentInputVariables
    global currentInputVariableOptions
    global currentTargetVariableOptions
    global X_TEST
    global Y_TEST
    
    # Checking to see if the model is null
    if (model == NULL):
        # If it is, let the user know and return
        print("\nThere is no model currently loaded, and therefore nothing can be saved.")
        return
    
    # If it's a valid model, save it
    pickle.dump(model, open(MODEL_FILENAME_PREFIX + currentModelFilename + MODEL_FILENAME_POSTFIX, 'wb'))
    
    # Also, save all of the additional information necessary
    file = open(EXTRA_DATA_MODEL_FILENAME_PREFIX + currentModelFilename + EXTRA_DATA_MODEL_FILENAME_POSTFIX, "w")
    
    # Writing the current target variables
    file.write(currentTargetVariable)
    file.write("\n")
    
    # Writing the options for the target variable
    for listt in currentTargetVariableOptions:
        for string in listt:
            file.write(string + ",")
    file.write("\n")
    
    # Writing the current column names (inputs)
    for x in range(len(currentInputVariables)):
        file.write(currentInputVariables[x] + ",")
    file.write("\n")
    
    # Writing the options for each column (inputs)
    for listt in currentInputVariableOptions:
        for string in listt:
            file.write(string + ",")
        file.write("-")
    file.write("\n")
    
    # Closing the file
    file.close()
    
    # Saving the test cases
    x_test_string = TEST_DATAFRAME_FILENAME_PREFIX + "x" + currentModelFilename + TEST_DATAFRAME_FILENAME_POSTFIX
    y_test_string = TEST_DATAFRAME_FILENAME_PREFIX + "y" + currentModelFilename + TEST_DATAFRAME_FILENAME_POSTFIX
    X_TEST.to_csv(x_test_string, header = True)
    Y_TEST.to_csv(y_test_string, header = True)
    
    # Let the user know it was saved
    print("\nThe model was successfully saved!")

# Tests and displays the model's accuracy
def testModelAccuracy(model):
    i = 0

#
# The following functions are for part 3
#

# Loads a model
def loadModel():
    # Variables
    global currentModel
    global currentModelFilename
    global currentTargetVariable
    global currentTargetVariableOptions
    global currentInputVariables
    global currentInputVariableOptions
    global X_TEST
    global Y_TEST
    loadedModel = NULL
    target = ""
    targetOptions = []
    inputColumnNames = []
    inputColumnOptions = []
    x_test2 = NULL
    y_test2 = NULL
    
    # Getting what model the user wants to load
    modelName = input("What model would you like to load? Enter its name, not including the \".csv\".\n")
    
    # Attempting to open the model
    try:
        # Loading the model
        loadedModel = pickle.load(open(MODEL_FILENAME_PREFIX + modelName + MODEL_FILENAME_POSTFIX, 'rb'))
        
        # Updating the tests
        x_test_string = TEST_DATAFRAME_FILENAME_PREFIX + "x" + currentModelFilename + TEST_DATAFRAME_FILENAME_POSTFIX
        y_test_string = TEST_DATAFRAME_FILENAME_PREFIX + "y" + currentModelFilename + TEST_DATAFRAME_FILENAME_POSTFIX
        x_test2 = pd.read_csv(x_test_string)
        y_test2 = pd.read_csv(y_test_string)
        
        # Opening the file with the extra data
        file = open(EXTRA_DATA_MODEL_FILENAME_PREFIX + currentModelFilename + EXTRA_DATA_MODEL_FILENAME_POSTFIX, "r")
        
        # Reading all of the lines
        lines = file.readlines()
        
        # Looping through and grabbing all of the data from the text
        lineNum = 0
        for line in lines:
            # Getting rid of the \n at the end (and any unwanted spaces)
            line = line.strip()
            
            # Seeing what line number it is and therefore what should be done
            #
            # Grabbing the target variable name
            if (lineNum == 0):
                target = line
            # Grabbing the target variable possibilities
            elif (lineNum == 1):
                # Looping through all of the possiblities
                while(not (line.find(",") == -1)):
                    # Getting the name of an option
                    targetOptions.append(line[:line.find(",")])
                    
                    # Removing that option
                    line = line[line.find(",") + 1:]
            # Grabbing the input column names
            elif (lineNum == 2):
                # Looping through all of the column names
                while(not (line.find(",") == -1)):
                    # Getting the name of an option
                    inputColumnNames.append(line[:line.find(",")])
                    
                    # Removing that option
                    line = line[line.find(",") + 1:]
            # Grabbing the options for the input columns
            elif (lineNum == 3): #inputColumnOptions
                # Variable to keep track of which column number we're on
                colNum = 0
                # Looping through each column individually
                while(not (line.find("-") == -1)):
                    # Cutting the line down so it only includes one column
                    columnLine = line[:line.find("-")]
                    
                    # Appending another list
                    inputColumnOptions.append([])
                    
                    # Looping through each of the possibilities
                    while(not (columnLine.find(",") == -1)):
                        # Getting the name of an option
                        inputColumnOptions[colNum].append(columnLine[:columnLine.find(",")])
                        
                        # Removing that option
                        columnLine = columnLine[columnLine.find(",") + 1:]
                    
                    # Removing that column option
                    line = line[line.find("-") + 1:]
                    
                    # Incrementing colNum
                    colNum = colNum + 1
            # Uh oh, it shouldn't be here
            else:
                # error, this shouldn't ever go here
                i = 0
            
            # Increment lineNum
            lineNum = lineNum + 1
        
        # Closing the file
        file.close()
        
        # If everything was successful, load all of the temporary variables
        # into the global ones 
        #
        # Model
        currentModel = loadedModel
        # Filename
        currentModelFilename = modelName
        # Target variable
        currentTargetVariable = pd.DataFrame(targetOptions, columns = [target])
        # Target variable options
        currentTargetVariableOptions = targetOptions
        # Input variables
        currentInputVariables = pd.DataFrame(inputColumnOptions, columns = inputColumnNames)
        # Input variable options
        currentInputVariableOptions = inputColumnOptions
        # X and Y tests
        X_TEST = x_test2
        Y_TEST = y_test2
        
        # Letting the user know the model was successfully loaded
        print("\nThe model was successfully loaded!")
        
        # Returning the new model
        return loadedModel
    except:
        # Letting the user know their model wasn't valid
        print("\nThe filename you entered was not a valid model name.")
    
    # If it gets to here, no model was loaded, so return NULL
    return NULL

#
# The following function is the driver function
#

# Driver function
def py_nb():
    # Variables
    global currentModel
    selection = "1" # The user's selection
    
    # If the warnings should be turned off
    if (TURN_OFF_ALL_WARNINGS):
        # Turning off the warnings
        pd.options.mode.chained_assignment = None
    
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
            # Save the model
            saveModel(currentModel)
        elif (selection == "3"):
            # Load a model
            currentModel = loadModel()
            
            # If there's a model loaded, test its accuracy
            if (not (currentModel == NULL)):
                testModelAccuracy(currentModel)
        elif (selection == "4"):
            # to do
            i = 0
    
    # Telling the user they're quitting
    print("\nExiting...")