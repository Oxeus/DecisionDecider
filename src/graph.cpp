//*****************************************************************************************
//Program by: Adam LaFleur
//Date: March 15, 2019
//Class: CS163 - Data Structures
//Program: #5
//File: graph.cpp
//Purpose: The purpose of this program is to keep track of decisions that a user wants to make
//and show which future decisions that can be made next.
//graph.cpp has the purpose of containing the algorithms to add a vertex to the graph, add an edge
//to the graph, display all adjacent vertices to each vertex, display all vertices, and display
//all paths that can be taken from each vertex without repeadtedly visiting a vertex (depth first).
//*****************************************************************************************
#include "graph.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;



//Constructor used to initialize the vertex array in memory and sets data at each array location to NULL
graph::graph()
{
	list_size = 10;
	adjacency_list = new vertex[list_size];
	for(int i = 0; i < list_size; ++i)
	{
		adjacency_list[i].decision = nullptr;
		adjacency_list[i].head = nullptr;
		adjacency_list[i].visit = 0;
	}
}



//This function recursively deletes the edge list sent in from the deconstructor. Takes in a pass by 
//reference node head. 
int graph::delete_list(node *& head)
{
	if(!head) return 0;
	delete_list(head->next);
	if(head)
	{
		head->adjacent = nullptr;
		head->weight = 0;
		delete head;
		head = nullptr;
	}
	return 1;
}



//Deconstructor used to deallocate memory, calls delete_list function to delete the edge list at each
//location. 
graph::~graph()
{
	for(int i = 0; i < list_size; ++i)
	{
		if(adjacency_list[i].decision)
		{
			delete [] adjacency_list[i].decision;
		}
		delete_list(adjacency_list[i].head);
		adjacency_list[i].head = nullptr;
		adjacency_list[i].visit = 0;
	}
	delete [] adjacency_list;
	adjacency_list = nullptr;
}



//Function to add a decision to the vertex list, checks the array for next available space. If the array is
//full then there is no insertion, hence a failure. Takes in a char value as an argument.
int graph::add_vertex(char * decision)
{
	if(!adjacency_list) return 0;
	for(int i = 0; i < list_size; ++i)
	{
		if(!adjacency_list[i].decision)
		{
			adjacency_list[i].decision = new char[strlen(decision) + 1];
			strcpy(adjacency_list[i].decision, decision);
			return 1;
		}
	}
	return 0;
}



//Function used to locate a decision in the vertex list, used to prevent multiple repeations of code. If data is
//found return location value if not then -1 is returned for failure. Takes in a char value as a argument and returns
//an int.
int graph::find_location(char * decision)
{
	if(!adjacency_list) return -1;
	for(int i = 0; i < list_size; ++i)
	{
		if(adjacency_list[i].decision)
		{
			if(strcmp(adjacency_list[i].decision, decision) == 0)
			{
				return i;
			}
		}
	}
	return -1;
}



//Function used to add an edge between two vertices, uses the find_location function for each vertex and finds their
//location, will only add an edge if the values returned from find_location for each location is not -1 and not
//equal to each other. Takes in a two char values and an int value as arguments.
int graph::add_edge(char * choice_one, char * choice_two, int weight)
{
	int result = 0;
	if(!adjacency_list) return result;
	node * curr = nullptr;
	int vertex_one = find_location(choice_one), vertex_two = find_location(choice_two);
	if((vertex_one != -1 && vertex_two != -1) && vertex_one != vertex_two)
	{
		curr = new node;
		curr->adjacent = adjacency_list + vertex_two;
		curr->weight = weight;
		curr->next = adjacency_list[vertex_one].head;
		adjacency_list[vertex_one].head = curr;
		result = 1;
	}
	return result;
}



//Function that prints all vertices and the adjacent vertices for each.
int graph::print_adjacent()
{
	int result = 0;
	if(!adjacency_list) return result;
	node * curr = nullptr;
	cout << "list of All Decisions and Their Adjacents: " << endl;
	cout << "----------------------------------------------" << endl;
	for(int i = 0; i < list_size; ++i)
	{
		if(adjacency_list[i].decision)
		{
			cout << "Decision: " << adjacency_list[i].decision << endl;
			curr = adjacency_list[i].head;
			while(curr)
			{
				cout << endl;
				cout << "     Decision: " << curr->adjacent->decision << endl;
				cout << "     Weight: " << curr->weight << endl;
				curr = curr->next;
			}
			result = 1;
			cout << endl;
		}
	}
	return result;
}



//Function that prints all vertices
int graph::print_all()
{
	int result = 0;
	if(!adjacency_list) return result;
	cout << "List of All Decisions: " << endl;
	cout << "----------------------------------------------" << endl;
	for(int i = 0; i < list_size; ++i)
	{
		if(adjacency_list[i].decision)
		{
			cout << "Decision: " << adjacency_list[i].decision << endl << endl;
			result = 1;
		}
	}
	return result;
}



//Recursive function to Print out all paths for an enterted vertex through the graph. If node
//has already been visited then stop and return. Takes a vertex pointer, int values for indent
//and level as arguments.
int graph::print_depth_first(vertex * path, int indent, int level)
{
	path->visit = 1;
	cout << setw(indent) << "(" << level << ") Decision: " << path->decision << endl << endl;
	node * curr = path->head;
	while(curr)
	{
		if(curr->adjacent->visit != 1)
		{
			print_depth_first(curr->adjacent, indent + 5, level + 1);
		}
		curr = curr->next;
	}
	return 1;
}



//Wrapper function for recursive print_depth_first function, makes a call to recursive function
//for each vertex array locations edge list. 
int graph::print_depth_first()
{
	int result = 0;
	if(!adjacency_list) return result;
	cout << "List of All Decisions and Their Paths: " << endl;
	cout << "----------------------------------------------" << endl;
	for(int j = 0; j < list_size; ++j)
	{
		if((adjacency_list + j)->decision)
		{
			print_depth_first(adjacency_list + j, 0, 1);
			for(int i = 0; i < list_size; ++i)
			{
				(adjacency_list + i)->visit = 0;
			}
			result = 1;
		}
	}
	return result;
}
