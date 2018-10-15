#include <bits/stdc++.h> 
using namespace std;
struct Node { // Node for Queue and Adjacency list
	int value;
	struct Node* next;
};

struct Node* newNode(int value){ // returns newly allocated Node pointer
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->value = value;
	newnode->next = NULL;
	return newnode;
}

class List { // List that can behave as both adjacency list and queue
	struct Node* front;
	struct Node* rear;

	public :
	List(){
		front = rear = NULL;
	}


	void push_back(int value){ // pushing in the list
		struct Node* newnode = newNode(value);
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

	bool find(int value){ // search for an element
		struct Node* temp= front;
		while(temp!=NULL){
			if (temp->value == value)
				return true;
			temp = temp->next;
		}
		return false;
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

	void clear(){ // clear function to delete the list object
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
		this->parent = new int* [V+1];
		for(int i=0;i<V+1;i++){
			this->parent[i] = new int[V+1];
			memset(parent[i],false,(V+1)*sizeof(int));

		}
	}
	Graph(){}

	~Graph(){
		for(int i=0;i<V+1;i++){ // free lists
			adj[i].clear();
		}
		for(int i=0;i<V+1;i++){ // free parent matrix
			free(parent[i]);
		}
		free(parent); // free parent
		free(adj); // free adj
	}

	bool findEdge(int source , int dest){ // check if (u,v) belongs to E
		return adj[source].find(dest);
	}

	void makeEdge(int source , int dest){ // add (u,v) to E
		adj[source].push_back(dest);
	}

	void clearAdj(int source){ // clear the the list corresponding to a vertex
		for(int i=0;i<V+1;i++){
			for(int j=0;j<V+1;j++)
				parent[i][j]=0;
		}
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

			free(item);

		}
		cout<<endl;
		queue.clear();
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
				while(temp!=NULL){
					if(!visited[temp->value]){
						visited[temp->value] = true;
						parent[source][temp->value] = item->value;
						queue.push_back(temp->value);					
					}
					temp=temp->next;
				}

			}
			queue.clear();
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
	else if(r=="B"){ // do bfs
		ss>>r;
		g.bfs(stoi(r));	
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
		string u ;
		ss>>u;
		g.clearAdj(stoi(u));
		while(ss>>r)
			g.makeEdge(stoi(u),stoi(r));	
	}
}
    return 0;
}