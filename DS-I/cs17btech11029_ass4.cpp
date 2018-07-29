#include<iostream>
using namespace std;
struct list {
	int x;
	struct list *next;
};
void Addnode(struct list **head,int data)
{
	struct list *newnode = (struct list*)malloc(sizeof(struct list));
	newnode->x=data;
	newnode->next=NULL;
	if(*head==NULL)
		*head=newnode;
	else
	{
		struct list *temp = (struct list*)malloc(sizeof(struct list));
		struct list *temp2 = (struct list*)malloc(sizeof(struct list));
		temp=*head;
		temp2=*head;
		while(temp!=NULL)
		{
			temp2=temp;
			temp=temp->next;
		}
		temp2->next=newnode;

	}
}
void Inputlist(struct list **head,int pos)
{
	
	for(int i=0;i>=0;i++)
	{
		cout<<"Enter item for list "<<pos<<" (enter -1 to stop entering) : ";
		int dta;
		cin>>dta;
		if(dta!=-1)
		{
			Addnode(&(*head),dta);
		}
		else
			break;
	}
}
void Union(struct list **head1,struct list **head2 , struct list **head3)
{
	struct list *temp = (struct list*)malloc(sizeof(struct list));
	struct list *temp2 = (struct list*)malloc(sizeof(struct list));
	temp=*head1;
	temp2=*head2;
	while(temp!=NULL && temp2!=NULL)
	{
		if(temp->x > temp2->x)
		{
			Addnode(&(*head3),temp->x);
			temp=temp->next;
		}
		else if(temp->x < temp2->x)
		{
			Addnode(&(*head3),temp2->x);
			temp2=temp2->next;

		}
		else
		{
		    Addnode(&(*head3),temp2->x);
			temp2=temp2->next;
			temp=temp->next;	
		}
	}

	while(temp!=NULL)
	{
		Addnode(&(*head3),temp->x);
		temp=temp->next;
	}
	while(temp2!=NULL)
	{
		Addnode(&(*head3),temp2->x);
		temp2=temp2->next;

	}
}
void DisplayList(struct list *head)
{
	struct list *temp = (struct list*)malloc(sizeof(struct list));
	temp=head;
	while(temp!=NULL)
	{
		cout<<temp->x<<"->";
		temp=temp->next;
	}
	cout<<"NULL"<<endl;
}
int main()
{
	struct list *head1=NULL;
	struct list *head2=NULL;
	struct list *head3=NULL;
	Inputlist(&head1,1);
	cout<<endl;
	Inputlist(&head2,2);
	cout<<endl;
	cout<<"List A : "; DisplayList(head1);
	cout<<"List B : "; DisplayList(head2);
	Union(&head1,&head2,&head3);
	cout<<"List C : "; DisplayList(head3);
	return 0;
}