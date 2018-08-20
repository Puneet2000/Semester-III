#include <iostream>
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

void inorder(struct Node* root){  // inorder traversal LVR
	if (root==NULL)
		return;
	inorder(root->left);
	cout<<root->value<<" ";	
	inorder(root->right);
}

void preorder(struct Node* root){  // preorder traversal VLR
	if (root==NULL)
		return;
	cout<<root->value<<" ";
	preorder(root->left);
	preorder(root->right);
}
void postorder(struct Node* root){  // postorder traversal LRV
	if (root==NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	cout<<root->value<<" ";
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

	while(temp->left != NULL){
		temp = temp->left;
	}
	return temp;
}

struct Node* findMax(struct Node* root){
	struct Node* temp = root;
	if (root == NULL)
		return root;

	while(temp->right != NULL){
		temp = temp->right;
	}
	return temp;
}

struct Node* successor(struct Node* root,int key){
	struct Node* keynode = search(root,key);
	if (keynode == NULL)
	{
		cout<<"Element not found in BST\n";
		return keynode;
	}

	if(keynode->right !=NULL){
		return findMin(keynode->right);
	}

	struct Node* temp = keynode;
	while(temp->parent != NULL){
		if (temp->parent->left == temp)
			break;
		temp = temp->parent;
	}
	return temp->parent;
}

struct Node* predessor(struct Node* root,int key){
	struct Node* keynode = search(root,key);
	if (keynode == NULL)
	{
		cout<<"Element not found in BST\n";
		return keynode;
	}

	if(keynode->left !=NULL){
		return findMax(keynode->left);
	}

	struct Node* temp = keynode;
	while(temp->parent != NULL){
		if (temp->parent->right == temp)
			break;
		temp = temp->parent;
	}
	return temp->parent;
}

struct Node* getParent(struct Node* root,int key){
	struct Node* keynode = search(root,key);
	if (keynode == NULL)
	{
		cout<<"Element not found in BST\n";
		return keynode;
	}
	return keynode->parent;
}

struct Node* deleteNode(struct Node* root,int key){
	struct Node* keynode = search(root,key);
	if (keynode == NULL)
	{
		cout<<"Element not found in BST\n";
	}
	else if(keynode->left ==NULL && keynode->right ==NULL){
		if(keynode == keynode->parent->left)
			keynode->parent->left = NULL;
		else
			keynode->parent->right = NULL;

		free(keynode);
	}
	else if (keynode->right !=NULL && keynode->left ==NULL){
		if(keynode == keynode->parent->left)
			keynode->parent->left = keynode->right;
		else
			keynode->parent->right = keynode->right;
		keynode->right->parent = keynode->parent;
		free(keynode);
	}
	else if (keynode->left !=NULL && keynode->right ==NULL){
		if(keynode == keynode->parent->left)
			keynode->parent->left = keynode->left;
		else
			keynode->parent->right = keynode->left;
		keynode->right->parent = keynode->parent;
		free(keynode);
	}
	else {
	struct Node* min = findMin(keynode->right);
	int val = min->value; 
	root =deleteNode(root,val);
	keynode->value = val;
	}
	return root;
}

int main(){
	struct Node* root = NULL;
	root = insert(root, 50,NULL);
    insert(root, 30,NULL);
    insert(root, 20,NULL);
    insert(root, 40,NULL);
    insert(root, 70,NULL);
    insert(root, 60,NULL);
    insert(root, 80,NULL);
    return 0;
}