
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
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
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
			cout << "hi";
			return H.size();
		}	

		//return index of parent of index i
		int parent(int i)
		{
			return (i - 1) / 2;
		}

		//bubble up item at index location
		//unitl no more violation
		void bubbleUp(int index)
		{
			int i = index;

			while (i > 0 && H[i].second < H[parent(i)].second)  //there is a parent viloation at i)
			{
				swap(H[i], H[parent(i)]);
				I[H[i].first] = i;
				I[H[parent(i)].first] = parent(i);
				i = parent(i);
			}
		}

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
			if(I.count(x)) return;
			H.push_back({x, p});
			int i = size() - 1;
			I[x] = i;
			bubbleUp(i);
		}

		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front()
		{
			if(H.empty()) return T();
			return H[0].first;
		}

		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{
			if(H.empty()) return;

			T top = H[0].first;
			swap(H[0], H[H.size() - 1]);
			I[H[0].first] = 0;
			I[H[H.size() - 1].first] = H.size() - 1;

			I.erase(top);
			H.pop_back();

			if(H.empty()) return;
			int i = 0;

			while(true)
			{
				int left = -1;
				int right = -1;
				int smallest = i;

				if(2*i + 1 < H.size() && H[smallest].second > H[2*i + 1].second)
				{
					smallest = 2*i + 1;
				}
				if(2*i + 2 < H.size() && H[smallest].second > H[2*i + 2].second)
				{
					smallest = 2*i + 2;
				}


				if(smallest != i)
				{
					swap(H[i], H[smallest]);
					I[H[i].first] = i;
					I[H[smallest].first] = smallest;
					i = smallest;
				}
				else break;
			}
		}

		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			int i = I[x];
			if(new_p >= H[i].second) return;
			H[i].second = new_p;
			bubbleUp(i);
		}

	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.
};

#endif 

