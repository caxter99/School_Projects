// Devin Hopkins
// 4190350

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <fstream>
#include <vector>
#include <set>
#include <time.h>
#include <chrono>
#include <cmath>

// Constants
const bool USE_USER_FILE_INPUT = false; // If this is true, it will use whatever file the user enters to test for convex halls.
         // Otherwise, uses the vector of all of the available test files
const bool ALWAYS_USE_DEFAULT_FILENAME = true; // If true, this will always use the default filename, regardless
std::vector<std::string> ALL_TEST_FILES; // This list contains all of the test files. These are used if USE_USER_INPUT is false (must be
         // loaded first, however)
const std::string PREFIX_FOR_TEST_CASES = "GUI4ConvexHall/Data/"; // This is the prefix for all of the test case files
const std::string NON_ERROR_OUTPUT_FILENAME = "hull.txt"; // This is the default output filename if one can't be determined and the default
         // can't be used
const bool DISPLAY_MILLISECONDS = false; // If true, displays the milliseconds
const std::string PREFIX_FOR_JAVA_OUTPUT = "GUI4ConvexHall/"; // The prefix for everything written to be easily used by the Java program
const std::string TEST_FILE_FOR_JAVA_OUTPUT = "test.txt"; // The test name for the Java program
const std::string HULL_FILE_FOR_JAVA_OUTPUT = "hull.txt"; // The name of the hull for the Java program

/*
This next chunk of code was adapted from the website: https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
*/
struct Point
{
    int x, y;
};

// A global point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;

// A utility function to find next to top in a stack
Point nextToTop(std::stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}
  
// A utility function to swap two points
// Is return type int in the example???
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2) 
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   // Find orientation 
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
std::vector<Point> doGrahamScan(Point points[], int n)
{
   // Creating the vector to return
   std::vector<Point> hullPoints;

   // Find the bottommost point
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;

     // Pick the bottom-most or chose the left
     // most point in case of tie
     if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }

   // Place the bottom-most point at first position
   swap(points[0], points[min]);

   // Sort n-1 points with respect to the first point.
   // A point p1 comes before p2 in sorted output if p2
   // has larger polar angle (in counterclockwise
   // direction) than p1
   p0 = points[0];
   qsort(&points[1], n - 1, sizeof(Point), compare);

   // If two or more points make same angle with p0,
   // Remove all but the one that is farthest from p0
   // Remember that, in above sorting, our criteria was
   // to keep the farthest point at the end when more than
   // one points have same angle.
   int m = 1; // Initialize size of modified array
   for (int i = 1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0) 
          i++;
  
       points[m] = points[i];
       m++;  // Update size of modified array
   }

   // If modified array of points has less than 3 points,
   // convex hull is not possible
   if (m < 3) return hullPoints;

   // Create an empty stack and push first three points
   // to it.
   std::stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   // Process remaining n-3 points
   for (int i = 3; i < m; i++)
   {
      // Keep removing top while the angle formed by
      // points next-to-top, top, and points[i] makes
      // a non-left turn
      while (orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }

   // Now stack has the output points, print contents of stack
   // and store them in the vector to return
   while (!S.empty())
   {
       Point p = S.top();
       hullPoints.push_back(p);
       std::cout << "(" << p.x << ", " << p.y <<")" << std::endl;
       S.pop();
   }

   // Returning the points
   return hullPoints;
}

/*
This next chunk of code is adaptd from the website: https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
*/
// Prints convex hull of a set of n points.
std::vector<Point> doJarvisMarch(Point points[], int n)
{
   // Creating the vector to return
   std::vector<Point> hullPoints;

   // There must be at least 3 points
   if (n < 3) return hullPoints;

   // Initialize Result
   std::vector<Point> hull;

   // Find the leftmost point
   int l = 0;
   for (int i = 1; i < n; i++)
      if (points[i].x < points[l].x)
         l = i;

   // Start from leftmost point, keep moving counterclockwise
   // until reach the start point again.  This loop runs O(h)
   // times where h is number of points in result or output.
   int p = l, q;
   do
   {
      // Add current point to result
      hull.push_back(points[p]);

      // Search for a point 'q' such that orientation(p, x,
      // q) is counterclockwise for all points 'x'. The idea
      // is to keep track of last visited most counterclock-
      // wise point in q. If any point 'i' is more counterclock-
      // wise than q, then update q.
      q = (p + 1) % n;
      for (int i = 0; i < n; i++)
      {
         // If i is more counterclockwise than current q, then
         // update q
         if (orientation(points[p], points[i], points[q]) == 2)
            q = i;
      }
  
      // Now q is the most counterclockwise with respect to p
      // Set p as q for next iteration, so that q is added to
      // result 'hull'
      p = q;
  
   } while (p != l);  // While we don't come to first point
  
   // Print Result 
   for (int i = 0; i < hull.size(); i++)
   {
      hullPoints.push_back(hull[i]);
      std::cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
   }

   // Return the result
   return hullPoints;
}

