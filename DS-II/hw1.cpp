#include<iostream>
using namespace std;
struct Node {
	int digit;
	struct Node* next;
	struct Node* prev;
};

struct Node* insertNode(struct Node* head ,int digit){

	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->digit = digit;
	newnode->prev = NULL;
	newnode->next = NULL;
	if(head == NULL)
		head = newnode;
	else{
		newnode->next = head;
		head->prev = newnode;
	}
	return newnode;
}

struct Node* addNum(struct Node* head1 , struct Node* head2, struct Node* sum){
	struct Node* num1 = head1 ;
	struct Node*  num2 = head2;
	int carry = 0;
	while(num1 != NULL || num2 != NULL){

		int s =0;
		if(num1!=NULL && num2!=NULL){
			s = num1->digit + num2->digit + carry;
			num1 = num1->next;
			num2 = num2->next;
		}
		else if(num1 != NULL && num2 == NULL){
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
	return sum;
}
int main(){

	struct Node* head = NULL;
	head = insertNode(head,1);
	head = insertNode(head,2);
	head = insertNode(head,2);
	head = insertNode(head,2);
	struct Node* head1 = NULL;
	head1 = insertNode(head1,1);
	head1 = insertNode(head1,2);
	head1 = insertNode(head1,3);
	struct Node* sum =NULL;
	sum = addNum(head1,head,sum);
	while(sum != NULL){
		cout<<sum->digit;
		sum= sum->next;
	}
	return 0;
}