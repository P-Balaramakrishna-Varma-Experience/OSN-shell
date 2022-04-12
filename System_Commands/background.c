#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "../Data_Abstractions/StringB.h"
#include "../Data_Abstractions/proc.h"
#include "../Data_Abstractions/hash.h"
#include "../Prompt/prompt.h" //pathlenght
#include "background.h"

extern char HomeDirectory[PathLenght];
extern int Next_leastNUmber;
extern Hash_quad HashTable;

void Remove_and(String Command);

void Run_in_background(String Command)
{
    Remove_and(Command);
    String StoreCommand = String_Create(sizeof(Command));
    strcpy(StoreCommand, Command);

    //getting lenght
    int Length = No_of_Words(Command);
    if(Length == -1)
        return ;
    strcpy(Command, StoreCommand);

    //getting the arguments
    StringArray Args = Generate_Format(Command, Length);
    strcpy(Command, StoreCommand);
    String_Delete(StoreCommand);



    //Actual code Given all input in desired form
    int id = fork();

    if(id > 0) //Parent
    {
        struct pros_record A;
        A.pid = id;
        A.Name = Args[0];
        A.status = running_p;
        A.JobNumber = Next_leastNUmber;
        Next_leastNUmber++;
        
        printf("%d\n", id);

        Insert_quad(&HashTable, &A);
        StringArray_Delete(Args, Length + 1);
        return;
    }

    if(id == 0)//Child resposible to run command and print output
    {
        sleep(1);
        setpgid(0, 0);
        execvp(Args[0], Args);
        exit(3);
    }

    if(id < 0) //error
    {
        printf("BKSH: Uanble to fork for \"%s\"  continuing to execute other commands\n",Command);
        return;
    }
}




void Remove_and(String Command)
{
    char *loc = strrchr(Command, (int)('&') );
    int index = loc - Command;
    Command[index] = '\0';
}
            //waitpid(childId, &Status, 0);