#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>

#include "pinfo.h"
#include "../Prompt/prompt.h"
#include "../Data_Abstractions/StringB.h"

struct ProcessInfo
{
    pid_t pid;
    char Process_Status[10];
    long Memory;
    char Executeable_Path[PathLenght];
    char Dirlocation[30];
    FILE* File;

};
typedef struct ProcessInfo ProcessInfo;


int GetNumber_pinfo(char *);
//Read word for number

void Print_Pinfo(ProcessInfo* P);
//Prints the output as specified in doc

int Initalize(ProcessInfo* P, int pid);
//Returns -1 if the file does not open

int Read_file(ProcessInfo* P);
int Read_ExePath(ProcessInfo *P);



void Cpinfo(String A)
{
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, "pinfo") == 0);

    ProcessInfo P_Process;
    Token = strtok_r(NULL, " ", &local);

    //Only Token is need forfurther work
    int ProcessID = GetNumber_pinfo(Token);
    if(ProcessID == -1){return;}

    int Check = Initalize(&P_Process, ProcessID);
    if(Check == -1){return;}


    //Only thing need  from here on is the struct.
    Check = Read_ExePath(&P_Process);
    Check += Read_file(&P_Process);
    if(Check != 0){return;}

    Print_Pinfo(&P_Process);
}


int Initalize(ProcessInfo* P, int pid)
{
    P->pid = pid;

    char Num[10];
    strcpy(P->Dirlocation,"/proc/");
    sprintf(Num, "%d", P->pid);
    strcat(P->Dirlocation, Num);

    char fileloc[40];
    strcpy(fileloc, P->Dirlocation);
    strcat(fileloc,"/status");
    P->File = fopen(fileloc, "r");

    //Check for correctness of pid.
    if(P->File == NULL)
    { 
        printf("%s\n",fileloc);
        printf("pinfo: cannot open the process inof (wrong process Id or not sufficiant permission)\n");
        return -1;
    }

    return 0;
}


int GetNumber_pinfo(char *Token)
{
    if(Token != NULL)
    {
        char *endptr = NULL;
        int n = (int)strtol(Token, &endptr , 10);

        if(strlen(endptr) != 0)
        {
            printf("%s ",Token);
            printf("pinfo: first agr is not a number \n");
            return -1;
        }
        if(n <= 0)
        {
            printf("pinfo: pid should be positeve u have entered invalid pid  \"%d\" \n",n);
            return -1;
        }
        
        return n;
    }
    else //Token == NULL
        return getpid();
}

void Print_Pinfo(ProcessInfo* P)
{
    printf("pid -- %d\n", P->pid);
    printf("Process Status -- %s\n", P->Process_Status);
    printf("memory -- %ld\n", P->Memory);
    printf("Executable Path -- %s\n",P->Executeable_Path);
}

int Read_ExePath(ProcessInfo *P)
{
    //Generating path to symbolic link
    char Path[PathLenght];
    strcpy(Path, P->Dirlocation);
    strcat(Path, "/exe");

    //Reading symbolic link and erro handeling
    int read = readlink(Path,P->Executeable_Path, PathLenght);
    if(read == -1)
    {
        printf("Pinfo: Unable to open %s\n",Path);
        return -1;
    }

    //writting the read to string formtat.
    P->Executeable_Path[read] = '\0';
    return 0;
}


int Read_file(ProcessInfo* P)
{
    int lenght;
    size_t len = 0;
    char *bufptr = NULL, *Token1, *Token2, *local;
    int VMsize, Status = -1;

    lenght = getline(&bufptr, &len, P->File);
    while (lenght >= 0)
    {
        local = bufptr;
        Token1 = strtok_r(bufptr, "\t :(\n", &local);
        Token2 = strtok_r(NULL, "\t :(\n", &local);
        
        if(strcmp(Token1, "State") == 0)
        {
            strcpy(P->Process_Status, Token2);
            Status = 0;
        }

        if(strcmp(Token1, "VmSize") == 0)
        {
            P->Memory = strtol(Token2, NULL, 10);
            VMsize = 0;
        }

        lenght = getline(&bufptr, &len, P->File);
    }


    free(bufptr);
    fclose(P->File);
    if(VMsize + Status == 0)
        return 0;
    else
    {
        printf("pinfo: uanble to fine VmSize and Status\n");
        return -1;
    }
}