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

# Constants
FILENAME = "train.csv" # The filename for the data for part 1
TEST_TO_TRAIN_RATIO = 0.2 # The amount of data that will become the test
TARGET_VARIABLES = ['cancelled', 'late', 'ontime', 'verylate'] # A list of the
# values in the target column

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
    
    # Getting rid of all of the non-number data
    df = replaceAllWithDummies(df)
    
    # Replacing any missing numbers with 0
    df = fixMissingNumbers(df)
    
    # Making sure all of the column names don't have any spaes in them
    df = removeWhitespaceFromColumnNames(df)
    
    # TEST ONLY
    print("\ndataframe:")
    print(df.head())
    # END TEST
    
    # Separate the target variable and the inputs
    target = df[TARGET_VARIABLES]
    inputs = df
    for x in range(len(TARGET_VARIABLES)):
        inputs = inputs.drop(TARGET_VARIABLES[x], axis='columns')
    
    # Splitting the training and the test data
    x_train, x_test, y_train, y_test = train_test_split(inputs, target, test_size=TEST_TO_TRAIN_RATIO)
    
    # TEST ONLY
    print("\ndataframe:")
    print(df.head())
    print("\nlen(x_train):")
    print(len(x_train))
    print("\nlen(x_test):")
    print(len(x_test))
    print("\nlen(inputs):")
    print(len(inputs))
    # END TEST
    
# Does part 2 of the assignment
#def doPart2():
    # to do
    
# Takes a data frame and returns it without any string columns
def replaceAllWithDummies(df):
    # Creating all of the variables that are necessary
    x = 0
    limit = len(df.columns)
    
    # Looping through each column to see if it's a string data type
    while (not x == limit):
        # Checking to see if it's a string data type
        if (not type(df.columns[x]) == np.number):
            # Getting the dummy data (0's and 1's) from the column with strings
            temp = pd.get_dummies(df.iloc[:, x])
            
            # Adding that data onto the end of the data frame
            df = pd.concat([df, temp],axis='columns')
            
            # Removing the old column (the column with strings)
            df.drop(df.columns[x],axis='columns',inplace=True)
            
            # Making sure the limit drops since a column got removed
            limit = limit - 1
        # It's a numeric column
        else:
            # Increment x
            x = x + 1
    
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
            
            
            
            
            
            
            
            
            
            