/*
This next chunk of code is adapted from the following website: https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/
*/

// Stores the result (points of convex hull)
std::vector<Point> hull;

// Returns the side of point p with respect to line
// joining points p1 and p2.
int findSide(Point p1, Point p2, Point p)
{
   int val = (p.y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p.x - p1.x);
  
   if (val > 0)
      return 1;
   if (val < 0)
      return -1;
   return 0;
}
  
// returns a value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
int lineDist(Point p1, Point p2, Point p)
{
   return abs ((p.y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p.x - p1.x));
}
  
// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(std::vector<Point>* a, int n, Point p1, Point p2, int side)
{
   int ind = -1;
   int max_dist = 0;
  
   // finding the point with maximum distance
   // from L and also on the specified side of L.
   for (int i = 0; i < n; i++)
   {
      int temp = lineDist(p1, p2, a->at(i));
      if (findSide(p1, p2, a->at(i)) == side && temp > max_dist)
      {
         ind = i;
         max_dist = temp;
      }
   }

   // If no point is found, add the end points
   // of L to the convex hull.
   if (ind == -1)
   {
      hull.push_back(p1);
      hull.push_back(p2);
      return;
   }

   // Recur for the two parts divided by a[ind]
   quickHull(a, n, a->at(ind), p1, -findSide(a->at(ind), p1, p2));
   quickHull(a, n, a->at(ind), p2, -findSide(a->at(ind), p2, p1));
}

std::vector<Point> doQuickHull(std::vector<Point>* a, int n)
{
   // Creating the return hull points
   std::vector<Point> hullPoints;

   // a[i].second -> y-coordinate of the ith point
   if (n < 3)
   {
      return hullPoints;
   }
  
   // Finding the point with minimum and
   // maximum x-coordinate
   int min_x = 0, max_x = 0;
   for (int i = 1; i < n; i++)
   {
      if (a->at(i).x < a->at(min_x).x)
         min_x = i;
      if (a->at(i).x > a->at(max_x).x)
         max_x = i;
   }
  
   // Recursively find convex hull points on
   // one side of line joining a[min_x] and
   // a[max_x]
   quickHull(a, n, a->at(min_x), a->at(max_x), 1);
  
   // Recursively find convex hull points on
   // other side of line joining a[min_x] and
   // a[max_x]
   quickHull(a, n, a->at(min_x), a->at(max_x), -1);
  
   std::cout << "The points in Convex Hull are:\n";
   for (int x = 0; x < hull.size(); x++)
   {
      // Creating a point and adding it
      hullPoints.push_back(hull.at(x));

      // Displaying the point
      std::cout << "(" << hull.at(x).x << ", " << hull.at(x).y << ") ";
   }

   // Clearing the vector
   hull.clear();

   // Return the hullPoints
   return hullPoints;
}

/*
This next chunk of code was adapted from the website: https://stackoverflow.com/questions/53072989/sort-2d-points-counter-clockwise
*/
double getClockwiseAngle(Point p)
{
   double angle = 0.0;
   angle = atan2(p.x, -p.y);
   return angle;
}

bool comparePoints(Point p1, Point p2)
{
   return getClockwiseAngle(p1) < getClockwiseAngle(p2);
}

/*
This next chunk of code is entirely my own.
*/
void getPointsFromFile(std::string filename, std::vector<Point>* points)
{
   // Creating a file reading object
   std::ifstream inputFile;
   inputFile.open(filename);
   if (inputFile)
   {
      // Creating the variables that are needed
      std::string tempString = "";
      int num1, num2;

      // Lopping through the entire file to get all of the data
      while(!inputFile.eof())
      {
         // Getting the x and y points from the line
         getline(inputFile, tempString);
         num1 = stoi(tempString.substr(0, tempString.find("\t")));
         num2 = stoi(tempString.substr(tempString.find("\t") + 1));

         // Creating a point from the data gathered
         Point p;
         p.x = num1;
         p.y = num2;
         points->push_back(p);
      }
   }
   else
   {
      // Letting the user know the filename they entered couldn't be opened
      std::cout << "The file " << filename << " could not be opened." << std::endl;
   }

   // Closing the file
   inputFile.close();
}

