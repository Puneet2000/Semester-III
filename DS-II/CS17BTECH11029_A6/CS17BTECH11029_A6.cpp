/**
@author Puneet Mangla
CS17BTECH11029
Dijsktra Algorithm
**/

#include <bits/stdc++.h> 
using namespace std;
struct Node { // Node for Queue and Adjacency list
	int value;
	int weight;
	struct Node* next;
};

struct Node* newNode(int value,int weight){ // returns newly allocated Node pointer
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->value = value;
	newnode->weight = weight;
	newnode->next = NULL;
	return newnode;
}

struct heapNode { // Node to store vertex and corresponding value in heap
	int vertex;
	int weight;
};

class MinHeap{ // Min-Heap
	struct heapNode *weights; // array of nodes
	int V;
	int size; // current size of heap
	int *map; // map to map vertex to corresponding index in min-heap array
public:

	MinHeap(int V){ // initialisation
		this->V = V;
		this->size =0;
		this->weights = (struct heapNode*)malloc(V*sizeof(heapNode));
		this->map = (int*)malloc((V+1)*sizeof(int));
		memset (this->map, -1, sizeof (int) * (V+1));
	}

	~MinHeap(){
		free(map);
		free(weights);
	}

	int parent(int i){ // parent 0 based indexing
		return (i-1)/2;
	}

	int left_child(int i){ // left child
		return 2*i+1;
	}

	int right_child(int i){ // right child
		return 2*i+2;
	}

	void swap(int i,int j){ // swap two nodes in min-heap
		struct heapNode node;
		node = weights[i];
		map[weights[i].vertex] = j; // change their corresponding maps
		map[weights[j].vertex] = i;
		weights[i] = weights[j]; // change the correspinding nodes
		weights[j] = node;	
	}

	void insert(int vertex , int weight){
		struct heapNode node;
		node.vertex = vertex;
		node.weight = weight;
		weights[size] = node;
		map[node.vertex] = size;
		int index = size;
		while(index!=0){ // correcting the destroyed heap
			if(weights[parent(index)].weight > weights[index].weight){
				swap(index, parent(index));
				index  = parent(index);
			}
			else
				break;
		}
		size++;

	}

	struct heapNode extractMin(){
		if(size==1){
			size--;
			return weights[0];
		}
		struct heapNode min = weights[0]; // extract and decreae size
		size--;
		map[min.vertex]=-1;
		weights[0] = weights[size]; // swap last and first node
		map[weights[size].vertex] = 0; 
		Heapify(0); // Heapify call
		return min;
	}

	void Heapify(int i){
		int left = left_child(i) , right = right_child(i);
		int min = i;
		if (left<size && weights[left].weight <  weights[i].weight)
			min = left;
		if (right<size && weights[right].weight < weights[min].weight)
			min = right;
		if (min!=i){
			swap(i,min);
			Heapify(min);
		}

	}

	void decreaseKey(int vertex , int weight){
		int index = map[vertex];
		weights[index].weight = weight;
		while (index != 0 && weights[parent(index)].weight > weights[index].weight) 
	    { 
	       swap(index , parent(index)); 
	       index = parent(index); 
	    }  
	}

	bool isEmpty(){
		if(size==0)
			return true;
		else
			return false;
	}


	bool inHeap(int vertex){
		if(map[vertex]==-1)
			return false;
		return true;
	}
};

class List { // List that can behave as both adjacency list and queue
	struct Node* front;
	struct Node* rear;

	public :
	List(){
		front = rear = NULL;
	}

	void push_back(int value , int weight){ // pushing in the list
		struct Node* newnode = newNode(value , weight);
		if(rear==NULL)
			rear = front = newnode;
		else{
			rear->next = newnode;
			rear = newnode;
		}
	}

	struct Node* pop_front(){ // pop front
		if(front==NULL)
			return NULL;
		struct Node* temp = front;
		front = front->next;
		if(front==NULL)
			rear = NULL;
		return temp;
	}

	int find(int value){ // search for an element
		struct Node* temp= front;
		while(temp!=NULL){
			if (temp->value == value)
				return temp->weight;
			temp = temp->next;
		}
		return -1;
	}

	bool isEmpty(){ // if list is empty or not
		if(front==NULL)
			return true;
		else
			false;
	}

	struct Node* getFront(){ // return pointer to front
		return front;
	}

