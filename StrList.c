#include "StrList.h"
#include <stdio.h>
#include <string.h>

typedef struct _node{
    char *data;
    struct _node* _next;
} Node;
   
typedef struct  _StrList {
    Node* _head;
    size_t _size;
}StrList;

Node* Node_alloc(const char* data,Node* next) {
    Node* p= (Node*)malloc(sizeof(Node));
    if(p==NULL){
        return NULL;
    }
	p->data= strdup(data);
	p->_next= next;
	return p;
}

StrList* StrList_alloc(){ 
    StrList* list = (StrList*)malloc(sizeof(StrList));  
        list->_head = NULL; 
        list->_size = 0; 
    return list; 
}

void Node_free(Node* node){
    if (node != NULL) {
        free(node->data);  // Free the dynamically allocated string data
        free(node);        // Free the node itself
    }
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
    if(StrList==NULL){
        return 0;
    }
    else return StrList->_size;
}

void StrList_insertLast(StrList* sourceList, const char* data) {
    Node* newNode = Node_alloc(data, NULL);  // Allocate the new node
    if (newNode == NULL) {
        return;
    }
    // If the list is empty, make the new node the head of the list
    if (sourceList->_head == NULL) {
        sourceList->_head = newNode;
    } else {
        // Otherwise, find the last node
        Node* curr = sourceList->_head;
        while (curr->_next != NULL) {
            curr = curr->_next;
        }
        // Make the last node's _next point to the new node
        curr->_next = newNode;
    }
    // Increment the size of the list (if you're maintaining a size variable)
    sourceList->_size++;
}
void StrList_insertAt(StrList* sourceList, const char* data, int index) {
    Node* newNode = Node_alloc(data, NULL);
    if (index == 0) {
        newNode->_next = sourceList->_head;
        sourceList->_head = newNode;
        return;
    }

    Node* p1 = sourceList->_head;
    for (int i = 1; i < index && p1 != NULL; i++) {
        p1 = p1->_next;
    }

    if (p1 == NULL) {
        perror("Index out of bounds");
        free(newNode); // Free newNode if not inserted
        return;
    }

    newNode->_next = p1->_next;
    p1->_next = newNode;
}

char* StrList_firstData(const StrList* StrList){
    return StrList->_head->data;
}

void StrList_print(const StrList* StrList){
    if (!StrList || !StrList->_head){
        printf("\n");
        return;
    }
    Node* p1 = StrList->_head;
    while (p1){
        printf("%s", p1->data);
        if (p1->_next != NULL) {
            printf(" ");  // Only print space if not the last node
        }
        p1 = p1->_next;
    }
    printf("\n");  // Print newline at the end
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
    printf("\n");
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
 Node* p1=StrList->_head;
while (p1){
    if (strcmp(data,p1->data)==0){
       ans++;
    }
    p1=p1->_next;
}
 return ans;
}

void StrList_remove(StrList* list, const char* data) {
 if (!list || !list->_head || !data) {
        return;
    }
    Node* current = list->_head;
    Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
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
    if (StrList1==NULL && StrList2==NULL)
    {
        return 1;
    }
    

    if (StrList1->_size != StrList2->_size) {
        return 0; // Lists are not equal if their sizes differ
    }
    Node* p1 = StrList1->_head;
    Node* p2 = StrList2->_head;

    while (p1 && p2) { // Check both pointers to be extra safe
        if (strcmp(p1->data, p2->data) != 0) {
            return 0; // Return 0 if there's a mismatch in data
        }
        p1 = p1->_next;
        p2 = p2->_next;
    }

    return 1; // Lists are equal if all their elements match
}
StrList* StrList_clone(const StrList* sourceList) {
	StrList* ans= StrList_alloc();
	 Node* old= sourceList->_head;
	Node** copy= &(ans->_head);
	ans->_size= sourceList->_size;
	while(old) {
		*copy= Node_alloc(old->data,NULL);
		old= old->_next;
		copy= &((*copy)->_next);
	}
	return ans;
}

void StrList_reverse(StrList* sourceList) {
    if (sourceList == NULL || sourceList->_head == NULL) {
        return;
    }
    Node* prev = NULL;
    Node* current = sourceList->_head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->_next;
        current->_next = prev;
        prev = current;
        current = next;
    }
    sourceList->_head = prev;  // Update the head of the list
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

int StrList_isSorted(StrList* sourceStrList){
    StrList* copy = StrList_clone(sourceStrList);
    StrList_sort(copy);
    int isSorted = StrList_isEqual(copy, sourceStrList);
    StrList_free(copy);  // Free the cloned list after use
    return isSorted;
}
