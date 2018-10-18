/**
@author Puneet Mangla
CS17BTECH11029
Disjoint Set Union Forrest
**/

#include <bits/stdc++.h> 
using namespace std;

struct Node{ // Node of DSU
	int rank;
	int value;
	struct Node* parent;
};

struct Node* newNode(int value){ // returns newly allocated Node pointer
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->value = value;
	newnode->rank = 1;
	newnode->parent = NULL;
	return newnode;
}

class DSU{
	int N;
	struct Node** pointers; // array of pointers pointing to a node of DSU for random access
public:
	DSU(int N){
		this->N = N;
		pointers = (struct Node**)malloc((N+1)*sizeof(struct Node*));
		for(int i=1;i<N+1;i++)
			pointers[i] = newNode(i);
		
	}

	~DSU(){
		for(int i=0;i<N+1;i++)
			free(pointers[i]);
		free(pointers);
	}

	int representative(int value){
		if(!(value >=1 && value<=N))
			return -1;
		struct Node* temp = pointers[value];
		while(temp->parent!=NULL) // go upward until parent becomes NULL , that node will be the representative
			temp = temp->parent;
		return temp->value;		
	}

	int same_set(int a, int b){
		if(!(a>=1 && a<=N) || !(b>=1 && b<=N))
			return -1;
		if(representative(a)==representative(b)) // check if representative are same or not
			return 1;
		return 0;
	}

	void Union(int a, int b){ // make set with small rank children of set with bigger rank 
		if(!(a>=1 && a<=N) || !(b>=1 && b<=N))
			return;
		struct Node* ra = pointers[representative(a)];
		struct Node* rb  = pointers[representative(b)];
		if(ra->rank < rb->rank)
			ra->parent = rb;
		else if(ra->rank > rb->rank)
			rb->parent = ra;
		else{ // if rank are same make anyone as parent and increase its rank by 1
			rb->parent = ra;
			ra->rank+=1;
		}
	}

	int rank(int a){ // print rank if node is valid
		if(a>=1 && a<=N)
			return pointers[a]->rank;
		return -1;
	}

};

int main(){
	DSU dsu(4);
	string s;
	while(getline(cin,s)){ 
		string r;
		stringstream ss(s);
		ss >> r;
		if (r=="N"){ // elements 
			ss>>r;
			(&dsu)->~DSU();
			new (&dsu) DSU(stoi(r));
		}
		else if(r=="?"){ // same set
			ss>>r;
			string dest;
			ss>>dest;
			cout<<dsu.same_set(stoi(r),stoi(dest))<<endl;	
		}
		else if(r=="R"){ // rank
			ss>>r;
			cout<<dsu.rank(stoi(r))<<endl;	
		}
		else if(r=="U"){ // union
			ss>>r;
			string dest;
			ss>>dest;
			dsu.Union(stoi(r),stoi(dest));	
		}
		else if(r=="S"){ // representative
			string u ;
			ss>>u;
			cout<<dsu.representative(stoi(u))<<endl;
	}
}
	return 0;
}