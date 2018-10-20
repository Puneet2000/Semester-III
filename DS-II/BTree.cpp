#include<iostream>
using namespace std;

struct Node{
	int n_keys;
	int *keys;
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
		root = newNode(t);
	}

	struct Node* split_child(struct Node* x , int i){
		//cout<<"split\n";

		struct Node* z = newNode(t);
		struct Node* y = x->children[i];
		z->isleaf = y->isleaf;
		z->n_keys = t-1;

		for(int j=1;j<=t-1;j++)
			z->keys[j] = y->keys[j+t];

		if (!y->isleaf){
			for(int j=1;j<=t-1;j++)
				z->children[j] = y->children[j+t];
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

	void insert(int key){
		//cout<<"inserintg "<<key<<endl;
		struct Node* r = root;
		if (r->n_keys == 2*t-1){
			struct Node* s = newNode(t);
			root = s;
			s->isleaf = false;
			s->children[1] = r;
			s = split_child(s,1);
			s = insert_non_full(s,key);
		}
		else
			root = insert_non_full(root,key);

	}

	struct Node* insert_non_full(struct Node* x, int key){
		//cout<<"insert non full "<<key<<endl;
		int i = x->n_keys;
		//cout<<i<<endl;
		if (x->isleaf){
			//cout<<"leaf\n";
			while(i>=1 && key < x->keys[i]){
				x->keys[i+1] = x->keys[i];
				i = i-1;
			}

			x->keys[i+1] =key;
			x->n_keys+=1;
			return x;
		}
		else{
			//cout<<"not leaf\n";
			while(i>=1 && key < x->keys[i])
				i =i-1;
			i = i+1;
			if(x->children[i]->n_keys == 2*t-1){
				x = split_child(x,i);
				if (key<x->keys[i])
					i=i+1;	
			}
			x->children[i]= insert_non_full(x->children[i],key);
			return x;
		}

	}

	void traverse(){
		Traverse(root);
		cout<<endl;
	}

	void Traverse(struct Node* root){
		int i;
		for(i=1;i<=root->n_keys;i++){
			if(root->isleaf == false)
				Traverse(root->children[i]);
			cout<<" "<<root->keys[i];
		}

		if (root->isleaf==false)
			Traverse(root->children[i]);

	}
};

int main(){
	BTree t(3);
	t.insert(10);
	t.insert(19);
	t.insert(5);
	t.insert(6);
	t.insert(12);
	t.insert(30);
	t.insert(7);
	t.insert(17);
	t.traverse();
	return 0;
}