/**
@Author Puneet Mangla
CS17BTECH11029
BST for integers
**/
#include <bits/stdc++.h> 
using namespace std;
struct Node{   // structure to store value,left,right,parent
	int value;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
};

struct Node* newNode(int value){  // returns a new node of type struct Node*
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->value = value;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	return newnode;
}

struct Node* insert(struct Node* root,int value,struct Node* parent){  // insert in BST
	if(root==NULL){
		struct Node* newnode = newNode(value);
		newnode->parent = parent;          // create new node
		return newnode;
	}

	if(value<root->value){   // go to left tree
		root->left = insert(root->left,value,root);
	}
	else{        // go to right tree
		root->right = insert(root->right,value,root);
	}

	return root;
}


void preorder(struct Node* root){  // preorder traversal VLR
	if(root==NULL)
		return;
	cout<<root->value;
	if(root->left != NULL){
		cout<<" ";
		preorder(root->left);
	}
	if(root->right !=NULL){	
		cout<<" ";
		preorder(root->right);
	}
}

struct Node* search(struct Node* root,int key){  // search a key
	if (root==NULL)
		return root;
	if (root->value == key)  // if found return
		return root;
	if(key<root->value)   // search in left subtree
		return search(root->left,key);
	if(key>root->value)   // search in right subtree
		return search(root->right,key);
}


struct Node* findMin(struct Node* root){
	struct Node* temp = root;
	if (root == NULL)
		return root;

	while(temp->left != NULL){ // go left until left of node is not NULL
		temp = temp->left;
	}
	return temp;
}

struct Node* deleteNode(struct Node* root,int key){
	struct Node* keynode = search(root,key);
	if (keynode == NULL)
	{
	}
	else if(keynode->left ==NULL && keynode->right ==NULL){ // no children delete Node
		if(keynode->parent==NULL){
			free(root);
			root = NULL;
		}
		else {
		if(keynode == keynode->parent->left)
			keynode->parent->left = NULL;
		else
			keynode->parent->right = NULL;
		free(keynode);
	}
	}
	else if (keynode->right !=NULL && keynode->left ==NULL){ // one children merge
		if (keynode->parent == NULL){
			keynode->right->parent = NULL;
			free(root);
			root = keynode->right;
		}
		else{
		if(keynode == keynode->parent->left)
			keynode->parent->left = keynode->right;
		else
			keynode->parent->right = keynode->right;
		keynode->right->parent = keynode->parent;
		free(keynode);
	}
	}
	else if (keynode->left !=NULL && keynode->right ==NULL){ // one children merge
		if (keynode->parent == NULL){
			keynode->left->parent = NULL;
			free(root);
			root = keynode->left;
		}
		else {
		if(keynode == keynode->parent->left)
			keynode->parent->left = keynode->left;
		else
			keynode->parent->right = keynode->left;
		keynode->left->parent = keynode->parent;
		free(keynode);
	}
	}
	else {
	struct Node* min = findMin(keynode->right); // find minimum using succesor
	int val = min->value; 
	root =deleteNode(root,val);
	keynode->value = val;
	}
	return root;
}

struct Node* successor(struct Node* root,int key){
	struct Node* keynode = search(root,key);
	if (keynode == NULL)  // insert node , find succesor and then delete
	{
		insert(root,key,NULL);
		struct Node* succ = successor(root,key);
		root = deleteNode(root,key);
		return succ;
	}

	if(keynode->right !=NULL){ // find minimum in right subtree
		return findMin(keynode->right);
	}

	struct Node* temp = keynode;
	while(temp->parent != NULL){ // use parent pointers to find succesor
		if (temp->parent->left == temp)
			break;
		temp = temp->parent;
	}
	return temp->parent;
}

void deleteBST(struct Node* root){ // using postorder to delete BST
	if (root==NULL)
		return;
	deleteBST(root->left);
	deleteBST(root->right);
	free(root);
}

string path(struct Node* root,int key,string bit){  // search a key
	// string bit stores the bit path if exits else -1
	if (root==NULL){
		bit = "-1"; 
		return bit;
	}
	if ((root->value) == key)  // if found return
		return bit;		
	if(key>=(root->value))  { // search in right subtree
		bit+="1";
		return path(root->right,key,bit);
	}
	else{ 
		bit+="0";
		return path(root->left,key,bit);
	}
}

int main(){
	struct Node* root = NULL;
	string s;
	while(getline(cin,s)){ // accept input
	string r;
	stringstream ss(s); // split into words
	ss >> r;
	if (r=="N"){ // new BST
		deleteBST(root); // delete previous BST
		root = NULL;
		while(ss >> r)
			root = insert(root,stoi(r),NULL);	// insert in new BST		
	}
	else if(r=="P"){
		preorder(root); // preorder
		cout<<endl;
	}
	else if(r=="S"){
		ss>>r;
		cout<<path(root,stoi(r),"")<<endl; // search
	}
	else if(r=="+"){
		ss>>r;
		root = insert(root,stoi(r),NULL); 
	}
	else if(r=="-"){
		ss>>r;
		root = deleteNode(root,stoi(r)); // search
	}
	else if(r==">"){
		ss>>r;
		struct Node* succ = successor(root,stoi(r));
		if(succ==NULL)
			cout<<"-1\n";
		else
			cout<<succ->value<<endl;
	}	
}
    return 0;
}