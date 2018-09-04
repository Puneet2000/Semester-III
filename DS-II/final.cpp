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

	BigNum(){
		this->head = NULL; // constructor initialising head = NULL
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

	BigNum operator + (BigNum const &obj) { // overloading + operator
	    BigNum result;
	    result.head = addNum(head,obj.head,result.head);
	    return result;
	}

	friend ostream &operator<<(ostream &out, const BigNum &num){  // overloading cout operator
		struct Node* temp = num.head;
	    while(temp != NULL){
		out<<temp->digit;
		temp= temp->next;
	}
	    return out;
	}
 
	friend istream &operator>>( istream  &input, BigNum &num ) { // overloading cin operator
		string s;
		input>>s;
		long long int j =0;
		for (j=0;s[j]=='0';j++);
		for(long long int i=j;i<s.length();i++){
			int d = s[i]-48;
			num.head = insertNode(num.head,d);
		}
        return input;           
      }

};

int main(){
	while(!cin.eof()){ // read till end of input buffer
	BigNum x,y;
	cin>>x>>y;
	cout<<x+y<<endl;
}
	
	return 0;
}