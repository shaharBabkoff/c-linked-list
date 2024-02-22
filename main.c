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
      // Example modification for the first scanf call

if (scanf("%d", &choice) != 1) {
    fprintf(stderr, "Error reading choice.\n");
    // Clear the input buffer to remove any leftover input
    while ((choice = getchar()) != '\n' && choice != EOF) { }
    // Optionally, prompt the user to try again or handle the error in another way
    continue; // For example, you might want to skip to the next iteration of the loop
}



        switch (choice) {
            case 1: {
                int number;
                //printf("Enter the number of words: ");
                if (scanf("%d", &number) != 1) {
    fprintf(stderr, "Error reading the number of words.\n");
    while ((number = getchar()) != '\n' && number != EOF) { } // Clear the input buffer
    continue; // Skip to the next iteration or handle the error differently
}
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
                if (scanf("%d", &index) != 1) {
    fprintf(stderr, "Error reading the index.\n");
    while ((index = getchar()) != '\n' && index != EOF) { } // Clear the input buffer
    continue; // Skip to the next iteration or handle the error differently
}
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
                if (scanf("%d", &index) != 1) {
    fprintf(stderr, "Error reading the index.\n");
    while ((index = getchar()) != '\n' && index != EOF) { } // Clear the input buffer
    continue; // Skip to the next iteration or handle the error differently
}
                StrList_printAt(list, index);
                break;
            }
            case 6:
                printf("%d\n", StrList_printLen(list));
                break;
            case 7: {
                char* data= getStringFromUser();
                printf("%d\n", StrList_count(list, data));
                free(data);
                break;
            }
            case 8: {
                char* data= getStringFromUser();
                StrList_remove(list, data);
                free(data);
                break;
            }
            case 9: {
                int index;
                //printf("Enter the index to remove: ");
                if (scanf("%d", &index) != 1) {
    fprintf(stderr, "Error reading the index.\n");
    while ((index = getchar()) != '\n' && index != EOF) { } // Clear the input buffer
    continue; // Skip to the next iteration or handle the error differently
}
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
                    printf("true\n");
                } else {
                    printf("false\n");
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

