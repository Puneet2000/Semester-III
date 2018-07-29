#include<iostream>
using namespace std;
struct cgpa{
	float cg;
	struct cgpa *next;
};
int main()
{
	struct cgpa *head=NULL;
	struct cgpa *s1 = (struct cgpa*) malloc(sizeof(struct cgpa));
	struct cgpa *s2 = (struct cgpa*) malloc(sizeof(struct cgpa));
	struct cgpa *s3 = (struct cgpa*) malloc(sizeof(struct cgpa));
	struct cgpa *s4 = (struct cgpa*) malloc(sizeof(struct cgpa));
	struct cgpa *temp = (struct cgpa*) malloc(sizeof(struct cgpa));

cout<<"Enter the CGPA's (with spaces) : ";
cin>>(s1->cg)>>(s2->cg)>>(s3->cg)>>(s4->cg);
head=s4;
s4->next=s3;
s3->next=s2;
s2->next=s1;
s1->next=NULL;
temp=head;
int i=0;
while(temp!=NULL)
{
	cout<<"Node "<<i<<endl;
	cout<<"index : "<<i<<"\nvalue : "<<temp->cg<<"\nNode address : "<<&temp<<"\npointer address : "<<temp->next<<endl;
	temp=temp->next;
	i++;
}
free(s1);
free(s2);
free(s3);
free(s4);
free(head);
free(temp);
cout<<"Memory deallocated"<<endl;

return 0;}