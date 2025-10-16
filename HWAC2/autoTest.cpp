#include "autocompleter.h"
#include <algorithm>
using namespace std;

Autocompleter::Autocompleter()
{
    root = new Node();
    count = 0;
}

void Autocompleter::insert(string x, int freq)
{
    // Update root->top first so completions("") works correctly
    {
        bool exists = false;
        for (auto &e : root->top)
            if (e.s == x)
                exists = true;
        if (!exists)
        {
            Entry e;
            e.s = x;
            e.freq = freq;
            root->top.push_back(e);
            sort(root->top.begin(), root->top.end(),
                 [](const Entry &a, const Entry &b) { return a.freq > b.freq; });
            if (root->top.size() > 3)
                root->top.pop_back();
        }
    }

    Node* n = root;

    for (unsigned char c : x)
    {
        if (n->children[c] == nullptr)
            n->children[c] = new Node();

        n = n->children[c];

        bool exists = false;
        for (auto &e : n->top)
            if (e.s == x)
                exists = true;
        if (!exists)
        {
            Entry e;
            e.s = x;
            e.freq = freq;
            n->top.push_back(e);
            sort(n->top.begin(), n->top.end(),
                 [](const Entry &a, const Entry &b) { return a.freq > b.freq; });
            if (n->top.size() > 3)
                n->top.pop_back();
        }
    }

    if (!n->marked)
    {
        n->marked = true;
        count++;
    }
}

int Autocompleter::size()
{
    return count;
}

void Autocompleter::completions(string x, vector<string> &T)
{
    Node* n = root;

    for (unsigned char c : x)
    {
        if (n->children[c] == nullptr)
        {
            T.clear();
            return;
        }
        n = n->children[c];
    }

    T.clear();
    for (auto &e : n->top)
        T.push_back(e.s);
}
