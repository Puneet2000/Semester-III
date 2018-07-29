#include<iostream>
#include<string>
#include<stack>
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
void deleteNode(struct course **head_ref, string key)
{
    struct course *temp = (struct course*)malloc(sizeof(struct course));
    temp=*head_ref;
        struct course *prev = (struct course*)malloc(sizeof(struct course));

    
    if (temp != NULL && temp->code == key)
    {
        *head_ref = temp->next;   // Changed head
        free(temp);               // free old head
        return;
    }

    
    while (temp != NULL && temp->code != key)
    {
        prev = temp;
        temp = temp->next;
    }

  
    if (temp == NULL) return;

   
    prev->next = temp->next;

    free(temp);  
}


void split(struct course **head,struct course **head1)
{ 
    stack <string> codes;
  struct course *temp = (struct course*)malloc(sizeof(struct course));
 

  temp=*head;
  
  
  while(temp!=NULL)
  {
  	string co = temp->code;
  	string nm=temp->name;
  	char ch=co[5];
  	if(ch=='0' || ch=='2' || ch=='4' || ch=='8' || ch=='6')
  	{
  		AddNode(co,nm,&(*head1));
  		codes.push(co);
  		temp=temp->next;

  		

  	}
  	else
  	{
  		temp=temp->next;
  	}


  	
  }
  while(!codes.empty())
  	{
  		deleteNode(&(*head),codes.top());
  		
  		codes.pop();
  	}
  
  

}
void printList(struct course *head)
{
	struct course *node = (struct course*)malloc(sizeof(struct course));
	node=head;
  while (node != NULL)
  {
     cout<<"("<<node->code<<" " <<&(*node)<<")"<<"->";
     node = node->next;
  }
  cout<<"NULL";
}
void freeList(struct course* head)
{
   struct course* tmp;

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
	struct course *head=NULL;
	struct course *head1=NULL;
	char choice ='Y';
	do {
		string code;
		string name;
		cout<<"Enter code : ";
		cin>>code;
		cout<<"Enter name : ";
		cin>>name;
		AddNode(code,name,&head);
		cout<<"Enter Y or y to continue : ";
		cin>>choice;
	}while(choice=='Y' || choice == 'y');

	printList(head);
	cout<<endl;
	split(&head,&head1);
	printList(head);
	cout<<endl;
	printList(head1);
	cout<<endl;
  freeList(head);
  freeList(head1);
	
   
	




return 0;}