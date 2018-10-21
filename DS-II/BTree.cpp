#include<iostream>
using namespace std;

struct Node{
	int n_keys;
	int *keys;
	bool isleaf;
	struct Node** children;
};

struct Id{
	struct Node* node;
	int index;
};

struct Node* newNode(int t){
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->keys = (int*)malloc((2*t)*sizeof(int));
	node->children = (struct Node**)malloc((2*t+1)*sizeof(struct Node*));
	node->n_keys = 0;
	node->isleaf = true;
	return node;
}

void deleteNode(struct Node* node){
	free(node->keys);
	free(node->children);
	free(node);
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

	int findPred(struct Node* node , int index){
		struct Node* temp = node->children[index];
		while(!temp->isleaf)
			temp = temp->children[temp->n_keys+1];
		return temp->keys[temp->n_keys];
	}

	int findSucc(struct Node* node , int index){
		struct Node* temp = node->children[index+1];
		while(!temp->isleaf)
			temp = temp->children[1];
		return temp->keys[1];
	}

	bool Search(struct Node* x , int k){
		int i=1;
		while(i<=x->n_keys && k>x->keys[i])
			i++;
		if (i<=x->n_keys && k== x->keys[i])
			return true;
		else if(x->isleaf)
			return false;
		else 
			return Search(x->children[i],k);
	}

	bool search(int k){
		return Search(root,k);
	}

	void Delete1(struct Node* node , int index){
		int k = node->keys[index];
		if(node->isleaf){
			for(int i= index+1;i<=node->n_keys;i++)
				node->keys[i-1]= node->keys[i];
			node->n_keys--;
		}
		else{
			if(node->children[index]->n_keys>=t){
				int x = findPred(node,index);
				node->keys[index] = x;
				deleteKey(node->children[index],x);
				
			}
			else if(node->children[index+1]->n_keys>=t){
				int succ = findSucc(node);
				node->keys[index] = x;
				deleteKey(node->children[index+1],x);
			}
			else{
				merge(node,index);
				deleteKey(node,k);
			}
		}
	}

	void merge(struct Node* node, int index){
		struct Node* left = node->children[index];
		struct Node* right =  node->children[index+1];
		left->keys[t] = node->keys[index];
		for(int i=1;i<=right->n_keys;i++)
			left->keys[t+i] =  right->keys[i];
		if(!left->isleaf){
			for(int i=1;i<=right->n_keys+1;i++)
				left->children[i+t] = right->children[i];
		}

		for(int i = index+1;i<=node->n_keys;i++)
			node->keys[i-1] = node->keys[i];
		for(int i=index+2;i<=node->n_keys+1;i++)
			node->children[i-1]= node->children[i];
		left->n_keys+= right->n_keys+1;
		node->n_keys--;
		delete(right);
		return;
	}

	void deleteKey(struct Node* node,int k){
		int index=1;
		while(index<=node->n_keys && node->keys[index]<k)
			index = index+1;
		if(index <=node->n_keys && node->keys[index]==k)
			Delete1(node,index);
		else{
			if(node->isleaf){
				cout<<"key doesn't exists\n";
				return;
			}
		}

	}

};

int main(){
	BTree t(3);
	t.insert(1); 
    t.insert(3); 
    t.insert(7); 
    t.insert(10); 
    t.insert(11); 
    t.insert(13); 
    t.insert(14); 
    t.insert(15); 
    t.insert(18); 
    t.insert(16); 
    t.insert(19); 
    t.insert(24); 
    t.insert(25); 
    t.insert(26); 
    t.insert(21); 
    t.insert(4); 
    t.insert(5); 
    t.insert(20); 
    t.insert(22); 
    t.insert(2); 
    t.insert(17); 
    t.insert(12); 
    t.insert(6); 
	struct Id found = t.search(7);
	cout<<(found.node)->keys[found.index]<<endl;
	return 0;
}