void writePointsToFile(std::string filename, std::vector<Point>* points)
{
   // Making sure there are enough points to write it to the file
   if (points->size() >= 3)
   {
      // Making the writing file object
      std::ofstream outputFile;
      outputFile.open(filename);
      if (outputFile)
      {
         // Just so the variable doesn't have to be recreated all the time
         std::string stringToWrite = "";

         // Looping through the entire point vector to make sure every point is written
         for(std::vector<Point>::iterator iter = (*points).begin(); iter != (*points).end(); iter++)
         {
            // Creating the string to write to the file
            stringToWrite = "" + std::to_string((*iter).x) + "\t" + std::to_string((*iter).y) + "\n";

            // Writing the string to the file
            //outputFile.write(stringToWrite);
            outputFile << stringToWrite;
         }
      }
      else
      {
         // Letting the user know the filename they entered couldn't be opened
         std::cout << "The file " << filename << " could not be opened." << std::endl;
      }
   }
}

void writePointsForJavaProgram(std::string testFilename, std::string hullFilename, std::vector<Point>* testPoints, std::vector<Point>* hullPoints)
{
   // Writing the test points to the Java program
   writePointsToFile(PREFIX_FOR_JAVA_OUTPUT + testFilename, testPoints);

   // Writing the hull points to the Java program
   writePointsToFile(PREFIX_FOR_JAVA_OUTPUT + hullFilename, hullPoints);
}

void loadTestCaseArray()
{
   // Loading all of the test cases
   //
   // onTriangle
   /*ALL_TEST_FILES.push_back("onTriangle_10.txt");
   ALL_TEST_FILES.push_back("onTriangle_100.txt");
   ALL_TEST_FILES.push_back("onTriangle_1000.txt");
   ALL_TEST_FILES.push_back("onTriangle_10000.txt");
   ALL_TEST_FILES.push_back("onTriangle_100000.txt");
   ALL_TEST_FILES.push_back("onTriangle_1000000.txt");
   // onRectangle
   ALL_TEST_FILES.push_back("onRectangle_10.txt");
   ALL_TEST_FILES.push_back("onRectangle_100.txt");
   ALL_TEST_FILES.push_back("onRectangle_1000.txt");
   ALL_TEST_FILES.push_back("onRectangle_10000.txt");
   ALL_TEST_FILES.push_back("onRectangle_100000.txt");
   ALL_TEST_FILES.push_back("onRectangle_1000000.txt");
   // rectangle
   ALL_TEST_FILES.push_back("rectangle_10.txt");
   ALL_TEST_FILES.push_back("rectangle_100.txt");
   ALL_TEST_FILES.push_back("rectangle_1000.txt");
   ALL_TEST_FILES.push_back("rectangle_10000.txt");
   ALL_TEST_FILES.push_back("rectangle_100000.txt");
   ALL_TEST_FILES.push_back("rectangle_1000000.txt");
   // onCircle
   ALL_TEST_FILES.push_back("onCircle_10.txt");
   ALL_TEST_FILES.push_back("onCircle_100.txt");
   ALL_TEST_FILES.push_back("onCircle_1000.txt");
   ALL_TEST_FILES.push_back("onCircle_10000.txt");
   ALL_TEST_FILES.push_back("onCircle_100000.txt");
   ALL_TEST_FILES.push_back("onCircle_1000000.txt");*/
   // circle
   /*ALL_TEST_FILES.push_back("circle_10.txt");
   ALL_TEST_FILES.push_back("circle_100.txt");
   ALL_TEST_FILES.push_back("circle_1000.txt");
   ALL_TEST_FILES.push_back("circle_10000.txt");
   ALL_TEST_FILES.push_back("circle_100000.txt");
   ALL_TEST_FILES.push_back("circle_1000000.txt");*/
   // triangle
   ALL_TEST_FILES.push_back("triangle_10.txt");
   ALL_TEST_FILES.push_back("triangle_100.txt");
   ALL_TEST_FILES.push_back("triangle_1000.txt");
   ALL_TEST_FILES.push_back("triangle_10000.txt");
   ALL_TEST_FILES.push_back("triangle_100000.txt");
   ALL_TEST_FILES.push_back("triangle_1000000.txt");
}

