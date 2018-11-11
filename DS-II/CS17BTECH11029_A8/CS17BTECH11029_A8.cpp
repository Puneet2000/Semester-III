/**
@author Puneet Mangla
CS17BTECH11029
Red-Black Tree
**/
#include <bits/stdc++.h> 
using namespace std;
struct Node { // Node for RBTree
	int value;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int colour;
};

struct Node* newNode(int value){ //  new RBTree Node allocation
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->value = value;
	newnode->left = newnode->right = newnode->parent = NULL;
	newnode->colour=1;
	return newnode;
}

class RBTree{ // CLass RBTree
	struct Node* root; // root of RBTree
	struct Node* SENTINAL; // SENTINAL Node
public:
	RBTree(){
		this->SENTINAL=newNode(-1); // allocating SENTINAL Node
		this->root=SENTINAL; // initialise root as SENTINAL
	}
	~RBTree(){
		deleteBST(root); // delete BST function from previous assignment
		root=NULL; // root = NULL
		free(SENTINAL); // free SENTINAL Node
		SENTINAL=NULL;
	}

	void deleteBST(struct Node* root){ // delete RBTree using Post order traversal
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

	struct Node* leftRotate(struct Node* found){ // same as rightRotate
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
		while(x!=SENTINAL){ // iterative insert 
			y=x;
			if(z->value<x->value)
				x = x->left; // go in left subtree
			else
				x = x->right; // go in right subtree
		}
		z->parent = y; // insert the node
		if (y==SENTINAL)
			root = z;
		else if (z->value<y->value)
			y->left = z;
		else
			y->right = z;

		z->left = SENTINAL; // assign child as sentinal
		z->right = SENTINAL;
		z->colour = 0; // assign red to node
		insert_fixup(z); // call fixup
	}

	void insert_fixup(struct Node* z){
		while(z->parent->colour==0){ // do until node is RED
			if (z->parent == z->parent->parent->left){
				struct Node* y = z->parent->parent->right;
				if(y->colour==0){ //  z’s uncle y is red
					z->parent->colour =1;
					y->colour =1;
					z->parent->parent->colour = 0;
					z = z->parent->parent;
				}
				else {
					if(z==z->parent->right){ //  z’s uncle y is black and  z is a right child
						z= z->parent;
						leftRotate(z);
					}
					z->parent->colour=1; //  z’s uncle y is black and  z is a left child
					z->parent->parent->colour = 0;
					rightRotate(z->parent->parent);
				}
			}
			else{ // same as previous if statement
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
		root->colour=1; // assign root as BLACK
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

	struct Node* maximum(struct Node* root){ // go to left subtree until SENTINAL is achieved
		struct Node* temp = root;
		if (root == SENTINAL)
			return root;

		while(temp->right != SENTINAL){ 
			temp = temp->right;
		}
		return temp;
	}

	void transplant(struct Node* u , struct Node* v){ // 
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
		if (z->left == SENTINAL){ // only right child
			x = z->right;
			transplant(z,z->right);
		}
		else if(z->right == SENTINAL){ // only left child
			x = z->left;
			transplant(z,z->left);
		}
		else{ // both children
			y = maximum(z->left); // find predecessor
			orignal_color = y->colour;
			x = y->left;
			if(y->parent==z)
				x->parent=y;
			else{
				transplant(y,y->left);
				y->left = z->left;
				y->left->parent =y;
			}
			transplant(z,y); // replace by predecessor
			y->right = z->right;
			y->right->parent =y;
			y->colour = z->colour;
		}
		if (orignal_color==1)
			delete_fixup(x); // call delete fixup
	}

	void delete_fixup(struct Node* x){
		while (x!=root && x->colour ==1){
			if (x==x->parent->left){
				struct Node* w = x->parent->right;
				if(w->colour==0){ // x’s sibling w is red
					w->colour=1;
					x->parent->colour = 0;
					leftRotate(x->parent);
					w  = x->parent->right;
				}

				if(w->left->colour==1 && w->right->colour==1){ // x’s sibling w is black, and both of w’s children are black
					w->colour=0;
					x= x->parent;
				}
				else {
					if (w->right->colour==1){ // x’s sibling w is black, w’s left child is red, and w’s right child is black
						w->left->colour=1;
						w->colour=0;
						rightRotate(w);
						w = x->parent->right;
					}

					w->colour==x->parent->colour; // x’s sibling w is black, and w’s right child is red
					x->parent->colour =1;
					w->right->colour =1;
					leftRotate(x->parent);
					x = root;
				}
			}
			else{ // same as previous if
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
				else {
					if (w->left->colour==1){
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
			}
			
		}
		x->colour = 1;
		
	}

	void remove(int k){ // call Delete if key exists
		struct Node* key = search(k);
		if(key==SENTINAL)
			return;
		Delete(key);
		free(key);
		key=NULL;
	}

	void print_preorder(struct Node* root){ // Preorder Traversal VLR
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
				bit+=" B"; // if colour is BLACK
			else
				bit+=" R"; // if colur id RED
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
				cout<<"L B "; // SENTINAL
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

	struct Node* Successor(struct Node* keynode){
		if(keynode->right !=SENTINAL){ // find minimum in right subtree
			return minimum(keynode->right);
		}

		struct Node* temp = keynode;
		while(temp->parent != SENTINAL){ // use parent pointers to find succesor
			if (temp->parent->left == temp)
				break;
			temp = temp->parent;
		}
		return temp->parent;
	}

	struct Node* successor(int key){
		struct Node* temp = root;
		struct Node* p = SENTINAL; 
		while(temp!=SENTINAL && temp->value!=key){ 
			p = temp;
			if(key<temp->value)
				temp= temp->left;
			else
				temp = temp->right;
		}

		if(temp!=SENTINAL && temp->value==key)
			return Successor(temp); // if key exists
		else if (p->value > key)
			return p;
		else
			return Successor(p); // else call successor of parent from which SENTINAL is achieved
	}


};

int main(){
	RBTree t;
	string s;
	while(getline(cin,s)){ // accept input
	string r;
	stringstream ss(s); // split into words
	ss >> r;
	if (r=="N"){ // new RBTree
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
		t.insert(stoi(r));  // insert
	}
	else if(r=="-"){
		ss>>r;
		t.remove(stoi(r)); // delete
	}	
	else if(r=="C"){
		ss>>r;
		t.children(stoi(r)); // Children
	}
	else if(r==">"){ // successor
		ss>>r;
		struct Node* succ = t.successor(stoi(r));
		if(succ==NULL)
			cout<<"-1\n";
		else
			cout<<succ->value<<endl;

	}
}
	return 0;
}