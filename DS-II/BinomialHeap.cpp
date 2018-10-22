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
public:
	BHeap(){
		head=NULL;
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
		cout<<h->value<<endl;
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
/**
	struct Node* extractMin(){
		struct Node* prev=NULL;
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
	}**/

	void decreaseKey(struct Node* x,int k){
		if(k>x->value)
			cout<<"can't decrease\n";
		else{
			x->value =k;
			struct Node* y = x;
			struct Node* z = x->parent;
			while(z!=NULL && y->value < z->value){
				swap(y,z);
				y=z;
				z = y->parent;
			}
		}
	}

	void Delete(struct Node* x){
		decreaseKey(x,INT_MIN);
		struct Node* m = extractMin();
	}

	void swap(struct Node* y, struct Node* z){
		struct Node temp;
		temp.value = z->value;
		temp.child = z->child;
		temp.sibling = z->sibling;
		temp.parent = z->parent;
		temp.degree = z->degree;
		z->child = y->child;
		z->parent = y->parent;
		z->sibling = y->sibling;
		y->child = temp.child;
		y->parent = temp.parent;
		y->sibling=temp.sibling;
	}
	
};

int main(){
	BHeap t;
	t.insert(10);
	t.insert(20);
	t.insert(30);
	t.insert(2);
	t.insert(4);
	struct Node* min = t.Minimum();
	cout<<min->value<<endl;
}