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

struct heapNode {
	int vertex;
	int weight;
}

class MinHeap{
	struct heapNode *weights;
	int V;
	int size;
public:

	MinHeap(int V){
		this->V = V;
		this->size =0;
		this->weights = (struct heapNode*)malloc(V*sizeof(heapNode));
	}

	int parent(int i){
		return (i-1)/2;
	}

	int left_child(int i){
		return 2*i+1;
	}

	int right_child(int i){
		return 2*i+2;
	}

	void insert(int vertex , int weight){
		struct heapNode node;
		node.vertex = vertex;
		node.weight = weight;
		weights[size] = node;
		int index = size;
		while(index!=0){
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
		struct heapNode min = weights[0];
		size--;
		weights[0] = weights[size];
		Heapify(0);
		return min;
	}

	void decreaseKey(int vertex , int weight){
		for (int i=0;i<size;i++){
			if(weights[i].vertex==vertex){
				weights[i].weight = weight;
			}
		}
	}



};

class List { // List that can behave as both adjacency list and queue
	struct Node* front;
	struct Node* rear;

	public :
	List(){
		front = rear = NULL;
	}

	~List(){
		clear();
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
	int **parent; // parents corresponding to bfs from a source vertex to avoid extra computation

public:
	Graph(int V){
		this->V = V;
		this->adj = (List *)malloc((V+1)*sizeof(List));
		parent = new int* [V+1];
		for(int i=0;i<V+1;i++){
			parent[i] = new int[V+1];
			memset(parent[i],false,(V+1)*sizeof(int));
		}
	}
	Graph(){}

	bool findEdge(int source , int dest){ // check if (u,v) belongs to E
		return adj[source].find(dest);
	}

	void makeEdge(int source , int dest , int weight){ // add (u,v) to E
		adj[source].push_back(dest,weight);
	}

	void clearAdj(int source){
		adj[source].clear();
	}

	void bfs(int source){ // breath first traversal for graphs
		bool visited[V+1]={0}; // visited arrat
		parent[source][0] = 1;
		List queue;
		queue.push_back(source);
		visited[source] = true;
		while(!queue.isEmpty()){
			struct Node* item = queue.pop_front(); // pop element
			struct Node* temp = adj[item->value].getFront();
			cout<<item->value<<" ";
			while(temp!=NULL){ // add not visited neighbours of poped element
				if(!visited[temp->value]){
					visited[temp->value] = true; // mark visited true
					queue.push_back(temp->value);
					parent[source][temp->value] = item->value;	// storing parent vertices				
				}
				temp=temp->next;
			}

		}
		cout<<endl;
	}

	void print_path(int source,int dest){ // recursively print the path given the parent array for all vertices
		if (parent[source][dest]==0) // return if we reached the source vertex
			return;
		int p = parent[source][dest];
		print_path(source,p); // print path from source vertex to parent of destination vertex
		cout<<p<<" "; // print destination vertex
		return;
	}

	void shortestPath(int source, int dest){
		if(parent[source][0]==0){ // if bfs is not done yet then do and store parent vertices 
			parent[source][0]=1;
			bool visited[V+1]={0};
			List queue;
			queue.push_back(source);
			visited[source] = true;
			while(!queue.isEmpty()){ // same as bfs
				struct Node* item = queue.pop_front();
				struct Node* temp = adj[item->value].getFront();
				if(item->value == dest)
					break;
				while(temp!=NULL){
					if(!visited[temp->value]){
						visited[temp->value] = true;
						parent[source][temp->value] = item->value;
						queue.push_back(temp->value);					
					}
					temp=temp->next;
				}

			}
	}
	if(parent[source][dest]==0) // if no parent for destination vertex is there then return -1
		cout<<"-1\n";
	else{
		print_path(source,dest);
		cout<<dest<<endl;
	}
}

};

int main(){
	Graph g = Graph();
	string s;
	while(getline(cin,s)){ 
	string r;
	stringstream ss(s);
	ss >> r;
	if (r=="N"){ // Number of vertices
		ss>>r;
		g = Graph(stoi(r)); // re-initialize graph
	}
	else if(r=="?"){ // check if (u,v) belongs to E
		ss>>r;
		string dest;
		ss>>dest;
		cout<<g.findEdge(stoi(r),stoi(dest))<<endl;	
	}
	else if(r=="P"){ // print shortest path from u to v
		ss>>r;
		string dest;
		ss>>dest;
		g.shortestPath(stoi(r),stoi(dest));	
	}
	else if(r=="E"){ // add Edges in E
		string u ,w;
		ss>>u;
		g.clearAdj(stoi(u));
		while(ss>>r){
			ss>>w;
			g.makeEdge(stoi(u),stoi(r),stoi(w));	
		}
	}
}
    return 0;
}