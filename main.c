#include <stdio.h>
#include "StrList.h"
#include <string.h>

char* getStringFromUser() {
    int size = 10;  // Initial buffer size
    char* str = (char*)malloc(size * sizeof(char));
    if (str == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int len = 0;  // Length of the input
    char temp;    // Temporary character storage

    // Ignore leading spaces and newline characters
    do {
        temp = getchar();
    } while (temp == ' ' || temp == '\n');

    // Read characters until a space, newline, or EOF is encountered
    while (temp != ' ' && temp != '\n' && temp != EOF) {
        str[len++] = temp;

        // If the length reaches the current buffer size, increase the buffer size
        if (len == size) {
            size += 10;  // Increase buffer size
            char* newstr = realloc(str, size * sizeof(char));
            if (newstr == NULL) {
                perror("Failed to reallocate memory");
                free(str);
                exit(EXIT_FAILURE);
            }
            str = newstr;
        }

        temp = getchar();  // Read the next character
    }

    str[len] = '\0';  // Null-terminate the string
    return str;
}
int main() {
    
    StrList* list = StrList_alloc();
    if (!list) {
        //fprintf(stderr, "Failed to allocate memory for the list\n");
        return EXIT_FAILURE;
    }

    int choice;
    do {
        //printf("\nEnter your choice (0 to exit): ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1: {
                int number;
                //printf("Enter the number of words: ");
                scanf("%d", &number);
                getchar();
                for (size_t i = 0; i < number; i++)
                {
                    char* data= getStringFromUser();
                    if (data[0]!='\0'&&data[0]!='\n'){
                     StrList_insertLast(list,data);
                    }
                    free(data);
                }  
                break;
            }
            case 2: {
                int index;
               // printf("Enter the string and index: ");
                scanf("%d", &index);
                getchar(); // Consume the newline character
                char* data= getStringFromUser();
                if (data!= NULL&& data[0]!='\n')
                {
                     StrList_insertAt(list, data, index);
                     free(data);
                }
                
                break;
            }
            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("%zu\n", StrList_size(list));
                break;
            case 5: {
                int index;
                //printf("Enter the index: ");
                scanf("%d", &index);
                getchar(); // Consume the newline character
                StrList_printAt(list, index);
                break;
            }
            case 6:
                printf("%d\n", StrList_printLen(list));
                break;
            case 7: {
                char data[20];
                //printf("Enter the string to count: ");
                scanf("%19s", data);
                getchar(); // Consume the newline character
                printf("%d\n", StrList_count(list, data));
                break;
            }
            case 8: {
                char data[20];
               // printf("Enter the string to remove: ");
                scanf("%19s", data);
                getchar(); // Consume the newline character
                StrList_remove(list, data);
                break;
            }
            case 9: {
                int index;
                //printf("Enter the index to remove: ");
                scanf("%d", &index);
                getchar(); // Consume the newline character
                StrList_removeAt(list, index);
                break;
            }
            case 10:
                StrList_reverse(list);
                break;
            case 11:
                StrList_free(list);
                list = NULL; // Ensure the list pointer is not used after being freed
                break;
            case 12:
                StrList_sort(list);
                break;
            case 13:
                if (StrList_isSorted(list)==1) {
                    printf("true");
                } else {
                    printf("false");
                }
                break;
            default:
                if (choice != 0) {
                //    printf("Invalid choice. Please try again.\n");
                }
        }
    } while (choice != 0);

    // Ensure the list is freed if not already done
    if (list) {
        StrList_free(list);
    }

    return 0;
}


