#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../Data_Abstractions/StringB.h"
#include "Urepeat.h"
#include "../Managers/Built_M.h"

int Get_Int_Repeat(char *);

void Crepeat(String A)
{
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, "repeat") == 0);


    //Taking the number (number might be misssing) (number might be less or equal to 0)
    Token = strtok_r(NULL, " ", &local);
    int n = Get_Int_Repeat(Token);
    if(n == -1){return;}

    //Runing the Next command n times
    String Instruction = String_Create(strlen(A));
    int x = strlen("repeat") + 1 + strlen(Token) + 1;

    for(int i = 0; i < n ; i++)
    {
       strcpy(Instruction, &(A[x]) );
       Distributor(Instruction);
    } 

    String_Delete(Instruction);
}


int Get_Int_Repeat(char * Token)
{
    if(Token == NULL)
        return -1;

    char *endptr = NULL;
    int n = (int)strtol(Token, &endptr , 10);

    if(strlen(endptr) != 0)
    {
        printf("repeat: Error first agr is not a number \n");
        return -1;
    }

    if(n <= 0)
    {
    printf("repeat: It does not make sense to run the command \"%d\" times\n",n);
        return -1;
    }
    return n;
}