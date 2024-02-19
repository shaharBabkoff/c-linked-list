#include <stdio.h>
#include "StrList.h"

int main() {
    StrList* list= StrList_alloc();
    if (!list)
    {
        fprintf(stderr,"fail to allocat memory for list");
        return EXIT_FAILURE;
    }
    
    int func;
    //printf("Enter first number: ");
    scanf("%d", &func);
    while (func !=0)
    {
        if(func ==1){
            char c;
            scanf ("%c",&c);
            if (c=='A')
            {
            listFromUser(list);
            }
        }
        if (func==2)
        {
            char data [20];
            scanf("%s",data);
            int index;
            scanf ("%d",&index);
            StrList_insertAt(list,data,index);
        }
        if (func==3)
        {
        StrList_print(list);
        }
        if (func==4){
            StrList_size(list);
        }
        if (func==5)
        {
            int index;
            scanf ("%d",&index);
            StrList_printAt(list,index);
        }
        if (func==6)
        {
            StrList_printLen(list);
        }
        if (func==7)
        {
            char data [20];
            scanf("%s",data);
           int ans= StrList_count(list,data);
           printf("%d",ans);
        }
        if (func==8)
        {
            char data [20];
            scanf("%s",data);
            StrList_remove(list,data);
        }
        if (func==9)
        {
            int index;
            scanf ("%d",&index);
            StrList_removeAt(list,index);
        }
        if (func==10)
        {
            StrList_reverse(list);
        }
        if (func==11)
        {
            StrList_free(list);
        }
        if (func==12)
        {
            StrList_sort(list);
        }
        if (func==13)
        {
            StrList_isSorted(list);
        }
        scanf("%d", &func);
    }
return 0;
}
