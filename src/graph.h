//*****************************************************************************************
//Program by: Adam LaFleur
//Date: March 15, 2019
//Class: CS163 - Data Structures
//Program: #5
//File: graph.h
//Purpose: The purpose of this program is to keep track of decisions that a user wants to make
//and show which future decisions that can be made next.
//graph.h has the purpose of defining the ADT structure and defining the entry structure
//*****************************************************************************************



class graph
{
	public:
		graph();
		~graph();
		int add_vertex(char * decision);
		int add_edge(char * choice_one, char * choice_two, int weight);
		int print_adjacent(void);
		int print_all(void);
		int print_depth_first(void);

	private:
		struct vertex;
		struct node;

		struct vertex {
			char * decision;
			struct node * head;
			int visit;
		};

		struct node {
			struct vertex * adjacent;
			int weight;
			node * next;
		};

		vertex * adjacency_list;
		int list_size;

		int find_location(char * decision);
		int print_depth_first(vertex * list, int indent, int level);
		int delete_list(node *& head);
};
