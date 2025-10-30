#include "solve.h"
#include "vertex.h"


struct pair_hash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};


void assignMap(vector<vector<char>>& map, string maze)
{
    vector<char> row;
    for(char a: maze)
    {
        if(a != '\n')
            row.push_back(a);
        else
        {
            map.push_back(row);
            row.clear();
        }
    }
}


void makeVertex(vector<vector<char>> & map, unordered_map<pair<int,int>, Vertex*, pair_hash> & hashmap)
{
    for(int col = 0; col < map.size(); col++)
    {
        for(int row = 0; row < map[0].size(); row++)
        {
            if(map[col][row] == ' ')
            {
                //assign row/col for vertex
                Vertex* n = new Vertex(row, col);

                //add to hashmap
                hashmap[{col,row}] = n; 
            }
        }
    }
}


void assignNeighs(unordered_map<pair<int,int>, Vertex*, pair_hash>& hashmap)
{
    for(auto ver : hashmap)
    {
        int row = ver.second->row;
        int col = ver.second->col;

        //North
        if(hashmap.find({col - 1,row}) != hashmap.end())
        {
            ver.second->neighs.push_back(hashmap.at({col - 1,row}));
        }
        //East
        if(hashmap.find({col,row + 1}) != hashmap.end())
        {
            ver.second->neighs.push_back(hashmap.at({col,row + 1}));
        }
        //South
        if(hashmap.find({col + 1,row}) != hashmap.end())
        {
            ver.second->neighs.push_back(hashmap.at({col + 1,row}));
        }
        //West
        if(hashmap.find({col,row - 1}) != hashmap.end())
        {
            ver.second->neighs.push_back(hashmap.at({col,row - 1}));
        }
    } 
}


void findExits(vector<vector<char>>& map, unordered_map<pair<int,int>, Vertex*, pair_hash> hashmap, Vertex*& start, Vertex*& end)
{
    bool foundFirst = false;
    for(int col = 0; col < map.size(); col++)
    {
        for(int row = 0; row < map[0].size(); row++)
        {
            if(!foundFirst && (col == 0 || row == 0 || col == map.size() - 1 || row == map[0].size() - 1))
            {
                if (hashmap.find({ col,row }) != hashmap.end())
                {
                    start = hashmap.at({col, row});
                    foundFirst = true;
                }
                
            }
            else if(foundFirst && (col == 0 || row == 0 || col == map.size() - 1 || row == map[0].size() - 1))
            {
                if (hashmap.find({ col,row }) != hashmap.end())
                    end = hashmap.at({col, row});
            }
        }
    }
}


void breadthFirstSearch(Vertex* start)
{
    unordered_set<Vertex*> marked;
    queue<Vertex*> Q;
    marked.insert(start);
    Q.push(start);

    while(!Q.empty())
    {
        Vertex* n = Q.front();
        Q.pop();

        for(auto vert : n->neighs)
        {
            if(marked.find(vert) == marked.end())
            {
                marked.insert(vert);
                Q.push(vert);

                vert->bread = n;
            }
        }
    }
}


void updateMap(vector<vector<char>>& map, Vertex* end)
{
    Vertex* n = end;
    while(n != nullptr)
    {
        map[n->col][n->row] = 'o';
        n = n->bread;
    }
}


string mapToString(vector<vector<char>> map)
{
    string s = "";
    for(int col = 0; col < map.size(); col++)
    {
        for(int row = 0; row < map[0].size(); row++)
        {
            s += map[col][row];
        }
        s += '\n';
    }
    return s;
}

string solve(string maze)
{
    string answer = "";
    vector<vector<char>> map;
    unordered_map<pair<int,int>, Vertex*, pair_hash> hashmap;
    Vertex* start;
    Vertex* end;

    //Make a 2d array of char to match maze
    assignMap(map, maze);

    //Add vertex items to hashmap
    makeVertex(map, hashmap);

    //Assign neighbors to all vertexes
    assignNeighs(hashmap);

    //Find both exits
    findExits(map, hashmap, start, end);

    //Use Breadth first search on the start
    breadthFirstSearch(start);

    //Update map with 'o' using the bread trails from exit to start
    updateMap(map, end);

    //add map to string
    answer = mapToString(map);

    return answer;
}
