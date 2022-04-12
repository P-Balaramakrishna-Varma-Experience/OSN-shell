#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "Ucd.h"
#include "../Prompt/prompt.h" //for macros
#include "../Data_Abstractions/StringB.h"

extern char HomeDirectory[PathLenght];
void Tohome();
void PrintError();
void CDAct(char *, char *);

void Ccd(String A)
{
    //Initalization for prev dir or - working
    static char PrevDir[PathLenght], NextPrevDir[PathLenght];
    char* E =  getcwd(NextPrevDir, PathLenght);

    static bool firsttime = true;
    if(firsttime == true)
    {
        firsttime = false;
        strcpy(PrevDir, HomeDirectory);
    }



    //checking command + eleminating space
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, "cd") == 0);


    //Takign arguments
    Token = strtok_r(NULL, " ", &local);
    if(Token == NULL)      // No argument
    {
        Tohome();
        return;
    } 
    char Arg[PathLenght];
    strcpy(Arg, Token);

    Token = strtok_r(NULL, " ", &local);
    if(Token != NULL)
    {
        PrintError();
        return;
    }


    //Runing
    CDAct(Arg,PrevDir);
    strcpy(PrevDir, NextPrevDir);
}



void CDAct(char * Path, char *PrevDirectory)
{
    char Temp[PathLenght];

    if(Path[0] == '~')
    {
        strcpy(Temp, HomeDirectory);
        strcat(Temp, &(Path[1]) );
        Path = Temp;
    }

    if(Path[0] == '-')
    {
        strcpy(Temp, PrevDirectory);
        strcat(Temp, &(Path[1]) );
        Path = Temp;
    }

    //convert into this form path.
    int check = chdir(Path);
    if(check == -1)
        printf("cd: unable to chdir(into path) (path does not exist)\n");
}


void Tohome()
{
    int check = chdir(HomeDirectory);
    if(check == -1)
        printf("cd: Unable to cd into home directory\n");
    return;
}


void PrintError()
{
    printf("cd: Expected one argument but recived more than one\n");
}