#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "../Data_Abstractions/hash.h"
#include "../Data_Abstractions/Jobtables.h"
#include "../Data_Abstractions/proc.h"
#include "jobssimilar.h"

extern struct pros_record *Job_Table;
extern Hash_quad HashTable;

int Actualt_Sig(int signal_no, int job_no, int Table_size);
void TakeInputSig(int *signal_no, int *job_no, String A, char *command);

int CSig(String A)
{
    int signal_no = -1, job_no = -1, ret;
    TakeInputSig(&signal_no, &job_no, A, "sig");
    if(signal_no == -1 || job_no == -1){return -1;}

    int Job_Table_size = Make_Jobs_Table(HashTable, &Job_Table);
    ret = Actualt_Sig(signal_no, job_no, Job_Table_size);
    Clear_Jobs_Table(Job_Table, Job_Table_size);

    return ret;
}


int Actualt_Sig(int signal_no, int job_no, int Table_size)
{
    struct pros_record A;
    int pid, index, check;
    
    index = Index_JobsTable(job_no, Table_size);
    if(index == -1){return -1;}                                     //job_no no longer exits

    A.pid = pid = Job_Table[index].pid;
    if(Search_quad(HashTable, &A) == -1){return -1;}               //job_no no longer exits

    errno = 0;
    check = kill(pid, signal_no);

    if(check == -1)                                             //error handelling
    {
        if(errno == EINVAL)           //Invalid signal number
            fprintf(stderr,"Invalid Signal number is given\n");
        else if(errno == EPERM)
            fprintf(stderr,"Shell does not have permission to send signal %d to %d \n", signal_no, pid);
        else if(errno == ESRCH)
            fprintf(stderr,"The process %d does not exit anylonger\n", pid);
        else
            fprintf(stderr,"some unknown error accored (not mentioned in man)\n");
        
        errno = 0;
        return -1;
    }

    return pid;
}


void TakeInputSig(int *signal_no, int *job_no, String A, char *Command)
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
    *signal_no = Get_int(Token, "sig");
    if(*signal_no == -1){return;}

    
    Token = strtok_r(NULL, " ", &local);
    if(Token != NULL)
        fprintf(stderr,"%s: More arguments are given. These are ignored",Command);

}