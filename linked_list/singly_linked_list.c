#include<stdio.h>
#include<stdlib.h>

//Representation of each node in a linked list
//Each node contain data and address of next node
typedef struct node NODE;
struct node
{
    int data;
    struct node* next;
};


//__________________________________________________________INSERTION_______________________________________________________________

//_________________STARTING____________________
//!! Observation !!!
//IF uses NODE q insted NODE* q then this will not work as we are returning a local variable(NO SCOPE OUTSIDE)
NODE* insert_start(NODE* head,int x)
{
    //Constructing a node with data as x
    NODE* q = (NODE*)malloc(sizeof(NODE)); //Allocating memory to the node
    q->data=x;                             //Adding the data
    q->next=NULL;                          //Setting next pointer to null as it does not pont to another node yet(optional)

    //Now as the node is being inserted at the start the new node becomes the head
    q->next=head;                          //And its next points to previous head

    return q;                              //q is now the new head
}


//_____________________ENDING_____________________
NODE* insert_end(NODE* head,int x)
{
    //Constructing a node with data as x
    NODE* q = (NODE*)malloc(sizeof(NODE)); //Allocating memory to the node
    q->data=x;                             //Adding the data
    q->next=NULL;                          //Setting next pointer to null as it does not pont to another node yet(optional)

    NODE* itr = head;

    //__!!CAUTION!!__
    //if the list is empty itr is null and null->next not meaningful so give error
    //SEGMENTATION FAULT
    //We are trying to access unallocated memeory location
            if(head==NULL)
            {
                return q;
            }   
    while(itr->next!=NULL)                 //If itr->next is pointing to null that means next node is null i.e. itr is pointing to the last node
        itr = itr->next;                   //Shifting the itr forward
    
    //NOW itr is pointing to last element of the list
    //we just need to add the new node at the end
    itr->next = q;
    return head;
}


//_____________________After a given node____________________
NODE* insert_after(NODE* head,int key,int y)
{
    //Constructing a node with data as y
    NODE* q = (NODE*)malloc(sizeof(NODE)); //Allocating memory to the node
    q->data=y;                             //Adding the data
    q->next=NULL;                          //Setting next pointer to null as it does not pont to another node yet(optional)

    NODE* itr = head;

    //__!!CAUTION!!__
    //if the list is empty itr is null and null->next not meaningful so give error
    //SEGMENTATION FAULT
    //We are trying to access unallocated memeory location
    //ITS USAGE IS WRONG
            if(head==NULL)
            {
                return NULL;
            }

    while(itr->data!=key)                  //keep going to next node till we reach the key node
        itr = itr->next;
    
    //now itr points to node with data = key
    
    // 10->20->40, inserting 30 after 20 
    q->next = itr->next;   // 30->40 connecting
    itr->next = q;         // 20->30 connecting
    //__!!CAUTION!!
    //IF we connect 20->30 first the 20->40 link is broken and the address of 40 is lost which was stord in 20 node.
    return head;  
}

//_____Before a node___________
//(TRICKY IMP)
NODE* inset_before(NODE *head,int key,int y)
{
    NODE* q = (NODE*)malloc(sizeof(NODE));
    q->data = y;
    q->next = NULL;

    NODE *itr = head, *itr_prev = NULL;
    
    //if only one element is present initially then or the element is to be inserted at the begining
    //itr_prev = null after loop
    //itr_prev->next give segmentation fault
    if(head->data == key)
    {
        return insert_start(head,y);
    }
    while(itr->data!=key)
    {
        itr_prev = itr;
        itr = itr->next;
    }
    //eg:- 10->20->40
    //add 30 before 40
    //now itr will be pointing to node 40
    //    itr_prev be pointing to node 20

    itr_prev->next = q;      //here order will not matter as no address is lost
    q->next        = itr;

    return head;
}




//_________________________________________________TRAVERSAL______________________________________________________
void display(NODE* head)
{
    NODE* itr = head;                      //Start at the head
    while(itr!=NULL)                       //Go on printing data till the control reaches to last             
    {                                      //itr=null means end of list id reached
        printf("%d ",itr->data);
        itr = itr->next;                   //move the pointer to next node
    }
    printf("\n");
}




//_________________________________________________DELETION_________________________________________________________
//_____DELETE FIRST ELEMENT____
NODE* delete_start(NODE *head)
{
    if(head==NULL)  //The list is already empty
    {
        printf("UNDERFLOW");
        return NULL;
    }

    NODE* first_node = head;
    head = head->next;       //Make next node (2nd) as the head
    free(first_node);        //Delete the first node

    return head;
}

//_____DELETE LAST ELEMENT______
NODE* delete_end(NODE *head)
{
    if(head==NULL)  //The list is already empty
    {
        printf("UNDERFLOW");
        return NULL;
    }
    NODE *itr = head, *itr_prev = NULL;
    while(itr->next!=NULL)
    {
        itr_prev = itr;
        itr = itr->next;
    }
    //now itr points to last element

    //__!!CAUTION!!__
    //if only onle element is present in the list
    //itr->prev give segmentation error
            if(itr_prev == NULL)
            {
                free(head);
                return NULL;
            }

    itr_prev->next = NULL;
    free(itr);
}

//_______DELETE particular node_______
NODE* delete(NODE *head,int key)
{
    NODE *itr = head, *itr_prev = NULL;
    while (itr->data!=key)
    {
        itr_prev = itr;
        itr = itr->next;
    }
    //__!!CAUTION!!__
    //if the element to be deleted is the first element
            if(itr_prev==NULL)
            {
                head = head->next;
                free(itr);
                return head;
            }
    itr_prev->next = itr->next;
    free(itr);
    return head;
}



int main()
{
    //Each list is represented by the head which stores the address of the first node
    NODE* head=NULL;

    head = insert_end(head,30);
    head = insert_end(head,20);
    head = insert_end(head,10);
    
    //Now list becomes like this
    //head -> 30 -> 20 -> 10 -> NULL

    // head = inset_before(head,30,1);
    head = delete(head,30);
    display(head);
    return 0;
}