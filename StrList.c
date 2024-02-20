#include "StrList.h"
#include <stdio.h>
#include <string.h>
#define Max 50

typedef struct _node{
    char *data;
    struct _node* _next;
} Node;
   
typedef struct  _StrList {
    Node* _head;
    size_t _size;
}StrList;

Node* Node_alloc(const char *data,Node* next) {
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
    free(node);
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
// void listFromUser(StrList* ans, int number){
//     int size=10;
//     char c;
//     int len=0;
//     char *data;
//     while (c!= '\n')
//     {
//         while (c!="")
//         {
//         c= getchar();
//         data=+c;
//         len++;
//         }
//         if (len==size){
//             size*=2;
//         realloc(ans,size);
//         }
//         Node* new= Node_alloc(data,NULL);
//         StrList_insertLast(ans,data);
    
// }
    
// }
void listFromUser(StrList* ans, int number) {
    int size = 10; // Initial capacity of the word buffer
    char* wordBuffer = (char*)malloc(size * sizeof(char));
    if (!wordBuffer) {
        perror("Failed to allocate word buffer");
        exit(EXIT_FAILURE);
    }

    int wordLength = 0;
    int wordCount = 0;
    char c;

    printf("Enter %d words separated by spaces:\n", number);

    // Read characters until the specified number of words have been read
    while (wordCount < number && (c = getchar()) != EOF) {
        if (c == ' ' || c == '\n') {
            if (wordLength > 0) { // A word has been collected
                wordBuffer[wordLength] = '\0'; // Null-terminate the current word
                // Insert the word into the list
                StrList_insertLast(ans, wordBuffer);
                wordCount++; // Increment the word count
                wordLength = 0; // Reset the word length for the next word

                if (c == '\n') break; // Stop reading if newline is encountered
            }
        } else {
            // Add the character to the word buffer
            wordBuffer[wordLength++] = c;

            // Resize the buffer if necessary
            if (wordLength == size) {
                size *= 2; // Double the buffer size
                char* temp = (char*)realloc(wordBuffer, size * sizeof(char));
                if (!temp) {
                    perror("Failed to resize word buffer");
                    free(wordBuffer);
                    exit(EXIT_FAILURE);
                }
                wordBuffer = temp;
            }
        }
    }

    // Free the word buffer
    free(wordBuffer);
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
        // Handle memory allocation failure if needed
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
       printf("%s ", p1->data);
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
int StrList_isSorted(StrList* sorceStrList){
    StrList* copy= StrList_clone(sorceStrList);
    StrList_sort(copy);
    if (StrList_isEqual(copy,sorceStrList)==1){
    return 1;
    }
    return 0;
}
    
	
    




