//Implement a (singly or doubly) linked list that supports
//the following methods.
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "linkedList.h"

using namespace std;

int main()
{
	linkedList<double> A;

	//Implement a push_back method that adds a given item to the back of the list.
	//Must run in O(1) time.
	A.push_back(450);
	A.push_back(320);
	A.push_back(750);
	A.push_back(510);
	A.push_back(720);
	A.push_back(230);
	A.push_back(290);
	A.push_back(240);
	A.push_back(320);
	A.push_back(820);
	A.push_back(530);
	A.push_back(210);

	//Implement a simple print method to test your list.
	A.print(); //450 320 750..... 530 210

	linkedList<double> left;
	linkedList<double> right;

	//Split the contents of list A evenly into the two given (initially empty) lists.
	//If the number of items in the list is odd, put the extra item in the first list.
	//Must run in O(n) time, where n is the total number of items in the list.
	A.split(left, right);

	A.print(); //(empty)
	left.print(); //450 320 750 510 720 230
	right.print(); //290 240 320 820 530 210

	//Implement a sorting routine for your list
	//You may implement any elementary sorting algorithm.
	left.slowSort();
	right.slowSort();

	left.print(); //230 320 450 510 720 750
	right.print(); //210 240 290 320 530 820

	//Implement a method that takes 2 sorted lists and merges them
	//into your (initially empty) list to create one sorted list.
	//Must run in O(n) time, where n is the total number of items in the two given lists.
	A.merge(left, right);

	left.print(); //(empty)
	right.print(); //(empty)
	A.print(); //210 230 240 290 320 320 450 510 530 720 750 820


	//Add a methods to load your list from a file, and write your list to a file
	linkedList<string> B;
	linkedList<string> C;

	//loadFromFile should open the file of the specified name and
	//enter each item (words in the novel "Moby Dick" in this case)
	//in the linked list.

	auto start = chrono::high_resolution_clock::now();
	B.loadFromFile("whale.txt");
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "Loading to B took  " << duration.count() << " miliseconds." << endl;

	start = chrono::high_resolution_clock::now();
	C.loadFromFile("whale.txt");
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "Loading to C took  " << duration.count() << " miliseconds." << endl;


	//This line will sort all the words in the novel Moby Dick.
	//You are encouraged to write some testing code to ensure that
	//both lists are identical after sorting.

	start = chrono::high_resolution_clock::now();
	B.slowSort();
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "bubbleSort took " << duration.count() << " milliseconds." << endl;


	start = chrono::high_resolution_clock::now();
	C.mergeSort();
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "mergeSort took " << duration.count() << " milliseconds." << endl;

	//writeToFile should write each item in the linked list to the provided output file.
	//In this example, it should write all the words from Moby Dick to the provided output file in sorted order.
	//Double check to see if the two files below are properly sorted.

	start = chrono::high_resolution_clock::now();
	B.writeToFile("slowSortedWhale.txt");
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "Writng to B took  " << duration.count() << " miliseconds." << endl;


	start = chrono::high_resolution_clock::now();
	C.writeToFile("mergeSortedWhale.txt");
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "Writng to C took  " << duration.count() << " miliseconds." << endl;


	//For your running time report, test each
	//sort one at a time by timing the entire process
	//of reading from the file, running the sorting algorithm,
	//and writing the result to the ouptut file.

	/*
	Loading to B took  81 miliseconds.
	Loading to C took  81 miliseconds.
	bubbleSort took 418545 milliseconds.
	mergeSort took 2714 milliseconds.
	Writng to B took  492 miliseconds.
	Writng to C took  427 miliseconds.
	*/
	cout << "Done" << endl;
	return 0;
}