std::string getOutputFilename(std::string inputFilename)
{
   // Creating the string in its default form
   std::string outputFilename = NON_ERROR_OUTPUT_FILENAME;

   // Getting the position of the underscore
   int underscorePos = inputFilename.find(".");

   // Making sure the underscore is present
   if (underscorePos != -1)
   {
      // Getting the new output filename
      outputFilename = inputFilename.substr(0, underscorePos) + "_hull.txt";
   }

   // Returning the filename
   return outputFilename;
}

int main(int argc, char *argv[])
{   
   if (argc < 3)
   {
      std::cout << "wrong format! should be \"a.exe algType dataFile\"";
   }
   else
   {
      // Separating the algorithm type and the data filename
      std::string algType = argv[1];
      std::string dataFilename = argv[2];

      // This is the limit about how many times the loop will run
      int loopLimit = 0;
      
      // If we're using the user's input
      if (USE_USER_FILE_INPUT)
      {
         loopLimit = 1;
      }
      // We're not using the user's input
      else
      {
         loadTestCaseArray();
         loopLimit = ALL_TEST_FILES.size();
      }

      // Looping through all of the necessary test cases
      for (int x = 0; x < loopLimit; ++x)
      {
         // If we're not using the user's input
         if (!USE_USER_FILE_INPUT)
         {
            dataFilename = PREFIX_FOR_TEST_CASES + ALL_TEST_FILES.at(x);
         }

         // Getting ready for the output filename and the algorithm
         std::string outputFile = "";
         std::vector<Point> hullPoints;

         // Variable to keep track of the start and end times
         time_t start, end;
         float startms, endms;

         // Getting the points into an array
         std::vector<Point> points;
         getPointsFromFile(dataFilename, &points);
         Point* pointsArr = &points[0];

         // Telling the user the computing details
         std::string computation = ALL_TEST_FILES.at(x).substr(0, ALL_TEST_FILES.at(x).find("."));
         std::cout << "Current Method: " << algType[0] << std::endl;
         std::cout << "Current Set of Data Points:" << computation << std::endl;

         // Figuring out the proper algorithm and perform it
         if (algType[0] == 'G')
         {
            start = time(0);
            startms = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count();
            hullPoints = doGrahamScan(pointsArr, points.size());
            endms = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count();
            end = time(0);
            outputFile = "hull_G.txt";
         } 
         else if (algType[0] == 'J')
         {
            start = time(0);
            startms = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count();
            hullPoints = doJarvisMarch(pointsArr, points.size());
            endms = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count();
            end = time(0);
            outputFile = "hull_J.txt";
         }
         else
         { //default 
            start = time(0);
            startms = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count();
            hullPoints = doQuickHull(&points, points.size());
            //hullPoints = doQuickHull(convertPointsToiPair(pointsArr), points.size());
            endms = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count();
            end = time(0);
            outputFile = "hull_Q.txt";

            // The hullPoints must be sorted as they aren't in clockwise or counterclockwise order
            sort(hullPoints.begin(), hullPoints.end(), comparePoints);
         }
      
         // Write the data to the file if applicable
         if (hullPoints.size() >= 3)
         {
            // This is to get the name for the output file, if we're not using user input
            if (!USE_USER_FILE_INPUT and !ALWAYS_USE_DEFAULT_FILENAME)
            {
               // Getting the name of the output file
               outputFile = getOutputFilename(ALL_TEST_FILES.at(x));
            }

            // Writing the points to the file
            writePointsToFile(outputFile, &hullPoints);

            // Write files to be tested by the Java program
            //writePointsForJavaProgram(std::string testFilename, std::string hullFilename, std::vector<Point>* testPoints, std::vector<Point>* hullPoints)
            writePointsForJavaProgram(TEST_FILE_FOR_JAVA_OUTPUT, HULL_FILE_FOR_JAVA_OUTPUT, &points, &hullPoints);

            // Displaying the time it took
            if (DISPLAY_MILLISECONDS)
            {
               std::cout << "startms:" << startms << ":\n";
               std::cout << "endms:" << endms << ":\n";
               std::cout << "Time to compute: " << (endms - startms) << " milliseconds\n";
            }
            std::cout << "Time to compute: " << difftime(end, start) << " seconds\n\n";
         }
         // Something is wrong with the data
         else
         {
            // Letting the user know there was something wrong
            std::cout << "There were less than 3 points in the convex hull.\n";
            std::cout << "This either means the file couldn't be read or it was\n";
            std::cout << "not a valid convex hull. No data was written to any file.\n";
            std::cout << "File used: " << dataFilename << "\n\n";
         }
      }
	}

   // Ending without an error
	return 0;
}