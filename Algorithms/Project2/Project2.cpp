// Devin Hopkins
// 4190350

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stack>

// My files
#include "Point.hpp"
#include "ConvexHull.hpp"
#include "HullAlgorithms.hpp"

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

      // Reading in the data points and storing them
      ConvexHull convex;
      convex.readFile(dataFilename);
      
      // Making sure there are at least 3 points in the convex hull
      if (convex.getPointVector()->size() >= 3)
      {
         // Getting ready for the output filename and the algorithm
         std::string outputFile = "";
         std::stack<Point> hullStack;
         HullAlgorithms algorithms;
         if (algType[0]=='G')
         {
            hullStack = algorithms.doGrahamScan();
            outputFile = "hull_G.txt";
         } 
         else if (algType[0]=='J')
         {
            hullStack = algorithms.doJarvisMarch();
            outputFile = "hull_J.txt";
         }
         else
         { //default 
            hullStack = algorithms.doQuickHull();
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