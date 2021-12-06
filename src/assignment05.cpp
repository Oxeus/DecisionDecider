//*****************************************************************************************
//Program by: Adam LaFleur
//Date: March 15, 2019
//Class: CS163 - Data Structures
//Program: #5
//File: assignment05.cpp
//Purpose: The purpose of this program is to keep track of decisions that a user wants to make
//and show which future decisions that can be made next.
//assignment05.cpp has the purpose of controlling the program and inputting data to be sent to the ADT. 
//*****************************************************************************************
#include <iostream>
#include <iomanip>
#include <cstring>
#include "graph.h"

using namespace std;

void status(int num);



// The purpose of main is the initialize and run the program, main has a menu that gives the user an
// option of what they want to do, the menu repeats until the user specifices when to stop.
// The user is given options such as adding a new decision, connecting two decisions 
// together, displaying all adjacent decisions for each decision, displaying
// all the decision, displaying each decision showing all possible paths from that decision, and 
// quitting the program.
int main()
{
	graph list;
	char input[100], input_two[100];
	int choice = 0, num = 0, weight; //choice used to control which menu option selected, num is used to record ADT return values
	bool control = true; //Controls whether the program loops or not

	cout << "----------------------------------------------" << endl;
        cout << "************** Program #5: Graph *************" << endl;
        cout << "----------------------------------------------" << endl;
	while(control)
	{
		num = 0;
		cout << "Please choose an option: " << endl;
		cout << "01. Add a new decision to the graph." << endl;
		cout << "02. Insert an edge along with its weight. " << endl;
		cout << "03. Display Adjacent. " << endl;
		cout << "04. Display All." << endl;
		cout << "05. Display Depth First. " << endl;
		cout << "06. Quit client program." << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Please enter a choice: ";
		cin >> choice;
		cin.ignore();
		cout << endl;
		switch(choice)
		{
			case 1:
				cout << "Please enter a decision: ";
				cin.getline(input, 100);
				num = list.add_vertex(input);
				status(num);
				break;
			case 2:
				cout << "Please enter the decisions to link: " << endl;
				cout << "From: ";
				cin.getline(input, 100);
				cout << "To: ";
				cin.getline(input_two, 100);
				cout << "Please enter the weight for the edge: ";
				cin >> weight;
				num = list.add_edge(input, input_two, weight);
				status(num);
				break;
			case 3:
				num = list.print_adjacent();
				status(num);	
				break;
			case 4:
				num = list.print_all();
				status(num);
				break;
			case 5:
				num = list.print_depth_first();
				status(num);
				break;
			case 6:
				control = false;
				status(1);
				break;
			default:
				break;
		}
	}
	return 0;
}



// Failure will be printed out, if 1 or greater is supplied then Success will be printed out.
void status(int num)
{
	cout << endl;
	cout << "Status: ";
	if(num == 0)
	{
		cout << "Failure! / Empty List!" << endl;
	}
	if(num > 0)
	{
		cout << "Success!" << endl;
	}
	cout << endl;
}
