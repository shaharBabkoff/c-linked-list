// #include <stdio.h>
// #include "StrList.h"

// int main() {
//     char *strings[] = {"Hello", "World", "This", "Is", "An", "World", "Of", "World"};

//     int i;
    
//     StrList* list = StrList_alloc();
    
//     for (i = 0; i < 5; ++i) {
//         StrList_insertLast(list, strings[i]);
//     }
//     //StrList* list= StrList_alloc();
//     int choice;
//     if (!list)
//     {
//         fprintf(stderr,"fail to allocat memory for list");
//         return EXIT_FAILURE;
//     }
//     do{
//     printf("Enter first number: ");
//     scanf("%d", &choice);
//     switch (choice)
//     {
//     case 1:
//           int number;
//           scanf("%d",&number);
//         //  listFromUser(list, number);
//         break;
//      case 2:{
//             char data [20];
//             scanf("%s",data);
//             int index;
//             scanf ("%d",&index);
//             StrList_insertAt(list,data,index);
//             break;
//      }
//        case 3:
//         StrList_print(list);
//         break;
//         case 4:
//            printf("%d", StrList_size(list));
//             break;
//        case 5:{
//             int index;
//             scanf ("%d",&index);
//             StrList_printAt(list,index);
//             break;
//        }
//         case 6:
//             StrList_printLen(list);
//             break;
//         case 7:{
//             char data [20];
//             scanf("%s",data);
//            int ans= StrList_count(list,data);
//            printf("%d",ans);
//         break;
//         }
//         case 8:{
//             char data [20];
//             scanf("%s",data);
//             StrList_remove(list,data);
//         break;
//         }
//         case 9:{
//             int index;
//             scanf ("%d",&index);
//             StrList_removeAt(list,index);
//         break;
//         }
//         case 10:
//             StrList_reverse(list);
//         break;
//         case 11:
//             StrList_free(list);
//         break;
//         case 12:
//             StrList_sort(list);
//         break;
//         case 13:
//             StrList_isSorted(list);
//         break;
//     }
//     }while (choice!=0);
// return 0;
// }
#include <stdio.h>
#include "StrList.h"

int main() {
    char *strings[] = {"Hello", "World", "This", "Is", "An", "Example"};
    int i;
    StrList* list = StrList_alloc();

    if (!list) {
        fprintf(stderr, "Failed to allocate memory for the list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < 6; ++i) {
        StrList_insertLast(list, strings[i]);
    }

    int choice;
    do {
        printf("\nEnter your choice (0 to exit): ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1: {
                int number;
                printf("Enter the number of words: ");
                scanf("%d", &number);
                getchar(); // Consume the newline character
                // listFromUser(list, number); // Make sure this function is implemented correctly
                break;
            }
            case 2: {
                char data[20];
                int index;
                printf("Enter the string and index: ");
                scanf("%19s %d", data, &index);
                getchar(); // Consume the newline character
                StrList_insertAt(list, data, index);
                break;
            }
            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("List size: %zu\n", StrList_size(list));
                break;
            case 5: {
                int index;
                printf("Enter the index: ");
                scanf("%d", &index);
                getchar(); // Consume the newline character
                StrList_printAt(list, index);
                break;
            }
            case 6:
                printf("Total length of all strings: %d\n", StrList_printLen(list));
                break;
            case 7: {
                char data[20];
                printf("Enter the string to count: ");
                scanf("%19s", data);
                getchar(); // Consume the newline character
                printf("Occurrences: %d\n", StrList_count(list, data));
                break;
            }
            case 8: {
                char data[20];
                printf("Enter the string to remove: ");
                scanf("%19s", data);
                getchar(); // Consume the newline character
                StrList_remove(list, data);
                break;
            }
            case 9: {
                int index;
                printf("Enter the index to remove: ");
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
                    printf("The list is sorted.\n");
                } else {
                    printf("The list is not sorted.\n");
                }
                break;
            default:
                if (choice != 0) {
                    printf("Invalid choice. Please try again.\n");
                }
        }
    } while (choice != 0);

    // Ensure the list is freed if not already done
    if (list) {
        StrList_free(list);
    }

    return 0;
}
