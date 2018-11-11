#include<iostream>
#include <stdio.h>
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
	~BigNum(){
		struct Node* t;
		while(head!=NULL){
			t = head;
			head = head->next;
			free(t);
		}
	}

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

	static struct Node* addNum(struct Node* head1 , struct Node* head2, struct Node* sum){ // add two doubly linked lists
		struct Node* num1 = head1 ;
		struct Node*  num2 = head2;
		int carry = 0;  // carry forward
		if(num1 == NULL && num2==NULL)
			sum = insertNode(sum,0);
		while(num1 != NULL || num2 != NULL){  // check while digits of both numbers are finished

			int s =0;
			if(num1!=NULL && num2!=NULL){       // if both of them are not finished add both digits and propogate carry
				s = num1->digit + num2->digit + carry;
				num1 = num1->next;
				num2 = num2->next;
			}
			else if(num1 != NULL && num2 == NULL){ // if one is finished , just add carry to the digit of another number
				s = num1->digit + carry;
				num1 = num1->next;
			}
			else{
				s = num2->digit + carry;
				num2 = num2->next;
			}
			
			carry = s/10;
			s = s%10;
			sum = insertNode(sum,s);
		}
		if(carry >0) // check if there is any non-zero carry left
			sum = insertNode(sum,carry);
		return sum;
	}
	static long int len(struct Node * head){ // length of linked lists
		struct Node* temp=head;
		unsigned long int length =0;
		while(temp!=NULL){
			length++;
			temp = temp->next;
		}
		return length;
	}

	BigNum operator + (BigNum const &obj) { // overloading + operator
	    BigNum result;
	    result.head = addNum(head,obj.head,result.head);
	    struct Node* t ;
	    return result;
	}

	bool operator >= (BigNum const &obj) { // overloading >= operator
		long int l1 = len(head) , l2 = len(obj.head); // calculate length of linked lists
		if(l1>l2)  // if first is greater return true
			return 1;
		else if(l1<l2)
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
	friend ostream &operator<<(ostream &out, const BigNum &num){  // overloading cout operator
		struct Node* temp = num.head;
	    while(temp != NULL){
		out<<temp->digit;
		temp= temp->next;
	}
	    return out;
	}
};

int main(){
	while(!cin.eof()){ // read till end of input buffer
	string x,y;
	cin>>x>>y;
	if (x!="" && y!=""){
	BigNum n1(x);
	BigNum n2(y);
	cout<<(n1>=n2)<<endl;
	}}
	return 0;
}
