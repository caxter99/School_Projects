# README for Project 2
By: Devin Hopkins

# How to Operate My Project
In a terminal, navigate to the directory containing the project.
In that directory, type:

- make

This will make the necessary files. To run the program, type:

- ./your [Algorithm] [Filename]

- [Algorithm] is G for Graham Scan, J for Jarvis March, or Q for Quickhull.
- [Filename] is the filename that contains the points you would like to test (with the extension).

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

If you have not compiled the Java program yet, type the following to compile it:

- javac ConvexHull_GUI.java

To run the Java program, simply type:

- java ConvexHull_GUI.java

This will then display all of the points and the convex hull made by them. If
you would like to look at the file containing every single point, it is in the
same directory as you are currently in, called "test.txt" (regardless of the
filename you entered). The file that contains the points on the hull is called
"hull.txt".

# Explaining Graham Scan

First, start off at an "extreme" point (meaning the point farthest in one
direction). The bottom point is preferable. Order all of the remaining
points in order of smallest angle to largest angle (relative to the
extreme point, as though angle was between 0 degrees with the bottom
point). Negative points must be put at the end of the sorted list.

Put the point with the next smallest slope onto the stack.

Then, put the point with the next smallest slope onto the stack. Verify that
the turn created is a left turn. If it's not, remove the point that was put
onto the stack before the most recent point was pushed on.

Continue doing this until all of the points have been checked. After doing
this, you will have the convex hull.

# Exaplaining Jarvis March

First, find the point on the left most side of all the points (the point with
the smallest x value). Next, pick a point that has the potential to be another
point on the convex hull (the next point). In this example, I will be going
clockwise. Then, after picking the hopeful next point, see if there are any
points above the line created by connecting the starting point and the point
that was just picked. If there is, replace the original next point with the
point above the line. Repeat this process until there is no point above the
line.

Repeat this process for the newest point. The algorithm stops when the next
point is the starting point.

# Explaining Quick Hull

Find the right and left most points in the set of points. Then, draw a line
connecting these two points. Then, find the point that's the farthest from
this line on either side of the line. If this isn't the first time it's been
done, ignore any points on the inside of the convex hull.

Use the point that's farthest away along with the right (or left) most point
to form a new line. Repeat these steps until no point is outside of the
convex hull. All of the created lines on the outside will form the complete
convex hull.

# Unusual Findings in My Code
The most unusual thing in my code is that the Quickhull returns each point in
the convex hull twice. They're the correct points, but every point is returned
twice. I'm not sure why and it still works perfectly fine in the Java program,
but I couldn't figure out why.
