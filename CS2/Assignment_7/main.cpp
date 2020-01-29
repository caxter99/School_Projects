/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 7
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.15.2018
Purpose: The purpose of this program is to use maps and iterators and get familiar with them.
*/

// Importing necessary libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>

// My movie struct
struct Movie
{
    // Includes a map with the reviews of the movie
    std::map<int, int> reviewScores;

    // Includes the title of the movie
    std::string title;

    // PRE: Expects an integer that's the score
    // POST: Adds the review score to the map and increments the key by one. Returns nothing
    void addScore(int score)
    {
        ++reviewScores[score];
    }

    // PRE: Expects nothing
    // POST: Returns the a float containing average review score of the movie
    float getAverage()
    {
        // Declaring necessary variables
        float totalScore = 0.0;
        int totalReviews = 0;

        // Goes through all of the elements of the map
        for (const auto &p : reviewScores)
        {
            // Total score is the review times the number of reviewers that gave it that score
            totalScore += (p.first * p.second);

            // Number of reviews is the total number of people who reviewed the movie
            totalReviews += p.second;
        }

        // Returns the average score by dividing the sum of the scores by the sum of the number of reviews
        return totalScore / totalReviews;
    }

    // PRE: Expects nothing
    // POST: Returns an integer containing the number of reviews for the movie
    int getNumOfReviews()
    {
        // Declaring a necessary variable
        int totalReviews = 0;

        // Goes through all the elements of the map
        for (const auto &p : reviewScores)
        {
            // Number of reviews is the total number of people who reviewed the movie
            totalReviews += p.second;
        }

        // Returns the total number of reviews
        return totalReviews;
    }
};

// Function prototype
bool movieExists(std::string, const std::vector<Movie>, int&);

int main()
{
    // Making my input file ready object and opening the document with it
    std::ifstream inFile;
    inFile.open("Movie_Reviews.txt");

    // If the file was opened successfully, then the code goes in here
    if (inFile)
    {
        // Declaring and initializing necessary variables
        std::vector<Movie> movieReviews;
        int reviewScore = 0, numberOfLines = 0, location = 0;
        std::string lineFromFile = "";

        // The first line in the file contains an integer that says how many lines
        // there are within the file. This gets that integer and moves the file reader
        // to the next line
        inFile >> numberOfLines;
        getline(inFile, lineFromFile);

        // This loop goes for as long as the file is
        for (int y = 0; y < numberOfLines; ++y)
        {
            // This gets the title of the movie
            getline(inFile, lineFromFile);

            // This gets the movie's review score
            inFile >> reviewScore;

            // If the movie already exists in the vector, then its score is simply added to the map
            if (movieExists(lineFromFile, movieReviews, location))
            {
                movieReviews.at(location).addScore(reviewScore);
            }

            // If the movie isn't in the vector, then a whole new Movie struct object is created and added
            // to the vector
            else
            {
                // Creating the new Movie struct object and initializing its elements
                Movie newMovie;
                newMovie.addScore(reviewScore);
                newMovie.title = lineFromFile;

                // Adding the new movie to the vector
                movieReviews.push_back(newMovie);
            }

            // This gets the \n character left behind from getting the integer
            getline(inFile, lineFromFile);
        }

        // This loop goes through each element in the movieReviews vector and prints its contents
        // in a neat, orderly fashion
        for (std::size_t x = 0; x < movieReviews.size(); ++x)
        {
            // If there are zero or more than one reviews for the movie, then this is displayed
            if (movieReviews.at(x).getNumOfReviews() != 1)
            {
                std::cout << movieReviews.at(x).title << ": " << movieReviews.at(x).getNumOfReviews()
                << " reviews, average of " << std::setprecision(2) << movieReviews.at(x).getAverage()
                << " / 5" << std::endl;
            }

            // If there's only one review, then this is displayed
            else
            {
                std::cout << movieReviews.at(x).title << ": " << movieReviews.at(x).getNumOfReviews()
                << " review, average of " << std::setprecision(2) << movieReviews.at(x).getAverage()
                << " / 5" << std::endl;
            }
        }
    }

    // If the file was not opened successfully, then the code goes in here
    else
    {
        // Displaying an error message
        std::cout << "Could not open the file." << std::endl;
    }

    return 0;
}

// PRE: Expects a string containing a movie title, a vector that contains movies, and an integer that will
// contain the location of where the movie is in the vector, if it exists at all
// POST: Returns false if the movie is not a part of the vector. In this case, spot stays as is. If the movie
// does exist, then this function returns true and the integer spot is set to the position the movie is in the
// vector
bool movieExists(std::string newTitle, const std::vector<Movie> movieVector, int &spot)
{
    // Going through each element in the vector, searching for the movie
    for (std::size_t z = 0; z < movieVector.size(); ++z)
    {
        // If the movie is equal to the current element of the vector, then the code goes in here
        if (newTitle.compare(movieVector.at(z).title) == 0)
        {
            // Sets spot to the location of the movie in the vector and returns true
            spot = z;
            return true;
        }
    }

    // If it doesn't find the movie, returns false and spot isn't changed
    return false;
}
