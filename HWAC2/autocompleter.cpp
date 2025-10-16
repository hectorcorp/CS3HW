#include "autocompleter.h"
#include <iostream>
using namespace std;
// Creates a new Autocompleter with an empty dictionary.
//
// Must run in O(1) time.
Autocompleter::Autocompleter()
{
    root = new Node();
    count = 0;
}

// Adds a string x to the dictionary.
// If x is already in the dictionary, does nothing.
//
// Must run in O(1) time.

void Autocompleter::insert(string x, int freq)
{
    Node* n = root;
    Entry e;
    e.freq = freq;
    e.s = x;
    for(char a: x)
    {
        bool inserted = false;
        for(int i = 0; i < n->top.size(); i++)
        {
            if(e.s == n->top[i].s)
            { 
                inserted = true;
                break;
            }
            else if(e.freq > n->top[i].freq)
            {
                n->top.insert(n->top.begin() + i, e);
                inserted = true;
                break;
            }     
        }  
        if(!inserted) 
            n->top.push_back(e);   


        if(n->top.size() > 3)
            n->top.pop_back();

        
        if(n->children[int(a)] == nullptr)
            n->children[int(a)] = new Node();

        n = n->children[int(a)];
    }

    if(n->marked) 
        return;
    n->marked = true;
    count++;
}


// Returns the number of strings in the dictionary.
// 
// Must run in O(1) time.
int Autocompleter::size()
{
    return count;
}

// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then 
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
// 
// Must run in O(1) time.
void Autocompleter::completions(string x, vector<string> &T)
{
    T.clear();
    Node* n = root;
    for(char a: x)
    {
        if(n->children[int(a)] == nullptr)
            return;
        else
            n = n->children[int(a)];
    }
    for(int i = 0; i < n->top.size(); i++)
        T.push_back(n->top[i].s);
}


