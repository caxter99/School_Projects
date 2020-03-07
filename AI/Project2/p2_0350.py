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

#
# The following function is the driver function
#
    
# Driver function
def py_nb():
    # Variables
    selection = "1"
    
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
                print(df)
        elif (selection == "2"):
            # to do
            i = 0
        elif (selection == "3"):
            # to do
            i = 0
        elif (selection == "4"):
            # to do
            i = 0
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
