#include "trendtracker.h"

// Creates a Trendtracker containing hashtags
// found in the provided file.
// The file is promised to have the following format:
//
// string1
// string2
// ...
// stringN
//
// where string1 < string2 < ... < stringN
//
// Must run in O(n) time.
Trendtracker::Trendtracker(string filename)
{

    //opens the file as inFile
    ifstream inFile(filename);
    string line;

    //checks if the file actually opens
    if(!inFile.is_open())
        return;
    
    //counters for inputing correct data in S vector
    int count = 3;
    int lineCount = 0;

    //while in the file there is a line, create an entry and push it to E
    //also adds the first 3 items in the file to S
    while(getline(inFile, line))
    {      
        Entry tempE;
        tempE.hashtag = line;
        tempE.pop = 0;
        E.push_back(tempE);
        if(count > 0)
        {
            S.push_back(lineCount);
            count--;
        }
        lineCount++;
    }
    
    //if S wasnt fully filled with 3 items, fill it with null items
    for(int i = 0; i < count; i++)
    {
        S.push_back(-1);
    }

    //close the file
    inFile.close();
}


// Return the number of hashtags in the Trendtracker.
//
// Must run in O(1) time.
int Trendtracker::size()
{
    return E.size();
}

// Optional helper method.
// Returns the index of E containing an Entry with hashtag ht.
// If no such hashtag is found, returns -1.
//
// Should run in O(log(n)).
int Trendtracker::search(string ht)
{
    //counter for start and end of search span
    int s = 0;
    int e = E.size() - 1;
    //while the start is not bigger than the end, continue with the search
    while(s <= e)
    {
        //creats a mid point to check
        int m = (s + e) / 2;

        //either returns or moves a point of the search to continue with
        if(E[m].hashtag == ht)
            return m;
        if(E[m].hashtag < ht)
            s = m + 1;
        if(E[m].hashtag > ht)
            e = m - 1;
    }

    return -1;
}

// Adds 1 to the total number times a hashtag has been tweeted.
// If the hashtag does not exist in TrendTracker, does nothing.
//
// Must run in O(log(n)) time.
void Trendtracker::tweeted(string ht)
{
    //find the index of the tweeted string
    int index = search(ht);

    //checks if the string was in the trendtracker
    if(index < 0)
        return;
    
    //adds one to the population of the tweet
    E[index].pop += 1;

    //if statements used to sort S vector
    if(E[S[0]].pop < E[S[1]].pop)
        {
            int temp = S[0];
            S[0] = S[1];
            S[1] = temp;
        }
    if(E[S[0]].pop < E[S[2]].pop)
        {
            int temp = S[0];
            S[0] = S[2];
            S[2] = temp;
        }
    if(E[S[1]].pop < E[S[2]].pop)
        {
            int temp = S[1];
            S[1] = S[2];
            S[2] = temp;
        }    

    //goes through S vector and places ht in correct place
    for(int i = 0; i < 3; i++)
    {
        if(S[i] == index)
            break;
        if(E[index].pop > E[S[i]].pop)
        {
            S.insert(S.begin() + i, index);
            S.pop_back();
            break;
        }
    }
}

// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
//
// Must run in O(log(n)) time.
int Trendtracker::popularity(string name)
{
    //gets index of name
    int index = search(name);
    //checks if it is valid
    if(index == -1)
        return -1;
    return E[index].pop;
}

// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
//
// Must run in O(1) time.
string Trendtracker::top_trend()
{
    //returns the first item in vector S, unless it is -1
    if(S[0] >= 0)
        return E[S[0]].hashtag;
    return "";
}

// Fills the provided vector with the 3 most-tweeted hashtags,
// in order from most-tweeted to least-tweeted.
//
// If there are fewer than 3 hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(1) time.
void Trendtracker::top_three_trends(vector<string> &T)
{
    //clears the vector T
    T.clear();

    //goes through vector S and adds valid items to T
    for(int i = 0; i < 3; i++)
    {
        if(S[i] >= 0)
        {
            T.push_back(E[S[i]].hashtag);
        }
        else
            break;
    }
}
