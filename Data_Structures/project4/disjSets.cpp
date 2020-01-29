
// Devin Hopkins
// 4190350
// djh155@zips.uakron.edu

#include "DisjSets.h"


/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjSets::DisjSets( int numElements ) : s( numElements, -1 )
{
}

/**
 * Union two disjoint sets.
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set names.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 * Be careful, this could cause a problem.
 */
void DisjSets::unionSets( int root1, int root2 )
{
    if( s[ root2 ] < s[ root1 ] )  // root2 is deeper
        s[ root1 ] = root2;        // Make root2 new root
    else
    {
        if( s[ root1 ] == s[ root2 ] )
            --s[ root1 ];          // Update height if same
        s[ root2 ] = root1;        // Make root1 new root
    }
}



/**
 * TO DO: YOU will write code for this function.
 * You need to perform a find with path compression
 * per exercise 8.16 in the book.  This will be a 
 * recursive function.
 * 
 * Return the set containing x.  
 * That is, you will need to return the root;
 * be careful!
 */
int DisjSets::find( int x )
{
    // If the value held is less than 0, then position x holds the position
    // of the root node, so x is returned
   if (s[x] < 0)
   {
       return x;
   }
   // If the value held is greater than or equal to 0, then the current node must not
   // be the root node. Therefore, the root node must be one of the parents of the
   // current node (or one of the parent's parents)
   else
   {
       return s[x] = find(s[x]);
   }
}

/* TO DO: Write this code.  
 * Return true if the two nieghbors are in the same set.
*/
bool DisjSets::isConnected(int n1, int n2)
{
    // If the root of both of the nodes sent in is the same, then they're connected
    if (find(n1) == find(n2))
    {
        return true;
    }

    // If their root nodes are different, then they're not connected
    return false;
}