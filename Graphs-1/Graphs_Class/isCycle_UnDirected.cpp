#include<bits/stdc++.h>

using namespace std;

class LinkedList{

public:

	char data;
	LinkedList *next;
	LinkedList *head;
	LinkedList *tail;
};

void addEdge(LinkedList *helper_array, char u, char v)
{
	LinkedList *node = new LinkedList;
	node->data = v;
	node->next = NULL;

	if(helper_array[u - 'a'].head == NULL)
	{
		helper_array[u - 'a'].head = node;
		helper_array[u - 'a'].tail = node;
	}
	

	else
	{
		helper_array[u -'a'].tail->next = node;	
		helper_array[u -'a'].tail = node;
	}

	LinkedList *node2 = new LinkedList;
	node2->data = u;
	node2->next = NULL;

	if(helper_array[v- 'a'].head == NULL)
	{
		helper_array[v - 'a'].head = node2;
		helper_array[v - 'a'].tail = node2;
	}
	

	else
	{
		helper_array[v -'a'].tail->next = node2;	
		helper_array[v -'a'].tail = node2;
	}

}


void printGraph(LinkedList *helper_array, int V)
{

	for(int i=0;i<V;i++)
	{
		cout << "Adjaceny List for vertex " << char(i + 'a') << " is " << endl;
		LinkedList *temp = helper_array[i].head;

		while(temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}

		cout << endl << endl;
	}
}


int tt = 0;
bool isCyclic = false;

void DFS_Traversal(LinkedList *helper_array, int *colour, int *starting_time,
				   int *finishing_time, char *predeccesor, int V, 
				   int **edges_colour, char source_node)
{
	tt++;
	starting_time[source_node - 'a'] = tt;
	colour[source_node - 'a'] = 1; //Grey
	cout << source_node << " ";


	LinkedList *temp = helper_array[source_node - 'a'].head;

	while(temp != NULL)
	{
		if( colour[ (temp->data) - 'a' ]  == 0) //white colour
		{
			edges_colour[source_node - 'a'][temp->data - 'a'] = 'T'; //tree edge
			predeccesor[(temp->data) - 'a'] = source_node;
			DFS_Traversal(helper_array,colour,starting_time,finishing_time, 
			predeccesor, V, edges_colour,temp->data );
		}

		else if( colour[ (temp->data) - 'a' ]  == 1) //grey colour
		{	
			if(predeccesor[source_node - 'a' ] != temp->data )
				isCyclic = true;
		}  


		temp = temp->next;
	}	

	colour[source_node - 'a'] = 2; //black
	tt++;
	finishing_time[source_node - 'a' ] = tt;
}




void DFS(LinkedList* helper_array, int V, int **edges_colour)
{
	int *colour = new int[V]; // 0 for white, 1 for grey and 2 for black
	int *starting_time = new int [V]; //discovery time
	int *finishing_time = new int [V]; //finishing time
	char *predeccesor =  new char[V];
	

	for(int i=0;i<V;i++)
	{
		colour[i] = 0; //initialize all colours as white //Not Visited yet
		starting_time[i] = -1;
		finishing_time[i] = -1;
		predeccesor[i] = '\0';

	}
	for(int i=0;i<V;i++)
		if(colour[i] == 0)
	DFS_Traversal(helper_array,colour,starting_time,finishing_time,
		predeccesor,V,edges_colour,'a' + i);

}


int main()
{
	int V = 5;
	LinkedList *helper_array = new LinkedList[V];

	for(int i=0;i<V;i++)
	{
		helper_array[i].next = NULL;
		helper_array[i].head = NULL;
		helper_array[i].tail = NULL;
	}

    addEdge(helper_array, 'a', 'b');
    addEdge(helper_array, 'b', 'c');
    addEdge(helper_array, 'a', 'c');
    addEdge(helper_array, 'a', 'e');
    addEdge(helper_array, 'd', 'e');

    int **edges_colour = new int*[V];

	for(int i=0;i<V;i++)
	{
		edges_colour[i] = new int[V];
		for(int j=0;j<V;j++)
			edges_colour[i][j] = 0;
	}

    //printGraph(helper_array,V);
   	DFS(helper_array,V,edges_colour);
   	cout << endl;

   	if(isCyclic == true)
   		cout << "There is a Cycle in the Graph" << endl;
   	else
   		cout << "There is no Cycle in the Graph" << endl;



	return 0 ; 

}

