#include<bits/stdc++.h> 
using namespace std;

struct Node{
	int value;
	struct Node* parent;
	struct Node* child;
	struct Node* sibling;
	int degree;
};

struct Node* newNode(int x){
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->value = x;
	newnode->parent=NULL;
	newnode->child=NULL;
	newnode->sibling=NULL;
	newnode->degree=0;
	return newnode;
}

class BHeap{
	struct Node* head;
	map <int,struct Node*> mymap;
public:
	BHeap(){
		head=NULL;
	}
	~BHeap(){
		map<int, struct Node*>::iterator it;
		for ( it = mymap.begin(); it != mymap.end(); it++ )
			free(it->second);
		mymap.clear();
	}

	struct Node* Minimum(){
		struct Node* y=NULL;
		struct Node* temp = head;
		int min = INT_MAX;
		while(temp!=NULL){
			if(temp->value<min){
				min = temp->value;
				y = temp;
			}
			temp = temp->sibling;
		}
		return y;
	}

	void link(struct Node* y, struct Node* z){
		y->parent = z;
		y->sibling = z->child;
		z->child = y;
		z->degree++;
	}

	struct Node* Union(struct Node* h1 , struct Node* h2){
		struct Node* h=NULL;
		h = merge(h1,h2);
		if(h==NULL)
			return h;
		struct Node* prev = NULL;
		struct Node* x = h;
		struct Node* next = x->sibling;
		while(next!=NULL){
			if((x->degree != next->degree) || (next->sibling!=NULL && (next->sibling->degree==x->degree))){
				prev = x;
				x = next;
			}
			else if(x->value<=next->value){
				x->sibling = next->sibling;
				link(next,x);
			}
			else{
				if(prev==NULL)
					h = next;
				else
					prev->sibling = next;
				link(x,next);
				x = next;
			}
			next = x->sibling;
		}
		return h;
	}

	void insert(int v){
		struct Node* x = newNode(v);
		struct Node* h = x;
		this->head = Union(this->head,h);
		mymap.insert(pair<int,struct Node*>(v,x));
	}

	struct Node* merge(struct Node* h1 , struct Node* h2){
		struct Node* h = NULL;
		struct Node* temp1 = h1;
		struct Node* temp2 = h2;
		struct Node* x =NULL;
		while(temp1!=NULL || temp2!=NULL){
				if(((temp1!=NULL && temp2!=NULL)&&(temp1->degree<=temp2->degree))||(temp1!=NULL && temp2==NULL)){
					if(h==NULL){
						h=temp1;
						x=h;
					}
					else {
						x->sibling = temp1;
						x = x->sibling;
					}
					temp1 = temp1->sibling;
				}
				else if(((temp1!=NULL && temp2!=NULL)&&(temp2->degree<=temp1->degree))||(temp2!=NULL && temp1==NULL)){
					if(h==NULL){
						h=temp2;
						x=h;
					}
					else{
						x->sibling = temp2;
						x = x->sibling;
					}
					temp2 = temp2->sibling;
				}
			}
		return h;
	}
	void extractMin(){
		struct Node* prev=NULL;
		struct Node* p = NULL;
		struct Node* y=NULL;
		struct Node* temp = head;
		int min = INT_MAX;
		while(temp!=NULL){
			if(temp->value<min){
				min = temp->value;
				y = temp;
				prev =p;
			}
			p = temp;
			temp = temp->sibling;
		}
		if (y==NULL)
			return;
		if(prev==NULL)
			head = y->sibling;
		else
			prev->sibling = y->sibling;
		struct Node* h = y->child;
		temp = h;
		while(temp!=NULL){
			temp->parent =NULL;
			temp = temp->sibling;
		}
		this->head = Union(this->head,h);
		mymap.erase(mymap.find(y->value));
		free(y);
	}

	void remove(int v){
		decKey(v,INT_MIN);
		extractMin();
	}

	void decKey(int v , int k){
		struct Node* x = mymap.find(v)->second;
		if(k>x->value)
			cout<<"can't decrease\n";
		else{
			x->value =k;
			mymap.erase(mymap.find(v));
			mymap.insert(pair<int,struct Node*>(k,x));
			struct Node* y = x;
			struct Node* z = x->parent;
			while(z!=NULL && y->value < z->value){
				mymap.find(y->value)->second = z;
				mymap.find(z->value)->second = y;
				int m = y->value;
				y->value = z->value;
				z->value = m;
				y=z;
				z = y->parent;
			}
		}

		
	}
	
};

int main(){
	BHeap t;
	t.insert(10);
	t.insert(20);
	t.insert(30);
	t.insert(2);
	t.insert(4);
	t.insert(-1);
	t.insert(100);
	t.insert(-2);
	t.insert(0);
	t.decKey(0,-4);
	struct Node* min = t.Minimum();
	cout<<min->value;
	return 0;
}