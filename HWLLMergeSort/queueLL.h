template <class T>
class queueLL
{
private:
	//put what you need here...
	class node
	{
		public:
			T data;
			node * next;
	};

	node * front;
	node * back;

public:
	//O(1)
	queueLL()
	{
		front = nullptr;
		back = nullptr;
	}

	~queueLL()
	{
		while(!empty())
			dequeue();
	}

	//O(1)
	//add item to back of queue
	void enqueue(T x)
	{
		node * n = new node();
		n->data = x;
		n->next = nullptr;
		if(empty())
		{
			front = n;
			back = n;
		}
		else
		{
			back->next = n;
			back = n;
		}
	}

	//O(1)
	//remove and return first item from queue
	T dequeue()
	{
		if(!empty())
		{
			T num = front->data;
			node * temp = front;
			front = front->next;
			if(front == nullptr)
				back = nullptr;
			delete temp;
			return num;
		}

		return T();
	}

	//O(1)
	//return true if empty, false otherwise.
	bool empty()
	{
		return front == nullptr;
	}

	//O(n)
	//For the final part of the test program, template this class
	//and add a decimate method.
	void decimate()
	{
		if(empty() || front->next == nullptr)
			return;

		node * current = front;
		int count = 2;
		while(current != nullptr && current->next != nullptr)
		{
			if(count % 10 == 0)
			{
				node * temp = current->next;
				current->next = current->next->next;
				if(temp == back)
					back = current;
				delete temp;
			}
			else
			{
				current = current->next;
			}
			count++;
		}
	}
};