#include <bits/stdc++.h> 
using namespace std;
struct Node { 
	int value;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int colour;
};

struct Node* newNode(int value){
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->value = value;
	newnode->left = newnode->right = newnode->parent = NULL;
	newnode->colour=1;
	return newnode;
}

class RBTree{
	struct Node* root;
	struct Node* SENTINAL;
public:
	RBTree(){
		this->SENTINAL=newNode(-1);
		this->root=SENTINAL;
	}
	~RBTree(){
		deleteBST(root);
		root=NULL;
		free(SENTINAL);
		SENTINAL=NULL;
	}

	void deleteBST(struct Node* root){
		if (root==SENTINAL)
			return;
		deleteBST(root->left);
		deleteBST(root->right);
		free(root);
	}

	void rightRotate(struct Node* found){ // rightRotate 
		struct Node* y = found->left;
		found->left = y->right; // make right subtree of of y as left subtree of found
		if (y->right!=SENTINAL)
			y->right->parent =  found;
		y->parent = found->parent;
		if (found->parent==SENTINAL) // check if root is modified in process or not
			this->root =y;
		else if (found->parent->left == found)
			found->parent->left = y; // assign y as the left subtree of parent of node
		else
			found->parent->right =y;
		y->right = found;
		found->parent =y;
		
	}

	struct Node* leftRotate(struct Node* found){
		struct Node* y = found->right;
		found->right = y->left;
		if (y->left!=SENTINAL)
			y->left->parent =  found;
		y->parent = found->parent;
		if (found->parent==SENTINAL)
			this->root =y;
		else if (found->parent->right == found)
			found->parent->right = y;
		else
			found->parent->left =y;
		y->left = found;
		found->parent =y;
	}

	struct Node* Search(struct Node* root ,int key){  // search a key
		if (root==SENTINAL)
			return root;
		if (root->value == key)  // if found return
			return root;
		if(key<root->value)   // search in left subtree
			return Search(root->left,key);
		if(key>root->value)   // search in right subtree
			return Search(root->right,key);
	}

	struct Node* search(int key){
		return Search(root,key);
	}

	void insert(int value){ 
		struct Node* z = newNode(value);
		struct Node* y = SENTINAL;
		struct Node* x = root;
		while(x!=SENTINAL){
			y=x;
			if(z->value<x->value)
				x = x->left;
			else
				x = x->right;
		}
		z->parent = y;
		if (y==SENTINAL)
			root = z;
		else if (z->value<y->value)
			y->left = z;
		else
			y->right = z;

		z->left = SENTINAL;
		z->right = SENTINAL;
		z->colour = 0;
		insert_fixup(z);
	}

