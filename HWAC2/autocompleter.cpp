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

//instead of updating the n top first and then moving to next one, moving to first checking the root top first, then in loop updating n then updating top works.
void Autocompleter::insert(string x, int freq)
{
    Node* n = root;

    
    bool inVect = false;
    //go throught top vector
    for(int i = 0; i < n->top.size(); i++)
    {
        if(n->top[i].s == x)
            inVect = true;
    }
    //item not in current top and adds it and sorts it
    if(!inVect)
    {
        Entry e;
        e.s = x;
        e.freq = freq;
        n->top.push_back(e);
        int size = n->top.size();
        for(int j = 0; j < size; j++)
        {
            for(int k = 0; k < size - j - 1; k++)
            {
                if(n->top[k].freq < n->top[k + 1].freq)
                {
                    Entry temp = n->top[k];
                    n->top[k] = n->top[k + 1];
                    n->top[k + 1] = temp;
                }
            }
        }
        if(n->top.size() > 3)
            n->top.pop_back();
    }

    
    for (int a : x)
    {
        //n needs to go throught each char and find the int(a) to it.
        //while it in its node update itself to correct sorted location on top 3 of the vector
        //if vector is more than 3 pop_back
        //dont crash :)
        
        if(n->children[a] == nullptr)
            n->children[a] = new Node();
        n = n->children[a];

        bool inVect = false;
        //go throught top vector
        for(int i = 0; i < n->top.size(); i++)
        {
            if(n->top[i].s == x)
                inVect = true;
        }
        //item not in current top and adds it and sorts it
        if(!inVect)
        {
            Entry e;
            e.s = x;
            e.freq = freq;
            n->top.push_back(e);
            int size = n->top.size();
            for(int j = 0; j < size; j++)
            {
                for(int k = 0; k < size - j - 1; k++)
                {
                    if(n->top[k].freq < n->top[k + 1].freq)
                    {
                        Entry temp = n->top[k];
                        n->top[k] = n->top[k + 1];
                        n->top[k + 1] = temp;
                    }
                }
            }
            if(n->top.size() > 3)
                n->top.pop_back();
        }
        
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
    for(int a: x)
    {
        if(n->children[a] == nullptr)
            return;
        n = n->children[a];
    }
    for(int i = 0; i < n->top.size(); i++)
        T.push_back(n->top[i].s);
}


