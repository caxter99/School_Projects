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
from math import sqrt
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB

# Part 1 Constants
TRAIN_FILENAME = "train.csv" # The filename for the data for part 1
TEST_TO_TRAIN_RATIO = 0.01 # The amount of data that will become the test
COLUMN_NAMES = ["day", "season", "wind", "rain", "clas"] # The original column
# names for the first data set
COLUMN_NAMES2 = ["attribute1", "attribute2", "clas2"] # The original column
# names for the second data set
TARGET_COLUMN = "clas" # This is the column that will be predicted
TEST_ONE = ["weekday", "summer", "high", "heavy"] # Test 1 for part 1
TEST_TWO = ['sunday', 'summer', 'normal', 'slight'] # Test 2 for part 1
TEST_THREE = [9.1, 11.0] # Test 3 for part 2
FIGURE_FILENAME = "figure3_5.csv" # The filename for the data for part 2
NUMBER_OF_NEAREST_NEIGHBORS = 5 # The number of nearest neighbors to find in
# part 2

# Does both parts of the assignment
def doAll():
    # Doing part 1
    print("Part 1:")
    doPart1()
    
    # Doing part 2
    print("\n\nPart 2:")
    doPart2()





# PART ONE
#
# Does part 1 of the assignment
def doPart1():
    # Get the data from the file
    df = pd.read_csv(TRAIN_FILENAME)
    
    # Get rid of unnecessary values
    # do nothing here because all of the columns are necessary
    
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
    
    # Performing the tests
    print("Prediction 1:", end ="")
    printList(TEST_ONE)
    print(convertIntToAnswer(model.predict(test1)))
    print("^should be \"on time\"")
    print("Prediction 2:", end="")
    printList(TEST_TWO)
    print(convertIntToAnswer(model.predict(test2)))

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
    
    # Returning the data frame
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
    
    # "clas2" column
    if (x == "M"):
        return 1
    elif(x == "P"):
        return 2
    
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





# PART TWO
#
# Does part 2 of the assignment
def doPart2():
    # Get the data from the file
    df = pd.read_csv(FIGURE_FILENAME)
    
    # Removing the whitespace form the column names
    df = removeWhitespaceFromColumnNames(df)
    
    # Replacing the string values with integers
    df = replaceAllWithDummies2(df)
    test3 = convertListToDataFrame2(replaceAllWithDummies2(TEST_THREE.copy()))
    
    # Getting the target and inputs
    inputs = df.drop('clas2_int', axis='columns')
    target = df.clas2_int
    
    # Getting the k closest points
    closestPoints, closestDistance = getNearestNeighbors(df)
    
    # Split into training and test set 
    x_train, x_test, y_train, y_test = train_test_split(inputs, target, test_size=TEST_TO_TRAIN_RATIO)
    
    # Fit the model
    knn = KNeighborsClassifier(n_neighbors=NUMBER_OF_NEAREST_NEIGHBORS)
    knn.fit(x_train, y_train)
    
    # The results
    print("The point (", TEST_THREE[0], ", ", TEST_THREE[1], ") is most likely a:", sep="", end=" ")
    print(convertIntToAnswer2(knn.predict(test3)))
    print("The", NUMBER_OF_NEAREST_NEIGHBORS, "closest neighbors (in order):")
    for x in range(len(closestPoints)):
        print("Point #", (x + 1), ": (", closestPoints[x][0], ", ", closestPoints[x][1], ")", sep="")
        print("Distance: ", closestDistance[x], sep="")
        print()

# Returns the K closest neighbors in a 2D array
def getNearestNeighbors(df):
    # The 2D array to store the nearest points
    closestPoints = []
    closestDistance = []
    for x in range(NUMBER_OF_NEAREST_NEIGHBORS):
        closestPoints.append([0, 0])
        closestDistance.append(-1)
    
    # The 2D array for storing all of the points
    allPoints = []
    allDistance = []
    for x in range(len(df)):
        allPoints.append([0, 0])
        allDistance.append(-1)
    
    # Getting the test points
    test_x = TEST_THREE[0]
    test_y = TEST_THREE[1]
    
    # Lopping through each point in df
    for p in range(len(df)):
        # Getting the x and the y values
        x = df.attribute1[p]
        y = df.attribute2[p]
        
        # Calculating the distance
        dist = sqrt((test_x - x)**2 + (test_y - y)**2)
        
        # Adding the point and the distance to the array
        allPoints[p] = [x, y]
        allDistance[p] = dist
    
    # Sorting the distance
    quickSort(allPoints, allDistance, 0, len(allPoints) - 1)
    
    # Getting the closest times
    for q in range(NUMBER_OF_NEAREST_NEIGHBORS):
        closestPoints[q] = allPoints[q]
        closestDistance[q] = allDistance[q]
    
    # Returning the closest points and distance
    return closestPoints, closestDistance

# Takes a data frame (or a specific test case) and returns it with all integers
def replaceAllWithDummies2(df):
    # Replacing all of the values of the given dataset with integers
    limit = 0
    try:
        # Getting the number of columns
        limit = len(df.columns)
        
        # Looping through and converting them to numeric values
        for x in range(limit):
            newString = "" + df.columns[x] + "_int"
            #temp = pd.get_dummies(df.iloc[:, x])
            if (x == limit - 1):
                df[newString] = df[COLUMN_NAMES2[x]].apply(changeValuesToIntegers)
            
        # Looping through and getting rid of the old values
        for x in range(limit):
            if (x == limit - 1):
                df = df.drop(COLUMN_NAMES2[x], axis='columns')
    except:
        # Do nothing here
        """# Getting the number of test input variables
        limit = len(df)
        
        # Looping through each test case and converting it to integers
        for x in range(limit):
            if (x == limit - 1):
                df[x] = changeValuesToIntegers(df[x])"""
            
    
    # Returning the data frame
    return df

# Converts an integer into the answer
def convertIntToAnswer2(x):
    if (x == 1):
        return "M (-)"
    elif (x == 2):
        return "P (+)"
    return "unknown prediction"

# Converts a list to a data frame
def convertListToDataFrame2(testList):
    # Figuring out what the columns name's are
    newColumns = ["attribute1", "attribute2"]
    
    # Putting it into a data frame
    tempDF = pd.DataFrame(np.array(testList).reshape(1, len(testList)), columns=list("ab"))
    
    # Converting the column names to their proper names
    tempDF.columns = newColumns
    
    # Returning the data frame
    return tempDF

def partition(arr2, arr, low, high):
    i = (low - 1)
    pivot = arr[high]

    for j in range(low, high):
        if (arr[j] <= pivot):
            i = i + 1
            arr[i], arr[j] = arr[j], arr[i]
            arr2[i], arr2[j] = arr2[j], arr2[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    arr2[i + 1], arr2[high] = arr2[high], arr2[i + 1]
    return (i + 1)

def quickSort(arr2, arr, low, high):
    if (low < high):
        pi = partition(arr2, arr, low, high)

        quickSort(arr2, arr, low, pi - 1)
        quickSort(arr2, arr, pi + 1, high)
            
            
            
            
            
            
            
            
            
            