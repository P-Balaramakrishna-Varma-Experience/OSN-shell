#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../Data_Abstractions/hash.h"


#include "Singals.h"
extern int Next_leastNUmber;
extern char Foreground_Name[1000];


extern bool Foreground_Runing;
extern int Foregoround_pid;
extern Hash_quad HashTable;

void Child_sig_handler(int a)
{
    int child_status, index, pid_child;
    char Termination[30];
    struct pros_record A, *Hasadd;

    pid_child = waitpid(-1, &child_status, WNOHANG | WUNTRACED);
    if(!pid_child > 0){return;}

    A.pid = pid_child;
    index = Search_quad(HashTable, &A);
    if(index == -1) {return;}
    Hasadd = HashTable->Array[index].data;

    if(WIFSTOPPED(child_status) == true)
    {
        HashTable->Array[index].data->status = stopped_p;
        printf("\nThe process %d %s was send to stoped",Hasadd->pid, Hasadd->Name);
    }
    else 
    {
        if(WIFEXITED(child_status) == true)
        {
            if(WEXITSTATUS(child_status) == 0)
                printf("\nThe process %d %s exited normally",Hasadd->pid, Hasadd->Name);
            else
                printf("\nThe process %d %s ",Hasadd->pid, Hasadd->Name);

            Delete_quad(&HashTable, &A);
        }
        if(WIFEXITED(child_status) == false)
        {
            printf("\nThe process %d %s was aborted",Hasadd->pid, Hasadd->Name);
            Delete_quad(&HashTable, &A);
        }
    }
}

void transfer_ctrlc(int a)
{
    if(Foreground_Runing == false)
        return;
    else 
        kill(Foregoround_pid, SIGINT);
}

void transfer_ctrlz(int a)
{
    if(Foreground_Runing == false)
        return;

    kill(Foregoround_pid, SIGSTOP);
    struct pros_record A;
    A.pid = Foregoround_pid;
    A.status = stopped_p;
    A.JobNumber = Next_leastNUmber;
    Next_leastNUmber++;
    A.Name = Foreground_Name;
    Insert_quad(&HashTable, &A);
}


void Signal_Init_ctrl_c(struct sigaction *Aptr)
{
    (*Aptr).sa_handler = transfer_ctrlc;
    sigemptyset( &((*Aptr).sa_mask) );
    (*Aptr).sa_flags = 0;
}

void Signal_Init_ctrl_z(struct sigaction *Aptr)
{
    (*Aptr).sa_handler = transfer_ctrlz;
    sigemptyset( &((*Aptr).sa_mask) );
    (*Aptr).sa_flags = 0;
}

void Signal_Child(struct sigaction *Aptr)
{
    (*Aptr).sa_handler = Child_sig_handler;
    sigemptyset( &((*Aptr).sa_mask) );
    (*Aptr).sa_flags = 0;
}

