#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T>
class linkedList
{
class node
	{
		public:
			T data;
			node * next;
	};

	node * front;
	node * back;
    int size;

    public:
	linkedList()
	{
		front = nullptr;
		back = nullptr;
		size = 0;
	}

	~linkedList()
	{
		while(!empty())
			dequeue();
	}

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

	//return true if empty, false otherwise.
	bool empty()
	{
		return front == nullptr;
	}

	void push_back(T x)
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
		size++;
	}

	void print()
	{
		node * current = front;
		while(current != nullptr)
		{
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}

    void split(linkedList<T> & left, linkedList<T> & right)
    {
        node * current = front;

        for(int i = 0; i < size / 2; i++)
        {
            left.push_back(current->data);
            current = current->next;
        }

        for(int i = size / 2; i < size; i++)
        {
            right.push_back(current->data);
            current = current->next;
        }
        //empty the original list
        front = nullptr;
        back = nullptr;
        size = 0;
    }
    void slowSort()
    {
        if(size <= 1)
            return;

        for(int i = 0; i < size - 1; i++)
        {
            node * current = front;
            node * nextNode = front->next;
            for(int j = 0; j < size - i - 1; j++)
            {
                if(current->data > nextNode->data)
                {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;
                }
                current = nextNode;
                nextNode = nextNode->next;
            }
        }
    }

    void mergeSort()
    {
        if(size <= 1)
            return;

        linkedList<T> left;
        linkedList<T> right;
        split(left, right);

        left.mergeSort();
        right.mergeSort();

        //merge left and right back into this list
        front = nullptr;
        back = nullptr;
        size = 0;
        merge(left, right);
    }

    void merge(linkedList<T> & left, linkedList<T> & right)
    {
        node * leftCurrent = left.front;
        node * rightCurrent = right.front;

        while(leftCurrent != nullptr && rightCurrent != nullptr)
        {
            if(leftCurrent->data <= rightCurrent->data)
            {
                push_back(leftCurrent->data);
                leftCurrent = leftCurrent->next;
            }
            else
            {
                push_back(rightCurrent->data);
                rightCurrent = rightCurrent->next;
            }
        }

        while(leftCurrent != nullptr)
        {
            push_back(leftCurrent->data);
            leftCurrent = leftCurrent->next;
        }

        while(rightCurrent != nullptr)
        {
            push_back(rightCurrent->data);
            rightCurrent = rightCurrent->next;
        }

        //empty the left and right lists
        left.front = nullptr;
        left.back = nullptr;
        left.size = 0;

        right.front = nullptr;
        right.back = nullptr;
        right.size = 0;
    }

    void loadFromFile(const std::string & filename)
    {
        ifstream inFile(filename);
        string word;
        if(!inFile.is_open())
            return;
        while(inFile >> word)
        {
            push_back(word);
        }
        inFile.close();
    }

    void writeToFile(const std::string & filename)
    {
        ofstream outFile;
        outFile.open(filename); 
        node * current = front;
        while(current != nullptr)
        {
            outFile << current->data << endl;
            current = current->next;
        }
        outFile.close();
    }

    int getSize()
    {
        return size;
    }
    
    /*
	Loading to B took  81 miliseconds.
	Loading to C took  81 miliseconds.
	bubbleSort took 418545 milliseconds.
	mergeSort took 2714 milliseconds.
	Writng to B took  492 miliseconds.
	Writng to C took  427 miliseconds.
	*/
};