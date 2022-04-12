#include <stdio.h>
#include <string.h>
#include "unistd.h"
#include <assert.h>

#include "../Data_Abstractions/StringB.h"
#include "../Prompt/prompt.h" //for micros
#include "Upwd.h"

void Cpwd(String A)
{
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, "pwd") == 0);

    //Checking if pwd has no arguments
    Token = strtok_r(NULL, " ", &local);
    if(Token != NULL)   //pwd has arguments
    {
        printf("pwd: supposed to have no arguments but argument found \"%s\"\n",Token);
        return;
    }

    char PeresentDir[PathLenght];
    char *ErrorCheck = getcwd(PeresentDir, PathLenght);
    if(ErrorCheck == NULL)
        printf("Unable to get pwd getcwd not working");
    else
        printf("%s\n",PeresentDir);
}