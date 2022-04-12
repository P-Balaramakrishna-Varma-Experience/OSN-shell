#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>
#include <signal.h>

#include "../Data_Abstractions/hash.h"
#include "../Data_Abstractions/Jobtables.h"
#include "../Data_Abstractions/proc.h"
#include "../Data_Abstractions/StringB.h"
#include "jobssimilar.h"

extern struct pros_record *Job_Table;
extern Hash_quad HashTable;


//Some abstractions
int Index_JobsTable(int Job_Number, int Size)
{
    int i;
    for(i = 0; i < Size; i++)
        if(Job_Table[i].JobNumber == Job_Number)
            break;

    if(i == Size)  //did not find the corresponding job number.
        return -1;
    else 
        return i;
}

//CommName is for output printing purpose
int Get_int(char *Token, char *CommName)
{
    if(Token == NULL)
        return -1;

    char *endptr = NULL;
    int n = (int)strtol(Token, &endptr , 10);

    if(strlen(endptr) != 0)
    {
        fprintf(stderr,"%s: Error agr %s is not a number \n", CommName ,Token);
        return -1;
    }

    if(n < 0)
    {
        fprintf(stderr,"%s: Number must be greater than 0",CommName);
        return -1;
    }
    return n;

}

void TakeInputFgBg(int *job_no, String A, char *Command)
{
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, Command) == 0);

    Token = strtok_r(NULL, " ", &local);
    *job_no = Get_int(Token, "sig");
    if(*job_no == -1){return;}


    Token = strtok_r(NULL, " ", &local);
    if(Token != NULL)
        fprintf(stderr,"%s: More arguments are given. These are ignored",Command);
}

int SignalContinue(int JobNumber)
{
    char A[100];
    sprintf(A,"sig %d %d",JobNumber, SIGCONT);

    int ret = CSig(A);

    return ret;
}