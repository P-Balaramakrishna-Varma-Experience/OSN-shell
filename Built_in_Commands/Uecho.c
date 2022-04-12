#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Uecho.h"
#include "../Data_Abstractions/StringB.h"

//echo = printf
//no chance of errors here
void Cecho(String A)
{
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, "echo") == 0);

    Token = strtok_r(NULL, " ", &local);
    while (Token != NULL)
    {
        printf("%s ",Token);
        Token = strtok_r(NULL, " ", &local);
    }

    printf("\n");
}