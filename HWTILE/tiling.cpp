
#include "tiling.h"
#include "vertex.h"

using namespace std;


// Finds a (shortest according to edge length) augmenting path
// from s to t in a graph with vertex set V.
// Returns whether there is an augmenting path.
bool augmenting_path(Vertex* s, Vertex* t, 
        unordered_set<Vertex*> V, vector<Vertex*> &P)
{
        // Check that s and t aren't nullptr
        if (s == nullptr || t == nullptr)
	{
		cerr << "augmenting_path() was passed nullptr s or t." << endl;
		abort();
	}

        // Check that s and t are in the graph
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "augmenting_path() was passed s or t not in V." << endl;
		abort();
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "augmenting_path() was passed invalid vertex." << endl;
				abort();
			}

        // Since augmenting paths should have the fewest edges,
	// not the minimum weight, run BFS.
	queue<Vertex*> Q;
	Q.push(s);

	unordered_set<Vertex*> R;
	R.clear(); 
	R.insert(s);

	unordered_map<Vertex*, Vertex*> prev;

	while (!Q.empty())
	{
		Vertex* cur = Q.front();
		Q.pop();

		for (Vertex* nei : cur->neighs)
		{
			// Must have positive edge weight
			if (cur->weights[nei] == 0)
				continue;

			if (R.find(nei) == R.end())
			{
				Q.push(nei);
				R.insert(nei);
				prev[nei] = cur; 
			}
		}
	}      

        // If BFS never reached t
        if (R.find(t) == R.end())
                return false;

        // Reconstruct shortest path backwards
        P.clear();
        P.push_back(t);
        while (P[P.size()-1] != s)
                P.push_back(prev[P[P.size()-1]]);

        // Reverse shortest path
        for (int i = 0; i < P.size()/2; ++i)
		swap(P[i], P[P.size()-1-i]);

        return true;
}

// Returns the maximum flow from s to t in a weighted graph with vertex set V.
// Assumes all edge weights are non-negative.
int max_flow(Vertex* s, Vertex* t, unordered_set<Vertex*> V)
{
	// If s or t is invalid.
        if (s == nullptr || t == nullptr)
	{
		cerr << "max_flow() was passed nullptr s or t." << endl;
		abort(); 
	}

	// If s or t is not in the vertex set.
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "max_flow() was passed s or t not in V." << endl;
		abort(); 
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "max_flow() was passed invalid vertex." << endl;
				abort();
			}

        // Create a deep copy of V to use as the residual graph
        unordered_set<Vertex*> resV;
        unordered_map<Vertex*, Vertex*> C; // Maps vertices in V to copies in resV
        for (Vertex* vp : V)
        {
                Vertex* rp = new Vertex;
                resV.insert(rp);
                C[vp] = rp;
        }
        for (Vertex* vp : V)
                for (Vertex* np : vp->neighs)
                {
                        C[vp]->neighs.insert(C[np]);
                        C[vp]->weights[C[np]] = vp->weights[np];
                }
	// Add any missing necessary "back" edges. 
        for (Vertex* vp : V)
                for (Vertex* np : vp->neighs)
		{
			if (C[np]->neighs.find(C[vp]) == C[np]->neighs.end())
			{
				C[np]->neighs.insert(C[vp]);
				C[np]->weights[C[vp]] = 0;
			}
		}

        // Run Edmonds-Karp
        while (true)
        {
                // Find an augmenting path
                vector<Vertex*> P;
                if (!augmenting_path(C[s], C[t], resV, P))
                        break;  
                // Update residual graph
                for (int i = 0; i < P.size()-1; ++i)
                {
                        --((*(resV.find(P[i])))->weights[P[i+1]]);
                        ++((*(resV.find(P[i+1])))->weights[P[i]]);
                }
        }

        // Compute actual flow amount
        int flow = 0;
        for (Vertex* snp : C[s]->neighs)
                flow += 1 - C[s]->weights[snp];

        // Delete residual graph
        for (Vertex* vp : resV)
                delete vp;

        return flow;
}


void getColRow(int& col, int& row, string key)
{
	int c = key.find(',');
	col = stoi(key.substr(0, c));
	row = stoi(key.substr(c+1));
}

string makeCord(int col, int row)
{
	return to_string(col) + "," + to_string(row);
}


void fillMap(unordered_map<string, Vertex*>& map, string floor)
{
	int col = 0;
	int row = 0;
	for(char c : floor)
	{
		if(c != '\n')
		{
			if(c == ' ')
			{
				//add to map
				Vertex* v = new Vertex;
				map[makeCord(col, row)] = v;	
			}
			//update col
			col++;
		}
		else
		{
			col = 0;
			row++;
		}
	}
}



void assignNeighs(unordered_map<string, Vertex*>& map)
{
	for(auto &pair : map)
	{
		string key = pair.first;
		Vertex* v = pair.second;

		int col = 0;
		int row = 0;
		getColRow(col, row, key);

		if((col + row) % 2 != 0)
		{
			continue;
		}

		//check directions and add neights with weights
		//north
		if(map.find(makeCord(col + 1, row)) != map.end())
		{
			v->neighs.insert(map.at(makeCord(col + 1, row)));
			v->weights[map.at(makeCord(col + 1, row))] = 1;
		}
		//east
		if(map.find(makeCord(col, row + 1)) != map.end())
		{
			v->neighs.insert(map.at(makeCord(col, row + 1)));
			v->weights[map.at(makeCord(col, row + 1))] = 1;
		}
		//south
		if(map.find(makeCord(col - 1, row)) != map.end())
		{
			v->neighs.insert(map.at(makeCord(col - 1, row)));
			v->weights[map.at(makeCord(col - 1, row))] = 1;
		}
		//west
		if(map.find(makeCord(col, row - 1)) != map.end())
		{
			v->neighs.insert(map.at(makeCord(col, row - 1)));
			v->weights[map.at(makeCord(col, row - 1))] = 1;
		}
	}
}

void assignToS(Vertex* s, unordered_map<string, Vertex*> map)
{
	for(auto& pair : map)
	{
		string key = pair.first;
		Vertex* v = pair.second;

		int col = 0;
		int row = 0;
		getColRow(col, row, key);

		if((col + row) % 2 == 0)
		{
			s->neighs.insert(v);
			s->weights[v] = 1;
		}


	}
}

void assignToT(Vertex* t, unordered_map<string, Vertex*> map)
{
	for(auto& pair : map)
	{
		string key = pair.first;
		Vertex* v = pair.second;

		int col = 0;
		int row = 0;
		getColRow(col, row, key);

		if((col + row) % 2 == 1)
		{
			v->neighs.insert(t);
			v->weights[t] = 1;
		}
	}
}
bool has_tiling(string floor)
{
	unordered_map<string, Vertex*> map;
	Vertex* s = new Vertex;
	Vertex* t = new Vertex;
	unordered_set<Vertex*> V;

	//add every space char to map
	fillMap(map, floor); 

	//assign neighs to each vertex
	assignNeighs(map);


	//connect checkered half of vertexs to s and t
	assignToS(s, map);

	assignToT(t, map);



	//add all vectors to V
	for(auto pair : map)
	{
		V.insert(pair.second);
	}
	V.insert(s);
	V.insert(t);
	
	vector<Vertex*> P;
	if(augmenting_path(s, t, V, P) && V.size() % 2 == 0)
	{
		return (V.size() - 2) / 2 == max_flow(s, t, V);
	}
	return false;
}




