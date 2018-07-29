struct Node
{
  int data;
  struct Node *next;
};
 
/* Given a reference (pointer to pointer) to the head of a list and 
   an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
 
    /* 2. put in the data  */
    new_node->data  = new_data;
 
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);
 
    /* 4. move the head to point to the new node */
    (*head_ref)    = new_node;
}
 
/* Given a node prev_node, insert a new node after the given 
   prev_node */
void insertAfter(struct Node* prev_node, int new_data)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
      printf("the given previous node cannot be NULL");
      return;
    }
 
    /* 2. allocate new node */
    struct Node* new_node =(struct Node*) malloc(sizeof(struct Node));
 
    /* 3. put in the data  */
    new_node->data  = new_data;
 
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;
 
    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;
}
 
/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct Node** head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
 
    struct Node *last = *head_ref;  /* used in step 5*/
 
    /* 2. put in the data  */
    new_node->data  = new_data;
 
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
 
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
 
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}
 
// This function prints contents of linked list starting from head
void printList(struct Node *node)
{
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
}
 
/* Driver program to test above functions*/
int main()
{
  /* Start with the empty list */
  struct Node* head = NULL;
 
  // Insert 6.  So linked list becomes 6->NULL
  append(&head, 6);
 
  // Insert 7 at the beginning. So linked list becomes 7->6->NULL
  push(&head, 7);
 
  // Insert 1 at the beginning. So linked list becomes 1->7->6->NULL
  push(&head, 1);
 
  // Insert 4 at the end. So linked list becomes 1->7->6->4->NULL
  append(&head, 4);
 
  // Insert 8, after 7. So linked list becomes 1->7->8->6->4->NULL
  insertAfter(head->next, 8);
 
  printf("\n Created Linked list is: ");
  printList(head);
 
  return 0;
}
void deleteNode(struct Node **head_ref, int key)
{
    // Store head node
    struct Node* temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key)
    {
        *head_ref = temp->next;   // Changed head
        free(temp);               // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp);  // Free memory
}
void Delete(struct course **head,struct course **ref)
{
      if(*head==*ref)
      {
        *head=(*ref)->next;
        free(*ref);
      }
      else
      {
        struct course *temp = (struct course*)malloc(sizeof(struct course));
        struct course *pnode = (struct course*)malloc(sizeof(struct course));
        temp=*head;
        while(temp!=*ref)
        {
          pnode=temp;
          temp=temp->next;
        }

        pnode->next=temp->next;
        free(temp);
      }
}
void split(struct course **head,struct course **head1)
{
  struct course *temp = (struct course*)malloc(sizeof(struct course));
  struct course *p = (struct course*)malloc(sizeof(struct course));
  temp=*head;
  while(temp!=NULL)
  {
    if(temp->code[5]=='0' || temp->code[5]=='2' || temp->code[5]=='4' || temp->code[5]=='6' || temp->code[5]=='8')
    {
      AddNode(temp->code,temp->name,&(*head1));
      p=temp;
      Delete(&(*head),&p);
      temp=temp->next;

    }
    else
    {
      temp=temp->next;
    }
  }

}
while(temp!=NULL)
  {
    string co = temp->code;
    string nm=temp->name;
    int l= co.size();
    if(co[l-1]=='0' || co[l-1]=='2' || co[l-1]=='4' || co[l-1]=='6' || co[l-1]=='8')
    {
      cout<<"identified";
      AddNode(co,nm,&h2);
      p=temp->next;
      deleteNode(&h1,co);
      temp=p;

    }
    else
    {
      temp=temp->next;
    }
  }