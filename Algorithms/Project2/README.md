# README for Project 2
By: Devin Hopkins

# For Part 1
In a terminal, navigate to the directory containing the project.
In that directory, type:

- make

This will make the necessary files. To run the program, type:

- ./your [Algorithm] <Filename>

- <Algorithm> is G for Graham Scan, J for Jarvis March, or Q for Quickhull.
- <Filename> is the filename that contains the points you would like to test.

This will then start the program. The method chosen, as well as the filename
(without the extension) are displayed as the program works to solve it.
Depending on how many points are in the file and the algorithm chosen, it may
take a while. When it is done, the points on the convex hull will be displayed,
as well as how many milliseconds and seconds the process took.

Note: The time for milliseconds and seconds may not be the same. This is because 
the seconds time rounds to the nearest second (to a certain degree). So, not
every 1,000 millisecond is going to equal 1 second.

After this, to view the points on the Java program provided for this project,
type:

- cd GUI4ConvexHall

This will get you into the directory with the answers to the program and the
Java program. To run the Java program, simply type:

- java ConvexHull_GUI.java

This will then display all of the points and the convex hull made by them. If
you would like to look at the file containing every single point, it is in the
same directory as you are currently in, called "test.txt" (regardless of the
filename you entered). The file that contains the points on the hull is called
"hull.txt".
