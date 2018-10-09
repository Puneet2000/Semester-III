#include <bits/stdc++.h> 
using namespace std;
struct Node {
	int value;
	struct Node* next;
};

struct Node* newNode(int value){
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->value = value;
	newnode->next = NULL;
	return newnode;
}

class List {
	struct Node* front;
	struct Node* rear;

	public :
	List(){
		front = rear = NULL;
	}

	void push_back(int value){
		struct Node* newnode = newNode(value);
		if(rear==NULL)
			rear = front = newnode;
		else{
			rear->next = newnode;
			rear = newnode;
		}
	}

	struct Node* pop_front(){
		if(front==NULL)
			return NULL;
		struct Node* temp = front;
		front = front->next;
		if(front==NULL)
			rear = NULL;
		return temp;
	}

	bool find(int value){
		struct Node* temp= front;
		while(temp!=NULL){
			if (temp->value == value)
				return true;
			temp = temp->next;
		}
		return false;
	}

	bool isEmpty(){
		if(front==NULL)
			return true;
		else
			false;
	}

	struct Node* getFront(){
		return front;
	}

};

class Graph{
	int V;
	List *adj;
	int **parent;

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

	bool findEdge(int source , int dest){
		return adj[source].find(dest);
	}

	void makeEdge(int source , int dest){
		adj[source].push_back(dest);
	}

	void bfs(int source){
		bool visited[V+1]={0};
		parent[source][0] = 1;
		List queue;
		queue.push_back(source);
		visited[source] = true;
		while(!queue.isEmpty()){
			struct Node* item = queue.pop_front();
			struct Node* temp = adj[item->value].getFront();
			cout<<item->value<<" ";
			while(temp!=NULL){
				if(!visited[temp->value]){
					visited[temp->value] = true;
					queue.push_back(temp->value);
					parent[source][temp->value] = item->value;					
				}
				temp=temp->next;
			}

		}
		cout<<endl;
	}

	void print_path(int source,int dest){
		if (parent[source][dest]==0)
			return;
		int p = parent[source][dest];
		print_path(source,p);
		cout<<p<<" ";
		return;
	}

	void shortestPath(int source, int dest){
		if(parent[source][0]==0){
			parent[source][0]=1;
			bool visited[V+1]={0};
			List queue;
			queue.push_back(source);
			visited[source] = true;
			while(!queue.isEmpty()){
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
	if(parent[source][dest]==0)
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
	if (r=="N"){ 
		ss>>r;
		g = Graph(stoi(r));
	}
	else if(r=="B"){
		ss>>r;
		g.bfs(stoi(r));	
	}
	else if(r=="?"){
		ss>>r;
		string dest;
		ss>>dest;
		cout<<g.findEdge(stoi(r),stoi(dest))<<endl;	
	}
	else if(r=="P"){
		ss>>r;
		string dest;
		ss>>dest;
		g.shortestPath(stoi(r),stoi(dest));	
	}
	else if(r=="E"){
		string u ;
		ss>>u;
		while(ss>>r)
			g.makeEdge(stoi(u),stoi(r));	
	}
}
    return 0;
}