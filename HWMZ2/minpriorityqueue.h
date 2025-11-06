
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of strings in the MinPriorityQueue.
	//
	// Assume the operations of map are O(1) time 
	// (they are average case, but not worst-case).

	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size()
		{
			return H.size();
		}	

		// Pushes a new element x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time. 
		void push(T x, int p)
		{
			if(I.count(x)) return;
			int index = H.size();
			H.push_back({x, p});
			I[x] = index;
			while(index > 0)
			{
				if(H[index].second < H[(index - 1) / 2].second)
				{
					//Swap Values
					swap(H[index], H[(index - 1) / 2]);
					I[H[index].first] = index;
					I[H[(index - 1) / 2].first] = (index - 1) / 2;

					//Update index
					index = (index - 1) / 2;
				}
				else break;
			}
		}

		// Returns the string at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front()
		{
			if(H.empty()) return T();
			return H[0].first;
		}

		// Removes the string at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{
			// empty case
			if(H.empty()) return;

			//Swap values
			swap(H[0], H[H.size() - 1]);
			I[H[0].first] = 0;
			I[H[H.size() - 1].first] = H.size() - 1;

			//Remove value
			I.erase(H[H.size() - 1].first);
			H.pop_back();

			if(H.empty()) return;

			int index = 0;
			int p = H[0].second;

			while(true)
			{
				int left = -1;
				int right = -1;
				int smallest = index;

				if(2*index + 1 < H.size() && H[smallest].second > H[2*index + 1].second)
				{
					smallest = 2*index + 1;
				}
				if(2*index + 2 < H.size() && H[smallest].second > H[2*index + 2].second)
				{
					smallest = 2*index + 2;
				}


				if(smallest != index)
				{
					swap(H[index], H[smallest]);
					I[H[index].first] = index;
					I[H[smallest].first] = smallest;
					index = smallest;
				}
				else break;
			}
		}

		// If s is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			int index = I[x];
			if(new_p >= H[I[x]].second) return;
			H[I[x]].second = new_p;
			
			while(index > 0)
			{
				if(H[index].second < H[(index - 1) / 2].second)
				{
					swap(H[index], H[(index - 1) / 2]);
					I[H[index].first] = index;
					I[H[(index - 1) / 2].first] = (index - 1) / 2;
					index = (index - 1) / 2;
				}
				else break;
			}
		}

	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		unordered_map<T, int> I; // Maps elements to indices in H.
		vector< pair<T, int> > H; // The array containing the heap.
};

#endif 

