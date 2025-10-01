
template <class T>
class priorityQueueLL
{
private:
	class node
	{
	public:
		//put what you need here..
		T data;
		T priority;
		node * next;
	};

	//add what you wish here
	node * head;


public:

	//O(1)
	priorityQueueLL()
	{
		head = nullptr;
	}

	~priorityQueueLL()
	{
		while(!empty())
			extractMin();
	}

	//O(1)
	//return true if empty, false if not
	bool empty()
	{
		return head == nullptr;
	}

	//O(n)
	//add item
	void insert(T x)
	{
		node * n = new node();
		n->data = x;
		n->priority = x; //assume T has comparison operators
		n->next = nullptr;

		if(empty())
		{
			head = n;
		}
		else if(n->priority < head->priority) //insert at front
		{
			n->next = head;
			head = n;
		}
		else //find correct spot to insert
		{
			node * current = head;
			while(current->next != nullptr && current->next->priority <= n->priority)
			{
				current = current->next;
			}
			n->next = current->next;
			current->next = n;
		}
	}

	//O(1)
	//remove and return smallest item
	T extractMin()
	{
		if(empty())
			return T();

		node * temp = head;
		head = head->next;
		T data = temp->data;
		delete temp;
		return data;
	}
};