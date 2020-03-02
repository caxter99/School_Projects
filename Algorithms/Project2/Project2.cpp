// Devin Hopkins
// 4190350

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <fstream>
#include <vector>

/*
This chunk of code was adapted from the website: https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
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
std::vector<Point> convexHull(Point points[], int n)
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
   qsort(&points[1], n-1, sizeof(Point), compare);

   // If two or more points make same angle with p0,
   // Remove all but the one that is farthest from p0
   // Remember that, in above sorting, our criteria was
   // to keep the farthest point at the end when more than
   // one points have same angle.
   int m = 1; // Initialize size of modified array
   for (int i=1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0) 
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
This next block of code is entirely my own.
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

/*
This next block of code was given for the assignment. I have adapted it.
*/
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
      
      // Making sure there are at least 3 points in the convex hull
      if (true)
      {
         // Getting ready for the output filename and the algorithm
         std::string outputFile = "";
         std::vector<Point> hullPoints;

         // Getting the points into an array
         std::vector<Point> points;
         getPointsFromFile(dataFilename, &points);
         Point* pointsArr = &points[0];

         // Figuring out the proper algorithm and perform it
         if (algType[0]=='G')
         {
            hullPoints = convexHull(pointsArr, points.size());
            outputFile = "hull_G.txt";
         } 
         else if (algType[0]=='J')
         {
            //
            outputFile = "hull_J.txt";
         }
         else
         { //default 
            //
            outputFile = "hull_Q.txt";
         }
      
         //write your convex hull to the outputFile (see class example for the format)
         //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.
      }
      // There were 0, 1, or 2 points in the convex hull
      else
      {
         std::cout << "There were not enough points in the convex hull.\n";
         std::cout << "There must be at least 3 points." << std::endl;
      }
	}
	return 0;
}