	void insert_fixup(struct Node* z){
		while(z->parent->colour==0){
			if (z->parent == z->parent->parent->left){
				struct Node* y = z->parent->parent->right;
				if(y->colour==0){
					z->parent->colour =1;
					y->colour =1;
					z->parent->parent->colour = 0;
					z = z->parent->parent;
				}
				else {
					if(z==z->parent->right){
						z= z->parent;
						leftRotate(z);
					}
					z->parent->colour=1;
					z->parent->parent->colour = 0;
					rightRotate(z->parent->parent);
				}
			}
			else{
				struct Node* y = z->parent->parent->left;
				if(y->colour==0){
					z->parent->colour =1;
					y->colour =1;
					z->parent->parent->colour = 0;
					z = z->parent->parent;
				}
				else{ 
					if(z==z->parent->left){
						z= z->parent;
						rightRotate(z);
					}
					z->parent->colour=1;
					z->parent->parent->colour = 0;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->colour=1;
	}

	struct Node* minimum(struct Node* root){
		struct Node* temp = root;
		if (root == SENTINAL)
			return root;

		while(temp->left != SENTINAL){ 
			temp = temp->left;
		}
		return temp;
	}

	void transplant(struct Node* u , struct Node* v){
		if (u->parent==SENTINAL)
			root = v;
		else if(u==u->parent->left)
			u->parent->left = v;
		else u->parent->right = v;
		v->parent = u->parent;
	}

	void Delete(struct Node* z){
		struct Node* y = z;
		int orignal_color = y->colour;
		struct Node* x = SENTINAL;
		if (z->left == SENTINAL){
			x = z->right;
			transplant(z,z->right);
		}
		else if(z->right == SENTINAL){
			x = z->left;
			transplant(z,z->left);
		}
		else{
			y = minimum(z->right);
			orignal_color = y->colour;
			x = y->right;
			if(y->parent==z)
				x->parent=y;
			else{
				transplant(y,y->right);
				y->right = z->right;
				y->right->parent =y;
			}
			transplant(z,y);
			y->left = z->left;
			y->left->parent =y;
			y->colour = z->colour;
		}
		if (orignal_color==1)
			delete_fixup(x);
	}

	void delete_fixup(struct Node* x){
		while (x!=root && x->colour ==1){
			if (x==x->parent->left){
				struct Node* w = x->parent->right;
				if(w->colour==0){
					w->colour=1;
					x->parent->colour = 0;
					leftRotate(x->parent);
					w  = x->parent->right;
				}

				if(w->left->colour==1 && w->right->colour==1){
					w->colour=0;
					x= x->parent;
				}
				else if (w->right->colour==1){
					w->left->colour=1;
					w->colour=0;
					rightRotate(w);
					w = x->parent->right;
				}

				w->colour==x->parent->colour;
				x->parent->colour =1;
				w->right->colour =1;
				leftRotate(x->parent);
				x = root;
			}
			else{
				struct Node* w = x->parent->left;
				if(w->colour==0){
					w->colour=1;
					x->parent->colour = 0;
					rightRotate(x->parent);
					w  = x->parent->left;
				}

				if(w->right->colour==1 && w->left->colour==1){
					w->colour=0;
					x= x->parent;
				}
				else if (w->left->colour==1){
					w->right->colour=1;
					w->colour=0;
					leftRotate(w);
					w = x->parent->left;
				}

				w->colour==x->parent->colour;
				x->parent->colour =1;
				w->left->colour =1;
				rightRotate(x->parent);
				x = root;
			}
			x->colour = 1;
		}
		
	}

	void remove(int k){
		struct Node* key = search(k);
		if(key==SENTINAL)
			return;
		Delete(key);
		free(key);
		key=NULL;
	}

	void print_preorder(struct Node* root){ 
		if(root==SENTINAL)
			return;
		cout<<root->value;
		if(root->left != SENTINAL){
			cout<<" ";
			print_preorder(root->left);
		}
		if(root->right !=SENTINAL){	
			cout<<" ";
			print_preorder(root->right);
		}
	}

	void preorder(){
		print_preorder(root);
		cout<<endl;
	}

	string Path(struct Node* root,int key,string bit){  // search a key
		// string bit stores the bit path if exits else -1
		if (root==SENTINAL){
			bit = "-1"; 
			return bit;
		}
		if ((root->value) == key) {
			if(root->colour==1)
				bit+=" B";
			else
				bit+=" R";
			return bit;		
		}
		if(key>=(root->value))  { // search in right subtree
			bit+="1";
			return Path(root->right,key,bit);
		}
		else{ 
			bit+="0";
			return Path(root->left,key,bit);
		}
	}

	string path(int key)
	{
		return Path(root,key,"");
	}

	void Children(struct Node* root,int key){ // childeren of node
		struct Node* found = search(key);
		if(found==SENTINAL)  // no node exists
			cout<<"-1\n";
		else{
			if(found->left!=SENTINAL){
				cout<<found->left->value<<" "; // print left childern
				if (found->left->colour==1)
					cout<<"B ";
				else cout<<"R ";
			}
			else
				cout<<"L B ";
			if(found->right!=SENTINAL){
				cout<<found->right->value<<" "; // print right children
				if (found->right->colour==1)
					cout<<"B\n";
				else cout<<"R\n";
			}
			else
				cout<<"L B\n";
		}
	}

	void children(int key){
		Children(root,key);
	}

};

int main(){
	RBTree t;
	string s;
	while(getline(cin,s)){ // accept input
	string r;
	stringstream ss(s); // split into words
	ss >> r;
	if (r=="N"){ // new BST
		(&t)->~RBTree();
		new (&t) RBTree();
		while(ss >> r)
			t.insert(stoi(r));	// insert in new BST		
	}
	else if(r=="P"){
		t.preorder(); // preorder
	}
	else if(r=="S"){
		ss>>r;
		cout<<t.path(stoi(r))<<endl; // search
	}
	else if(r=="+"){
		ss>>r;
		t.insert(stoi(r)); 
	}
	else if(r=="-"){
		ss>>r;
		t.remove(stoi(r)); // delete
	}	
	else if(r=="C"){
		ss>>r;
		t.children(stoi(r)); // Children
	}
}
	return 0;
}