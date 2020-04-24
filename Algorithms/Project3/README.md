# README for Project 3
By: Devin Hopkins
4190350

# How to Operate My Project
In a terminal, navitage to the directory containing the project.
If the Makefile is not present, run:

- cmake .

After this, to build the project, run the command:

- make

After the program has been made, it is operated by using the following command:

- ./prj [image name] [number of vertical seam removals] [number of horizontal seam removals]

- [image name] is the name of the image you would like to perform seam removals on. Note that you must include the ".pbm"
- [number of vertical seam removals] is the number of vertical seams you would like to remove from the image
- [number of horizontal seam removals] is the number of horizontal seams you would like to remove from the image

This will run the program. The altered image will be saved in the [Processed_Images] directory located
in the same directory as the project. Its name will be:

[Original Image Name]_processed_[number of vertical seam removals]_[number of horizontal seam removals].pbm

# Extra Information
- Error in Input
Should you accidently enter invalid information (such as strings for the number of seam removals) the program
will not execute and will tell you how what the correct format looks like.

- Invalid Image Name
If you accidently enter an image name that isn't available, a list of all available default image names will
be displayed. This is assuming that there was no error in your input.

- Adding more Images
If you would like to add more images to process, they can either be added in the project directory or the [Images]
directory that is in the project directory.

- Removing Too Many Seams
Should you remove too many seams (i.e. the image is only 50 pixels wide and you remove 55 vertical seams) nothing
will be saved and the program will tell you what happened.

- Entering Negative Numbers for the Seam Removals
The program will treat those negative numbers as though they were 0s.