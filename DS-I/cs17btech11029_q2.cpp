#include<iostream>
using namespace std;
struct cgpa{
	float cg;
	struct cgpa *next;
};

void AddNode(struct cgpa** ref,float cgpa)
{
	struct cgpa *newnode =(struct cgpa*) malloc(sizeof(struct cgpa));
	newnode->cg=cgpa;
	newnode->next = (*ref);
	(*ref) = newnode;
}
void print(struct cgpa *hed)
{
	struct cgpa *temp=(struct cgpa*) malloc(sizeof(struct cgpa));
	temp=hed;
	int i=0;
while(temp!=NULL)
{
	cout<<"Node "<<i<<endl;
	cout<<"index : "<<i<<"\nvalue : "<<temp->cg<<"\nNode address : "<<&temp<<"\npointer address : "<<temp->next<<endl;
	temp=temp->next;
	i++;
}
}
void freeList(struct cgpa* head)
{
   struct cgpa* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

    cout<<"Memory deallocated"<<endl;

}
int main()
{
	
	struct cgpa *head=NULL;
	for (int i=0;i>=0;i++)
	{
		float x;
		cout<<"Enter cgpa (-1 to stop) : ";
		cin>>x;
		if(x>=0)
		{
			AddNode(&head,x);
		}
		else
		{
			print(head);
			break;
		}

	}

	freeList(head);




return 0;}