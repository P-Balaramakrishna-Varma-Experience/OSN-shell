#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "proc.h"

int Next_leastNUmber = 0;
//Assuming pros_record does not caintain any valid value.
void cpyProc(pros_record *A, pros_record B)
{
   pros_record Final = InitProc(B->pid, B->Name, B->status, false);
   Final->JobNumber = B->JobNumber;
   *A = Final;
}

void FreeProc(pros_record A)
{
    free(A->Name);
    free(A);
}

pros_record InitProc(int pid, char * Command, STATUS_pros s, bool First)
{
    pros_record To_Return;

    To_Return = malloc(sizeof(struct pros_record));
    if(To_Return == NULL)
    {
        fprintf(stderr, "Unable to malloc out of spce\n");
        exit(0);
    }

    To_Return->pid = pid;
    To_Return->status = s;
    To_Return->Name = malloc(strlen(Command) + 2);

    if(To_Return->Name == NULL)
    {
        fprintf(stderr, "Unable to malloc out of spce\n");
        exit(0);
    }
    strcpy(To_Return->Name, Command);

    if(First == true)
    {
        To_Return->JobNumber = Next_leastNUmber;
        Next_leastNUmber++;
    }
    else
        To_Return->JobNumber = 0;


    return To_Return;
}
