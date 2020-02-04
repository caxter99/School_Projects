#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Feb  3 19:54:20 2020

@author: devin

Devin Hopkins
4190350

Project 1 for AI

State class:
"""

# Game State class
class GameState:
    
    # Constructor, can take nothing or a pregenerated list
    def __init__(self, initialList = []):
        
        # If the list was not pregenerated or pregenerated incorrectly,
        # make a new list
        if (initialList.len() != 9):
            # Make itself
            y = 0
        # Otherwise, the list is good to go
        else:
            # The list has laready been made
            i = 9