#include<iostream>
using namespace std;

struct Node{
	int n_keys;
	int keys*;
	bool isleaf;
	struct Node** children;
	struct Node* parent;
};

struct Node* newNode(int t){
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->keys = (int*)malloc((2*t)*sizeof(int));
	node->children = (struct Node**)malloc((2*t+1)*sizeof(struct Node*));
	node->n_keys = 0;
	node->parent = NULL;
	node->isleaf = true;
	return node;
}

class BTree{
	struct Node* root;
	int t;
public:
	BTree(int t){
		this->t = t;
		root
	}

	bool search(struct Node* root = this->root , int key){
		int i=1;
		while((i<=root->n_keys) && (key>root->keys[i]))
			i++;
		if (i<=root->n_keys && key==root->keys[i])
			return true;
		else if (root->isleaf)
			return false;
		else
			return search(root->children[i],key);
	}

	struct Node* split_child(struct Node* x , int i){
		struct Node* z = newNode(t);
		struct Node* y = x->children[i];
		z->isleaf = y->isleaf;
		z->n_keys = t-1;
		for(int j=1;j<=t-1;j++)
			z->keys[i] = y->keys[i+t];
		if (!y->isleaf){
			for(int j=1;j<=t-1;j++)
				z->children[i] = y->children[i+t];
		}

		y->n_keys = t-1;
		for(int j= x->n_keys+1;j>=i+1;j--)
			x->children[j+1] = x->children[j];
		x->children[i+1] =z;

		for(int j= x->n_keys;j>=i;j--)
			x->keys[j+1] = x->keys[j];
		x->keys[i] =y->keys[t];
		x->n_keys+=1;
		return x;
	}

	struct Node* insert(struct Node* root =this->root,int key){
		struct Node* r = root;
		if (r->n_keys == 2*t-1){
			struct Node* s = newNode(t);
			root = s;
			s->isleaf = false;
			s->children[1] = r;
			split_child(s,1);
			root = insert_non_full(root,key);
		}
		else
			insert_non_full(root,key);
	}
}