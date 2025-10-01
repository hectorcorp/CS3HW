

class stackLL
{
private:
	class node
	{
	public:
		//put what you need in here
		int data;
		node * next;
	};

	node * top;

public:

	//O(1)
	stackLL()
	{
		top = nullptr;
	}
	
	//Decontructor
	~stackLL()
	{
		while( ! empty() )
			pop();
	}

	//O(1)
	//return true if empty, false if not
	bool empty()
	{
		return top == nullptr;
	}

	//O(1)
	//add item to top of stack
	void push(int x)
	{
		node * n = new node();
		n->data = x;
		n->next = top;
		top = n;
	}

	//O(1)
	//remove and return top item from stack
	int pop()
	{
		if(!empty())
		{
			int num = top->data;
			node * temp = top;
			top = top->next;
			delete temp;
			return num;
		}

		return -1;
	}

	//O(i)
	//add item x to stack, but insert it
	//right after the current ith item from the top
	//(and before the i+1 item).
	void insertAt(int x, int i)
	{
		if(i < 0) return;

		if(i == 0)
		{
			push(x);
			return;
		}

		node * curr = top;
		for(int j = 0; j < i - 1; j++)
		{
			if(curr == nullptr) return;
			curr = curr->next;
		}

		if(curr == nullptr) return;

		node * n = new node();
		n->data = x;
		n->next = curr->next;
		curr->next = n;
	}

};