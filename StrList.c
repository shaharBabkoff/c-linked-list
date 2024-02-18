#include "StrList.h"
#include <stdio.h>
#include <string.h>
#define Max 50

typedef struct _node{
    char data[Max];
    int count;
    struct _node* _next;
} Node;
   
struct  _StrList {
    Node* _head;
    size_t _size;
};
Node* Node_alloc(char data[],Node* next) {
	Node* p= (Node*)malloc(sizeof(Node));
	*p->data= data;
	p->_next= next;
	return p;
}


StrList* StrList_alloc(){ 
    StrList* list = (StrList*)malloc(sizeof(StrList));  
        list->_head = NULL; 
        list->_size = 0; 
    return list; 
} 
 
void StrList_free(StrList* StrList){
if (StrList==NULL) return;
	Node* p1= StrList->_head;
	Node* p2;
	while(p1) {
		p2= p1;
		p1= p1->_next;
		Node_free(p2);
	}
	free(StrList);
} 

size_t StrList_size(const StrList* StrList){
    return StrList->_size;
}

void StrList_insertLast(StrList* sourceList, const char* data){
Node* new= Node_alloc(data,NULL);
Node* p1= sourceList->_head;
while (p1->_next != NULL)
{
    p1= p1->_next;
}
p1->_next= new;
}
void StrList_insertAt(StrList* sourceList,const char* data,int index){
Node* new= Node_alloc(data,NULL);
Node* p1= sourceList->_head;
for (size_t i = 0; i < index; i++)
{
   p1=p1->_next;
}
new->_next=p1->_next;
p1->_next=new;
}

char* StrList_firstData(const StrList* StrList){
    return StrList->_head->data;
}

void StrList_print(const StrList* StrList){
    if (!StrList){
       return;
    }
    Node* p1=StrList->_head;
    while (p1){
       printf("%s\n", p1->data);
       p1=p1->_next;
    }
}
void StrList_printAt(const StrList* Strlist,int index){
     if (!Strlist){
       return;
    }
    Node* p1=Strlist->_head;
    while (index>0)
    {
        p1=p1->_next;
        index--;
    }
    printf("%s",p1->data);
}

int StrList_printLen(const StrList* Strlist){
    int ans=0;
    Node* p1=Strlist->_head;
    while (p1){
    ans=ans+strlen(p1->data); 
    p1=p1->_next;
    }
    return ans;
}

int StrList_count(StrList* StrList, const char* data){
int ans=0;
const Node* p1=StrList->_head;
while (p1){
    if (strcmp(data,p1->data)){
       ans++;
    }
}
 return ans;
}

void StrList_remove(StrList* list, const char* value) {
 if (!list || !list->_head || !value) {
        return;
    }
    Node* current = list->_head;
    Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            if (prev == NULL) {
                list->_head = current->_next;
            } else {
                prev->_next = current->_next;
            }
            Node* temp = current; 
            current = current->_next;
            free(temp->data); 
            free(temp);
            if (list->_size > 0) {
                list->_size--;
            }
        } else {
            prev = current;
            current = current->_next;
        }
    }
}
void StrList_removeAt(StrList* list, int index) {
    if (!list || !list->_head || index < 0) {
        // If the list is NULL, empty, or the index is invalid, no action is needed.
        return;
    }
    Node* current = list->_head;
    Node* prev = NULL;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index) {
        prev = current; // Track the previous node
        current = current->_next; // Move to the next node
        currentIndex++; // Increment the index counter
    }
    if (current == NULL) {
        // Index is out of the list's range
        return;
    }
    // Remove the node at the index
    if (prev == NULL) {
        // The node to remove is the head of the list
        list->_head = current->_next;
    } else {
        // Bypass the current node
        prev->_next = current->_next;
    }
    // Free the removed node's resources
    free(current->data); // Assuming data was dynamically allocated
    free(current);
    // Update list size if maintained
    if (list->_size > 0) {
        list->_size--;
    }
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if(StrList1->_size!=StrList2->_size){
        return 0;
    }
    const Node* p1=StrList1->_head;
    const Node* p2=StrList2->_head;
    while (p1){
       if (!strcmp(p1->data,p2->data)){
        return 0;
       }
       p1=p1->_next;
       p2=p2->_next;
    }
    return 1;
}
StrList* StrList_clone(const StrList* sourceList) {
	StrList* ans= StrList_alloc();
	const Node* old= sourceList->_head;
	Node** copy= &(ans->_head);
	ans->_size= sourceList->_size;
	while(old) {
		*copy= Node_alloc(old->data,NULL);
		old= old->_next;
		copy= &((*copy)->_next);
	}
	return ans;
}

void StrList_reverse( StrList* sourceList){
    if (sourceList == NULL)
    {
        return;
    }
    const Node* temp= sourceList->_head;
    const Node* new_head = NULL;
    // create new nodes and insert them beginning
    while (temp != NULL)
    {
        struct node* new_node = Node_alloc(temp->data,new_head);
        new_head = new_node;
        temp = temp->_next;

    }
    // update the head with the new head
    sourceList = new_head;
}
    
void StrList_sort(StrList* list) {
    if (!list || !list->_head || !list->_head->_next) {
        return;
    }
    Node* sorted = NULL; 
    Node* current = list->_head; 
    while (current != NULL) {
        Node* next = current->_next; 
        Node** tracer = &sorted;
        while (*tracer != NULL && strcmp((*tracer)->data, current->data) < 0) {
            tracer = &((*tracer)->_next); 
        }
        current->_next = *tracer;
        *tracer = current;
        current = next;
    }
    list->_head = sorted;
}
int StrList_isSorted(StrList* sorceStrList){
    StrList* copy= StrList_clone(sorceStrList);
    StrList_sort(copy);
    if (StrList_isEqual(copy,sorceStrList)==1){
    return 1;
    }
    return 0;
}
    
	
    




