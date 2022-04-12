#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include <assert.h>

#include "../Data_Abstractions/StringB.h"
#include "Foreground.h"
extern bool Foreground_Runing; 
extern int Foregoround_pid;
extern char Foreground_Name[1000];

void Run_In_Foreground(String Command)
{
    String StoreCommand = String_Create(sizeof(Command));
    strcpy(StoreCommand, Command);

    //getting lenght
    int Length = No_of_Words(Command);
    if(Length == -1)
        return;
    strcpy(Command, StoreCommand);

    //getting the arguments
    StringArray Args = Generate_Format(Command, Length);
    strcpy(Command, StoreCommand);
    String_Delete(StoreCommand);



    //Actual code Given all input in desired form
    int id = fork();

    if(id > 0) //Parent
    {
        Foregoround_pid = id;
        Foreground_Runing = true;
        strcpy(Foreground_Name, Args[0]);

        waitpid(id,NULL,0);

        Foreground_Runing = false;
        Foregoround_pid = -1;
        StringArray_Delete(Args, Length + 1);
        return;
    }

    if(id == 0)
    {
        execvp(Args[0], Args);

        printf("\nSome error cannot load the command \"%s\" (Command not found check speeling)\n", Command);
        exit(0);
    }

    if(id < 0) //error
    {
        printf("BKSH: Uanble to fork for \"%s\"  continuing to execute other commands\n",Command);
        return;
    }
}