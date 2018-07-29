#include<iostream>
using namespace std;
struct course {
	string code;
	string name;
	struct course *next;
};
void AddNode(string code,string name,struct course **head)
{
	struct course *newcourse = (struct course*)malloc(sizeof(struct course));
	newcourse->code=code;
	newcourse->name=name;
	newcourse->next=NULL;
	if(*head==NULL)
		*head=newcourse;
	else
	{
		struct course *temp=(struct course*)malloc(sizeof(struct course));
		temp=*head;
		struct course *temp2=(struct course*)malloc(sizeof(struct course));
		while(temp!=NULL)
		{
			temp2=temp;
			temp=temp->next;
		}

		temp2->next=newcourse;
	}
}

void swap(string code1,string code2,struct course **head)
{
	struct course *node1=(struct course*)malloc(sizeof(struct course));
	struct course *node2=(struct course*)malloc(sizeof(struct course));
	struct course *pnode1=(struct course*)malloc(sizeof(struct course));
	struct course *pnode2=(struct course*)malloc(sizeof(struct course));
	struct course *temp =(struct course*)malloc(sizeof(struct course));
	pnode1=NULL;
	pnode2=NULL;
	 node1=*head;
	while(node1->code!=code1)
	{
		pnode1=node1;
		node1=node1->next;
	}
	

	node2=*head;
	while(node2->code!=code2)
	{
		pnode2=node2;
		node2=node2->next;
	}
	
	if(node1==NULL || node2==NULL)
		return;
	if(pnode1==NULL)
	{
		*head=node2;
	}
	else
	{
		pnode1->next=node2;
	}
	if(pnode2==NULL)
	{
		*head=node1;
	}
	else
	{
		pnode2->next=node1;
	}

	temp=node2->next;
	node2->next=node1->next;
	node1->next=temp;



}

void Reverse(struct course **head)
{
	struct course *node1=(struct course*)malloc(sizeof(struct course));
	struct course *node2=(struct course*)malloc(sizeof(struct course));
	struct course *first=(struct course*)malloc(sizeof(struct course));
	struct course *last=(struct course*)malloc(sizeof(struct course));
	node1=*head;
	while(node1!=NULL)
	{
		node2=node1;
		node1=node1->next;
	}
	first=*head;
	last=node2;
	while(true)
	{ int flag=0;
		if(first==last)
			break;

		if(first->next==last)
			flag=1;
		struct course *first1=(struct course*)malloc(sizeof(struct course));
		struct course *last1=(struct course*)malloc(sizeof(struct course));
		first1=first->next;
		struct course *temp=(struct course*)malloc(sizeof(struct course));
		temp=*head;
		while(temp!=last)
		{
			last1=temp;
			temp=temp->next;
		}
		
       swap(first->code,last->code,&(*head));
       first=first1;
       last=last1;
       if(flag==1)
       	break;


	}

}
int main()
{
	struct course *head=NULL;
	AddNode("Hello","my name is",&head);
	
	

	struct course *temp=(struct course*)malloc(sizeof(struct course));
	temp=head;
	while(temp!=NULL)
	{
		cout<<temp->code<<" ";
		temp=temp->next;
	}
	Reverse(&head);
	cout<<endl;
	temp=head;
	while(temp!=NULL)
	{
		cout<<temp->code<<" ";
		temp=temp->next;
	}


	return 0;
}