	void clear(){
		struct Node* temp = front;
		while(front != NULL){
			temp = front;
			front = front->next;
			free(temp);
		}
		front = rear = NULL;
	}

};

class Graph{ // Graph Class
	int V; // number of vertices
	List *adj; // adjacency lists

public:
	Graph(int V){
		this->V = V;
		this->adj = (List *)malloc((V+1)*sizeof(List));
	}

	~Graph(){
		for(int i=0;i<V+1;i++){ // free lists
			adj[i].clear();
		}
		free(adj); // free adj
	}

	int findEdge(int source , int dest){ // check if (u,v) belongs to E
		return adj[source].find(dest);
	}

	void makeEdge(int source , int dest , int weight){ // add (u,v) to E
		//cout<<"edge made\n";
		adj[source].push_back(dest,weight);
	}

	void clearAdj(int source){
		adj[source].clear();
	}

	void dijsktra(int source){
		MinHeap heap(V);
		int distance[V+1];
		for(int i=1;i<V+1;i++){
			if(i==source){
				heap.insert(i,0);
				distance[i]=0;
			}
			else{
				distance[i]=INT_MAX;
				heap.insert(i,INT_MAX);
			}
		}
		
		while(!heap.isEmpty()){
			struct heapNode min = heap.extractMin();
			int vertex = min.vertex;
			if(min.weight != INT_MAX)
				cout<<vertex<<" "<<min.weight<<endl;
			else
				cout<<vertex<<" "<<-1<<endl;
			struct Node* temp = adj[vertex].getFront();
			while(temp!=NULL){
				if(heap.inHeap(temp->value) && distance[vertex]+temp->weight < distance[temp->value]){
					distance[temp->value] = distance[vertex]+temp->weight;
					heap.decreaseKey(temp->value,distance[temp->value]);
				}
				temp= temp->next;

			}
		}

	}

	void print_path(int source,int dest , int parent[]){ // recursively print the path given the parent array for all vertices
		if (parent[dest]==0) // return if we reached the source vertex
			return;
		int p = parent[dest];
		print_path(source,p,parent); // print path from source vertex to parent of destination vertex
		cout<<p<<" "; // print destination vertex
		return;
	}

	void shortest_path(int source, int dest){
		MinHeap heap(V);
		int distance[V+1];
		int parent[V+1]={0};
		for(int i=1;i<V+1;i++){
			if(i==source){
				heap.insert(i,0);
				distance[i]=0;
			}
			else{
				distance[i]=INT_MAX;
				heap.insert(i,INT_MAX);
			}
		}
		
		while(!heap.isEmpty()){
			struct heapNode min = heap.extractMin();
			int vertex = min.vertex;
			struct Node* temp = adj[vertex].getFront();
			while(temp!=NULL){
				if(heap.inHeap(temp->value) && distance[vertex]+temp->weight < distance[temp->value]){
					distance[temp->value] = distance[vertex]+temp->weight;
					heap.decreaseKey(temp->value,distance[temp->value]);
					parent[temp->value]=vertex;
				}
				temp= temp->next;

			}
		}
		if(parent[dest]==0 && source!=dest)
			cout<<"-1\n";
		else{
			cout<<distance[dest]<<" ";
			print_path(source,dest,parent);
			cout<<dest<<endl;
		}

	}
};

int main(){

	Graph g = Graph(4);
	string s;
	while(getline(cin,s)){ 
		string r;
		stringstream ss(s);
	ss >> r;
	if (r=="N"){ // Number of vertices
		ss>>r;
		(&g)->~Graph();
		new (&g) Graph(stoi(r));
	}
	else if(r=="?"){ // check if (u,v) belongs to E
		ss>>r;
		string dest;
		ss>>dest;
		cout<<g.findEdge(stoi(r),stoi(dest))<<endl;	
	}
	else if(r=="D"){ // dijstjra algorithm
		ss>>r;
		g.dijsktra(stoi(r));	
	}
	else if(r=="P"){ // print shortest path from u to v
		ss>>r;
		string dest;
		ss>>dest;
		g.shortest_path(stoi(r),stoi(dest));	
	}
	else if(r=="E"){ // add Edges in E
		string u ;
		ss>>u;
		g.clearAdj(stoi(u));
		while(ss>>r){
			string w;
			ss>>w;
			g.makeEdge(stoi(u),stoi(r),stoi(w));	
		}
	}
}
    return 0;
}