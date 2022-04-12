#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#include "jobssimilar.h"
#include "../Data_Abstractions/Jobtables.h"
#include "../Data_Abstractions/hash.h"
#include "../Data_Abstractions/proc.h"
#include "../Data_Abstractions/StringB.h"


extern Hash_quad HashTable;
extern bool Foreground_Runing;
extern int Foregoround_pid;
extern char Foreground_Name[1000];



void Cfg(String A)
{
    //removing the first space. And intializing strtok_R
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, "fg") == 0);

    //Getting Jobno.
    Token = strtok_r(NULL, " ", &local);
    int jobNo = Get_int(Token, "fg");
    if(jobNo == -1){return;}
    


    //Only jobNo matters.
    struct pros_record Prose;
    int pid = SignalContinue(jobNo);
    Prose.pid = 0;
    int index = Search_quad(HashTable, &Prose);


    if(pid > 0)
    {
        Foregoround_pid = pid; 
        Foreground_Runing = true;
        if(index != -1)
            strcpy(Foreground_Name, HashTable->Array[index].data->Name);
        Delete_quad(&HashTable, &Prose);
        waitpid(pid, NULL, 0);
        Foreground_Runing = false;
    }
    else //invalid pid
        fprintf(stderr, "fg: Unabe to restart/run in foreground\n");

}