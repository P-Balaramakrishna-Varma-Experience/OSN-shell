#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "proc.h"
#include "hash.h"
#include "Jobtables.h"

int Compare_Pros(const void *First, const void *Second)
{
    pros_record First_P = First, Second_P = Second;
    return strcmp(First_P->Name, Second_P->Name);
}

int Make_Jobs_Table(Hash_quad H, struct pros_record** Table_Ans)
{
    //create
    pros_record Table = malloc( sizeof(struct pros_record)*(H->filled) );

    int index = 0;
    for(int i = 0; i < H->tableSize; i++)
        if(H->Array[i].condition == filled)
        {
            Table[index].Name = malloc(strlen(H->Array[i].data->Name) + 2);
            if(Table[index].Name == NULL)
            {
                fprintf(stderr,"unable to allocate memory malloc \n");
                exit(0);
            }
            
            strcpy(Table[index].Name, H->Array[i].data->Name);
            Table[index].pid = H->Array[i].data->pid;
            Table[index].status = H->Array[i].data->status;
            Table[index].JobNumber = H->Array[i].data->JobNumber;
            index++;
        }

    //sort
    qsort(Table, H->filled, sizeof(struct pros_record), Compare_Pros);

   //return
   *Table_Ans = Table;
   return H->filled; 
}


void Clear_Jobs_Table(struct pros_record* A, int size)
{
    for(int i = 0; i < size ; i++)
        free(A[i].Name);
    
    free(A);
}