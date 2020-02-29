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

# Constants
FILENAME = "train.csv"

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
    
    # Separate the target variable
    target = df.clas
    inputs = df.drop('clas', axis='columns')
    
    # Getting rid of all of the non-number data
    df = replaceAllWithDummies(df)
    
    # TEST ONLY
    print("\ndataframe:")
    print(df.head())
    
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
            
            
            
            
            
            
            
            
            
            