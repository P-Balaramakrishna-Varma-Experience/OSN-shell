#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#include "Data_Abstractions/StringB.h"
#include "Data_Abstractions/hash.h"
#include "Prompt/prompt.h"
#include "Input/input.h"
#include "Top_Execute/Handler.h"
#include "Data_Abstractions/IOstreams.h"
#include "Signals/Singals.h"

#define Prime_1000 997
char HomeDirectory[PathLenght];
extern IOstreams Global;
bool Foreground_Runing = false;
int Foregoround_pid;
char Foreground_Name[1000];
Hash_quad HashTable;

int main()
{
    struct sigaction ctrl_c, ctrl_z, child;
    Signal_Init_ctrl_c(&ctrl_c);
    Signal_Init_ctrl_z(&ctrl_z);
    Signal_Child(&child);
    sigaction(SIGINT, &ctrl_c, NULL);
    sigaction(SIGTSTP, &ctrl_z, NULL);
    sigaction(SIGCHLD, &child, NULL);

    String User_Line;
    HashTable = Init_quad(Prime_1000);
    Init_Homedirectory(HomeDirectory);
    InitalizeGlobal(&Global);
    
    while(1)
    {
        Print_Prompt(HomeDirectory);
        User_Line = Take_User_Input();
        if(User_Line == NULL)  //due to interpt
            continue;
        MM(User_Line);
    }

    return 0;
}

