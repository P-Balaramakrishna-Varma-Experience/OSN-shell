#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

#include "../Data_Abstractions/hash.h"
#include "../Data_Abstractions/Jobtables.h"
#include "../Data_Abstractions/proc.h"
#include "../Data_Abstractions/StringB.h"

extern struct pros_record *Job_Table;
extern Hash_quad HashTable;


void GetInput_Cjobs(bool *Running, bool *Stopped, String Command);
void PrintJob(pros_record job);


void CJobs(String A)
{
    bool Running, Stopped;
    GetInput_Cjobs(&Running, &Stopped, A);

    int Job_Table_size = Make_Jobs_Table(HashTable, &Job_Table);
    for(int i = 0; i < Job_Table_size; i++)
    {
        if(Job_Table[i].status == running_p && Running == true)
            PrintJob(&Job_Table[i]);

        if(Job_Table[i].status == stopped_p && Stopped == true)
            PrintJob(&Job_Table[i]);
    }
    Clear_Jobs_Table(Job_Table, Job_Table_size);
}

void PrintJob(pros_record job)
{
    char status[20];
    if(job->status == running_p)
        strcpy(status, "Running");
    else
        strcpy(status, "Stopped");

    printf("[%d] %s %s [%d]\n",job->JobNumber, status, job->Name, job->pid);
}


void GetInput_Cjobs(bool *Running, bool *Stopped, String Command)
{
    Command = Space_in_Start_String(Command);
    if(Command == NULL)       //if input command is " "
        return;

    //getting lenght
    String StoreCommand = String_Create(strlen(Command) + 2);
    strcpy(StoreCommand, Command);
    int Length = No_of_Words(Command);
    if(Length == -1)
        return;
    strcpy(Command, StoreCommand);

    //getting the arguments
    StringArray Args = Generate_Format(Command, Length);
    strcpy(Command, StoreCommand);
    String_Delete(StoreCommand);


    int Long = 0, Hidden = 0, opt, No_args = Length; 
    optind = 0;
    opterr = 0;
    while((opt = getopt(No_args, Args, "rs")) != -1) 
    { 
        switch(opt) 
        { 
            case 'r': 
                *Running = true;
                break;
            case 's': 
                *Stopped = true;
                break; 
            case '?': 
                fprintf(stderr,"jobs: unknown option: %c\n", optopt);
                break;
        } 

    } 
    if(optind != No_args)
        fprintf(stderr,"Extra arguments provided which are ignored\n");

    if(*Running == false && *Stopped == false) //no valid flags given
        *Running = *Stopped = true;
}