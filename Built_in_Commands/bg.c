#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <signal.h>

#include "jobssimilar.h"
#include "../Data_Abstractions/Jobtables.h"
#include "../Data_Abstractions/hash.h"
#include "../Data_Abstractions/proc.h"
#include "../Data_Abstractions/StringB.h"


extern Hash_quad HashTable;

void Cbg(String A)
{
    //removing the first space. And intializing strtok_R
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, "bg") == 0);

    //Getting Jobno.
    Token = strtok_r(NULL, " ", &local);
    int jobNo = Get_int(Token, "bg");
    if(jobNo == -1){return;}
    


    //Only jobNo matters.
    struct pros_record Prose;
    int pid = SignalContinue(jobNo);

    Prose.pid = pid;
    int index = Search_quad(HashTable, &Prose);
    if(index != -1)
        HashTable->Array[index].data->status = running_p;


    if(pid <= 0)
        fprintf(stderr, "bg: Unabe to restart/run in background\n");
}