#include "solve.h"
#include "vertex.h"

//method i found to be able to use a pair as the key for an unordered_map
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

void makeVertex(vector<vector<char>> & map, unordered_map<pair<int,int>, Vertex*, pair_hash>& hashmap, unordered_map<int, vector<Vertex*>>& hashPortals)
{
    for(int col = 0; col < map.size(); col++)
    {
        for(int row = 0; row < map[0].size(); row++)
        {
            if(map[col][row] != '#' && map[col][row] != '\n')
            {
                //assign row/col for vertex
                Vertex* n = new Vertex(row, col);

                //add to hashmap
                hashmap[{col,row}] = n; 

                if(map[col][row] != ' ')
                {
                    hashPortals[map[col][row]].push_back(n);
                }
            }
        }
    }
}

void assignNeighs(unordered_map<pair<int,int>, Vertex*, pair_hash>& hashmap, vector<vector<char>>& map, unordered_map<int, vector<Vertex*>> hashPortals)
{
    for(auto ver : hashmap)
    {
        int row = ver.second->row;
        int col = ver.second->col;

        //Assign every non wall a neighbor to its surrounding vertexs

        //North
        if(hashmap.find({col - 1,row}) != hashmap.end())
        {
            ver.second->neighs.push_back({hashmap.at({col - 1,row}), 1});
        }
        //East
        if(hashmap.find({col,row + 1}) != hashmap.end())
        {
            ver.second->neighs.push_back({hashmap.at({col,row + 1}), 1});
        }
        //South
        if(hashmap.find({col + 1,row}) != hashmap.end())
        {
            ver.second->neighs.push_back({hashmap.at({ col + 1,row }), 1});
        }
        //West
        if(hashmap.find({col,row - 1}) != hashmap.end())
        {
            ver.second->neighs.push_back({hashmap.at({col,row - 1}), 1});
        }
        //Connect a portal to another portal
        if(map[col][row] != ' ')
        {
            for(Vertex* portalVert : hashPortals.at(map[col][row]))
            {
                if(portalVert != ver.second)
                {
                    ver.second->neighs.push_back({portalVert, map[col][row] - '0'});
                }
            }
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
                    hashmap.at({col, row})->value = 0;
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


void dijkstra(Vertex* start, unordered_map<pair<int,int>, Vertex*, pair_hash> hashmap, Vertex* end)
{
    MinPriorityQueue<Vertex*> PQ;
    for(auto& ver : hashmap)
    {
        PQ.push(ver.second, ver.second->value);
    }

    while(PQ.size() > 0)
    {
        Vertex* v = PQ.front();
        if (v == end) break;
        PQ.pop();
        for(pair<Vertex*, int> neighbor : v->neighs)
        {
            if(v->value + neighbor.second < neighbor.first->value)
            {
                neighbor.first->value = v->value + neighbor.second;
                neighbor.first->bread = v;
                PQ.decrease_key(neighbor.first, neighbor.first->value);
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
    unordered_map<int, vector<Vertex*>> hashPortals;   
    unordered_map<pair<int,int>, Vertex*, pair_hash> hashmap;
    Vertex* start;
    Vertex* end;

    //Make a 2d array of char to match maze
    assignMap(map, maze);

    //Add vertex items to hashmap
    makeVertex(map, hashmap, hashPortals);

    //Assign neighbors to all vertexes
    assignNeighs(hashmap, map, hashPortals);

    //Find both exits
    findExits(map, hashmap, start, end);

    //Use Breadth first search on the start
    dijkstra(start, hashmap, end);

    //Update map with 'o' using the bread trails from exit to start
    updateMap(map, end);

    //add map to string
    answer = mapToString(map);

    return answer;
}
