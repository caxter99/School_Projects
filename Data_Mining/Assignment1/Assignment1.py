#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Feb 29 13:25:40 2020

@author: devin
"""

"""
NOTE:
    THIS PROGRAM IS SPECIFICALLY BUILT FOR THE train.csv FILE. IT IS NOT
    BUILT TO HANDLE ANYTHING BUT THAT.
"""

# This YouTube video helped me a TON with this assignment:
# https://www.youtube.com/watch?v=PPeaRc-r1OI

# All imports for the assignment
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB

# Constants
FILENAME = "train.csv" # The filename for the data for part 1
TEST_TO_TRAIN_RATIO = 0.01 # The amount of data that will become the test
COLUMN_NAMES = ["day", "season", "wind", "rain", "clas"]
TARGET_COLUMN = "clas" # This is the column that will be predicted
TEST_ONE = ["weekday", "summer", "high", "heavy"] # Test 1
TEST_TWO = ['sunday', 'summer', 'normal', 'slight'] # Test 2

#["weekday", "summer", "high", "heavy"]
#['sunday', 'summer', 'normal', 'slight']
# These are all of the test that will run

# Does both parts of the assignment
def doAll():
    # Do both parts of the assignment
    doPart1()
    #doPart2()
    # Eventually, this program will do both parts of the assignment
    
# Does part 1 of the assignment
def doPart1():
    # Get the data from the file
    df = pd.read_csv(FILENAME)
    
    # Since all of the variables are necessary, keep them all
    # do nothing here
    
    # Replacing any missing numbers with 0
    df = fixMissingNumbers(df)
    
    # Making sure all of the column names don't have any spaes in them
    df = removeWhitespaceFromColumnNames(df)
    
    # Replacing all of the strings with integers
    df = replaceAllWithDummies(df)
    test1 = convertListToDataFrame(replaceAllWithDummies(TEST_ONE.copy()))
    test2 = convertListToDataFrame(replaceAllWithDummies(TEST_TWO.copy()))
    
    # Separate the target variable and the inputs
    target = getTarget(df)
    inputs = getInputs(df)
    
    # Splitting the training and the test data
    x_train, x_test, y_train, y_test = train_test_split(inputs, target, test_size=TEST_TO_TRAIN_RATIO)
    
    # Creating and fitting the model
    model = GaussianNB()
    model.fit(x_train, y_train)
    
    # Performing our tests
    print("Test 1:", end ="")
    printList(TEST_ONE)
    print(convertIntToAnswer(model.predict(test1)))
    print("\nTest 2:", end="")
    printList(TEST_TWO)
    print(convertIntToAnswer(model.predict(test2)))
    
# Does part 2 of the assignment
#def doPart2():
    # to do

# Displays a list
def printList(theList):
    # Printing out the lst, along with the brackets
    print("[", end="")
    for x in range(len(theList)):
        if (not x == len(theList) - 1):
            print(theList[x],end=", ")
        else:
            print(theList[x],end="")
    print("]")
    
# Converts an integer into the answer
def convertIntToAnswer(x):
    if (TARGET_COLUMN == "clas"):
        if (x == 1):
            return "on time"
        elif (x == 2):
            return "late"
        elif (x == 3):
            return "cancelled"
        else:
            return "very late"
    else:
        return "not done"

# Converts a list to a data frame
def convertListToDataFrame(testList):
    # Figuring out what the columns name's are
    newColumns = []
    if (TARGET_COLUMN == "clas"):
        newColumns = ["day_int", "season_int", "wind_int", "rain_int"]
    elif(TARGET_COLUMN == "day"):
        newColumns = ["season_int", "wind_int", "rain_int", "clas_int"]
    elif(TARGET_COLUMN == "season"):
        newColumns = ["day_int", "wind_int", "rain_int", "clas_int"]
    elif(TARGET_COLUMN == "wind"):
        newColumns = ["day_int", "season_int", "rain_int", "clas_int"]
    else:
        newColumns = ["day_int", "season_int", "wind_int", "clas_int"]
    
    # Putting it into a data frame
    tempDF = pd.DataFrame(np.array(testList).reshape(1, len(testList)), columns=list("abcd"))
    
    # Converting the column names to their proper names
    tempDF.columns = newColumns
    
    # REturning the data frame
    return tempDF

# Returns the target column given the dataframe
def getTarget(df):
    if (TARGET_COLUMN == "clas"):
        return df.clas_int
    elif(TARGET_COLUMN == "day"):
        return df.day_int
    elif(TARGET_COLUMN == "season"):
        return df.season_int
    elif(TARGET_COLUMN == "wind"):
        return df.wind_int
    else:
        return df.rain_int
    
# Returns the inputs given the dataframe
def getInputs(df):
    if (TARGET_COLUMN == "clas"):
        return df.drop('clas_int', axis='columns')
    elif(TARGET_COLUMN == "day"):
        return df.drop('day_int', axis='columns')
    elif(TARGET_COLUMN == "season"):
        return df.drop('season_int', axis='columns')
    elif(TARGET_COLUMN == "wind"):
        return df.drop('wind_int', axis='columns')
    else:
        return df.drop('rain_int', axis='columns')

# Changes all values to integers
def changeValuesToIntegers(x):
    # Remove the whitespace, just in case
    x = removeWhitespace(x)
    
    # "day" column
    if (x == "weekday"):
        return 1
    elif(x == "saturday"):
        return 2
    elif (x == "holiday"):
        return 3
    elif (x == "sunday"):
        return 4
    
    # "season" column
    if (x == "spring"):
        return 1
    elif(x == "winter"):
        return 2
    elif (x == "summer"):
        return 3
    elif (x == "autumn"):
        return 4
    
    # "wind" column
    if (x == "none"):
        return 1
    elif(x == "high"):
        return 2
    elif (x == "normal"):
        return 3
    
    # "rain" column
    if (x == "none"):
        return 1
    elif(x == "slight"):
        return 2
    elif (x == "heavy"):
        return 3
    
    # "clas" column
    if (x == "ontime"):
        return 1
    elif(x == "late"):
        return 2
    elif (x == "cancelled"):
        return 3
    elif (x == "verylate"):
        return 4
    
    # Unknown value
    return 0

# Takes a data frame (or a specific test case) and returns it with all integers
def replaceAllWithDummies(df):
    # Replacing all of the values of the given dataset with integers
    limit = 0
    try:
        # Getting the number of columns
        limit = len(df.columns)
        
        # Looping through and converting them to numeric values
        for x in range(limit):
            newString = "" + df.columns[x] + "_int"
            #temp = pd.get_dummies(df.iloc[:, x])
            df[newString] = df[COLUMN_NAMES[x]].apply(changeValuesToIntegers)
            
        # Looping through and getting rid of the old values
        for x in range(limit):
            df = df.drop(COLUMN_NAMES[x], axis='columns')
    except:
        # Getting the number of test input variables
        limit = len(df)
        
        # Looping through each test case and converting it to integers
        for x in range(limit):
            df[x] = changeValuesToIntegers(df[x])
            
    
    # Returning the data frame
    return df

# Replaces all the missing numeric values with 0
# NOTE: Assumes an all numeric data frame
def fixMissingNumbers(df):
    # If there's no missing numbers
    if (not areThereMissingNumbers(df)):
        return df
    
    # If the code makes it to here, there are some values that must be changed
    # CURRENTLY DOES NOT CORRECT ANY VALUES
    return df

# Returns true if there are any missing values in an all numeric data set
# NOTE: Assumes an all numeric data set
def areThereMissingNumbers(df):
    # Getting a string of all columns that have non-numbers in them
    strO = str(df.columns[df.isna().any()])
    
    # Checking to see if there are any
    first = strO.find("[")
    second = strO.find("]")
    if (first + 1 == second): # If this is true, there are none
        return False
    else: # Otherwise, there are some missing numbers
        return True
    
# Removes all of the whitespace from the column names of the given data frame
def removeWhitespaceFromColumnNames(df):
    # Variables needed for the funciton
    columnNames = []
    
    # Creating a list of all of the column names
    for x in range(len(df.columns)):
        columnNames.append(df.columns[x])
    
    # Removing any whitespace they may have
    for x in range(len(df.columns)):
        columnNames[x] = removeWhitespace(columnNames[x])
        
    # Setting the data frame's columns to be the ones without whitespace
    df.columns = columnNames
    
    # Returns the data frame
    return df

# Removes all of the whitespace from the given string
def removeWhitespace(string):
    return string.replace(" ", "")
            
            
            
            
            
            
            
            
            
            