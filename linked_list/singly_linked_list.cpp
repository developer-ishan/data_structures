#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define BOOST {ios_base::sync_with_stdio(false);cin.tie(NULL);}

typedef long long ll;

class Node{
    private:
        int key;
        Node* next;
    public:
        Node(int key){
            cout<<"Creating new node...\n";
            this->key = key;
        }

        void set_next(Node* node){
            this->next = node;
        }

        void set_key(int key){
            this->key = key; 
        }

        int get_key(){
            return this->key;
        }

        Node* get_next(){
            return this->next;
        }
        ~Node(){
            cout<<"Doconstructing Node\n";
        }
};

class Linked_List{
    private:
        Node* head;
        Node* tail;
    public:
        Linked_List(){
            cout<<"\nCreating a new linked list\n";
            this->head = NULL;
            this->tail = NULL;
        }

        void push_front(Node* node){
            cout<<"\nAdding node to front\n";
            node->set_next(this->head);
            this->head = node;
            if(this->tail == NULL){ //Before insertion list was empty
                this->tail=this->head;
            }
        }

        void pop_front(){
            cout<<"\nRemoving the front element\n";
            if(this->head == NULL)
                throw "Empty list error";
            this->head = this->head->get_next();  //Update the head to point now to next node
            if(this->head == NULL)    //If the list contained only one element now after removing that
                this->tail = NULL;    //it now is empty hence head as well ans tail become null
            
        }

        void push_back(Node* node){
            cout<<"\nAdding node to back\n";
            if(this->tail == NULL){  //If list is empty
                this->head=this->tail=node;
            }
            else{
                this->tail->set_next(node);
                this->tail = node;
            }
        }

        void pop_back(){
            cout<<"\nRemoving the last element of the list\n";
            if(this->head == NULL)
                throw "Empty list error";
            if(this->tail == this->head){
                this->head = this->tail = NULL;
            }
            else{
                Node* itr = this->head;
                while(itr->get_next()->get_next() !=NULL){
                    itr=itr->get_next();
                }
                //When control comes out the loop itr is pointing to the second last node of the list
                itr->set_next(NULL); //Set the second last node's next ptr to point to null this way the last element is removed;
                this->tail = itr;
            }
        }

        void add_after(Node* node,Node* new_node){
            cout<<"\nAdding after "<<node->get_key()<<'\n';
            new_node->set_next(node->get_next());
            node->set_next(new_node);
            if(this->tail == node) //If we are adding at last position
                this->tail = new_node->get_next();
        }
        
        void print(){
            cout<<"Printing the list-------";
            Node* itr = this->head;
            while(itr!=NULL){
                cout<<itr->get_key()<<'\t';
                itr=itr->get_next();
            }
            cout<<'\n';
        }

};
int main()
{
    Linked_List* list = new Linked_List();
    
    for(int i=0;i<3;i++)
    {
        int k;
        cin>>k;
        Node* n = new Node(k);
        list->push_back(n);
    }
    list->print();
    // Node* n1 = new Node(10);
    // Node* n2 = new Node(20);
    // Node* n3 = new Node(30);

    // list->push_front(n1);
    // list->push_front(n2);
    // list->push_front(n3);
    // list->print();

    list->pop_front();
    list->print();

    Node* n4 = new Node(40);
    list->push_back(n4);
    list->print();

    list->pop_back();
    list->print();

    // Node* n5 = new Node(50);
    // list->add_after(n[0],n5);
    // list->print();

    return 0;
}