
#include <vector>

using namespace std;

// A helper class implementing a vertex in 
// an adjacency-list-based graph.
class Vertex
{
        public:
                Vertex(int r, int c)
                {
                        row = r;
                        col = c;
                        bread = nullptr;
                        value = 1000000000;
                }
                int value;

                // Corresponding row and column location in maze
                int row;
                int col;

                // bread crumb to trace back steps
                Vertex* bread;

                // List of neighboring vertices, int is the weight to go to Vertex*
                vector< pair<Vertex*, int> > neighs;
};

