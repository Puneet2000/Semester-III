/**
@Author Puneet Mangla
CS17BTECH11029
BST for arbitary large non-negative numbers
**/

#include<iostream>
#include<sstream>
using namespace std;
struct Node { 
	// structure to store digit , previous and next node pointer
	int digit;
	struct Node* next;
	struct Node* prev;
};
// Class to handle large numbers
class BigNum{
	public:
	struct Node* head;     // declaring head

	BigNum(string s){
		this->head = NULL; // constructor initialising head = NULL
		long long int j =0;
		for (j=0;s[j]=='0';j++);
		for(long long int i=j;i<s.length();i++){ // making linked list
			int d = s[i]-48;
			this->head = insertNode(this->head,d);
		}
	}
	BigNum(){
		this->head = NULL; // constructor initialising head = NULL
	}
	BigNum(const BigNum &num) {head = num.head;} // copy constructor for class object
	~BigNum(){} // destructor
	
	static struct Node* insertNode(struct Node* head ,int digit){   // insert node function

	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));  // allocate memory
		newnode->digit = digit;
		newnode->prev = NULL;         
		newnode->next = NULL;
		if(head == NULL)             
			head = newnode;
		else{
			newnode->next = head;
			head->prev = newnode;
		}
			return newnode;       // head always store LSB
	}

	static int comparelength(struct Node* head1 , struct Node* head2){
		struct Node* temp1=head1;
		struct Node*  temp2=head2;
		while(temp1!=NULL && temp2!=NULL){
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		if(temp1==NULL && temp2!=NULL)
			return 2;
		else if(temp1!=NULL && temp2==NULL)
			return 1;
		else
			return 0;
	}
	bool operator >= (BigNum const &obj) { // overloading >= operator
		int l1 = comparelength(head,obj.head); // calculate length of linked lists
		if(l1==1)  // if first is greater return true
			return 1;
		else if(l1==2)
			return 0;
		else{           // if they are equal check if there is any MSD of first number greater than other
           struct Node* temp=head;
           struct Node* temp1 = obj.head;
           while(temp->next!=NULL)
           {
           	temp=temp->next;
           	temp1=temp1->next;
           }
           // temp and temp1 stores last node of linked list i.e MSD
           int flag=0;
           
           while(temp!=NULL){
           		if(temp->digit>temp1->digit)  // if digit of first number is greater tha other break and return 1
           		{
           			flag=1;
           			break;
           		}
           		else if(temp->digit < temp1->digit)  // if digit of first Num is less than second , break and return 0;
           		{
           			flag =0;
           			break;
           		}
           		else // Do nothing when they are equal keep flag = 1
           			flag=1;
           		temp = temp->prev;
           		temp1 = temp1->prev;
           }
           if(flag)
				return 1;
			else
				return 0;
		}    
	}
	bool operator == (BigNum const &obj) { // overloading == operator
		int l1 = comparelength(head,obj.head); // calculate length of linked lists
		if(l1!=0)  // if length not equal return false
			return 0;
		else{ // check for each digit if they are same or not
			int flag=1;
			struct Node* temp=head;
           	struct Node* temp1 = obj.head;
           while(temp!=NULL)
           {
           	if(temp->digit!=temp1->digit){
           		flag=0;
           		break;
           	}
           	temp=temp->next;
           	temp1=temp1->next;
           }
           return flag;
		}   
	}
	friend ostream &operator<<(ostream &out, const BigNum &num){  // overloading cout operator
		struct Node* temp = num.head;
	    while(temp->next != NULL)
			temp= temp->next;
		while(temp!=NULL){
			out<<temp->digit;
			temp = temp->prev;
		}	
	    return out;
	}
	void freeNum(){ // free the linked list corresponding to onject
		struct Node* t;
		while(head!=NULL){
			t = head;
			head = head->next;
			free(t);
		}
	}
};
struct BSTNode { // struct to store Node in BST
	BigNum* value;
	struct BSTNode* left;
	struct BSTNode* right;
	struct BSTNode* parent;
};

struct BSTNode* newBSTNode(BigNum* value){  // allocate a new node to be inserted in BST
	struct BSTNode* newnode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	newnode->value = value;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	return newnode;
}
struct BSTNode* insertBST(struct BSTNode* root, BigNum* value,struct BSTNode* parent){

	if(root==NULL){
		struct BSTNode* newnode = newBSTNode(value);
		newnode->parent = parent;          // create new node
		return newnode;
	}

	if(*value>=*(root->value)){   // go to right tree
		root->right = insertBST(root->right,value,root);
		
	}
	else{        // go to left tree
		root->left = insertBST(root->left,value,root);
	}
	return root;
}

void preorder(struct BSTNode* root){  // preorder traversal VLR
	if(root==NULL)
		return;
	cout<<*(root->value);
	if(root->left != NULL){
		cout<<" ";
		preorder(root->left);
	}
	if(root->right !=NULL){	
		cout<<" ";
		preorder(root->right);
	}
}

string search(struct BSTNode* root,BigNum* key,string bit){  // search a key
	// string bit stores the bit path if exits else -1
	if (root==NULL){
		bit = "-1"; 
		return bit;
	}
	if (*(root->value) == *key)  // if found return
		return bit;		
	if(*key>=*(root->value))  { // search in right subtree
		bit+="1";
		return search(root->right,key,bit);
	}
	else{ 
		bit+="0";
		return search(root->left,key,bit);
	}
}
struct BSTNode* insert(struct BSTNode* root, BigNum* value,struct BSTNode* parent){
	string found = search(root,value,"");
	if(found=="-1")
		return insertBST(root, value,parent);
	else
		return root;
}
void deleteBST(struct BSTNode* root){
	if(root==NULL)
		return;
	deleteBST(root->left); // delete left subtree
	deleteBST(root->right); // delete right subtree
	(root->value)->freeNum(); // free the class object in node
	free(root->value); // free class object
	free(root); // free BST node
}
int main(){
	struct BSTNode* root = NULL; // global BST node
	string s;
	while(getline(cin,s)){ // accept input
	string r;
	stringstream ss(s); // split into words
	ss >> r;
	if (r=="N"){ // new BST
		deleteBST(root); // delete previous BST
		root = NULL;
		int size=0;
		while(ss >> r)
			root = insert(root,new BigNum(r),NULL);	// insert in new BST		
	}
	else if(r=="P"){
		preorder(root); // preorder
		cout<<endl;
	}
	else if(r=="S"){
		ss>>r;
		cout<<search(root,new BigNum(r),"")<<endl; // search
	}	
}
	return 0;
}