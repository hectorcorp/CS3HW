#include "autocompleter.h"
#include <iostream>
// Optional helper methods (you'll probably want them)

// Returns the size of the binary tree rooted at p.
//
// Should run in O(n) time.
int Autocompleter::size_recurse(Node* p)
{
    if(p == nullptr)
        return 0;
    return 1 + size_recurse(p->left) + size_recurse(p->right);
}

// Fills C with the completions of x in the BST rooted at p.
void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C)
{
    if(p == nullptr) return;
    if(x == p->e.s.substr(0, x.length()))
        C.push_back(p->e);
    if(x >= p->e.s.substr(0, x.length()))
        completions_recurse(x,p->right,C);
    if(x <= p->e.s.substr(0, x.length()))
        completions_recurse(x,p->left,C);
}

// Rebalances the AVL tree rooted at p.
// Helpful for insert().
// Should be called on every node visited during
// the search in reverse search order.
//
// Should run in O(1) time.
void Autocompleter::rebalance(Node* &p)
{
    if (height(p->right) - height(p->left) >= 2)
		{
			if (height(p->right->right) > height(p->right->left))
				left_rotate(p);
			else
            {
                right_rotate(p->right);
                left_rotate(p); 
            }
				
		}
    else if (height(p->left) - height(p->right) >= 2)
    {
        if (height(p->left->left) > height(p->left->right))
            right_rotate(p);
        else
        {
            left_rotate(p->left);
            right_rotate(p); 
        }
            
    }
    else
    {
        //We find this node is not guilty of
        //SUSness.  Do no rotations.
    }
}

// Perform left and right rotations
// of an AVL tree rooted at p (helpful for implementing rebalance).
//
// Should run in O(1) time.
void Autocompleter::right_rotate(Node* &p)
{
    Node* A = p;
    Node* B = p->left;
    Node* br = B->right;

    p = B;
    B->right = A;
    A->left = br;

    update_height(A);
    update_height(B);
}
void Autocompleter::left_rotate(Node* &p)
{
    Node* A = p;
    Node* B = p->right;
    Node* bl = B->left;

    p = B;
    B->left = A;
    A->right = bl;

    update_height(A);
    update_height(B);
}







// Inserts an Entry into an AVL tree rooted at p.
//
// Should run in O(log(n)) time.
void Autocompleter::insert_recurse(Entry e, Node* &p)
{
    if(p == nullptr)
        p = new Node(e);
    else
    {
        if(e.s > p->e.s)
            insert_recurse(e, p->right);
        else
            insert_recurse(e, p->left);
            
        update_height(p);
        rebalance(p);
    }
}


// Creates a new Autocompleter with an empty dictionary.
//
// Must run in O(1) time.
Autocompleter::Autocompleter()
{
    root = nullptr;
}

// Adds a string x to the dictionary.
// If x is already in the dictionary, does nothing.
//
// Must run in O(log(n)) time.
void Autocompleter::insert(string x, int freq)
{
    Entry e = Entry();
    e.s = x;
    e.freq = freq;
    insert_recurse(e, root);
}

// Returns the number of strings in the dictionary
// of possible completions.
//
// Must run in O(n) time.
int Autocompleter::size()
{
    return size_recurse(root);
}

// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
//
// Must run fast.  In particular, you should not search all nodes in the
// tree for possible completions.
// Instead, only search regions of the tree for which a completion could
// be present, which will yield a run time bound of O(k log n ) time,
// where k is the number of completions in the tree.
void Autocompleter::completions(string x, vector<string> &T)
{
    T.clear();
    vector<Entry> E;
    completions_recurse(x,root,E);
    if(E.size() == 0) return;
    else if(E.size() == 1) T.push_back(E[0].s);
    else if(E.size() == 2)
    {
        if(E[0].freq > E[1].freq)
        {
            T.push_back(E[0].s);
            T.push_back(E[1].s);
        }  
        else
        {
            T.push_back(E[1].s);
            T.push_back(E[0].s);
        }
    }
    else
    {
        for(int i = 0; i < 3; i++)
        {
            int mostFreq = 0;
            for(int x = 0; x < E.size(); x++)
            {
                if(E[x].freq > E[mostFreq].freq)
                    mostFreq = x;
            }
            T.push_back(E[mostFreq].s);
            E.erase(E.begin() + mostFreq);
        }
    }
}




