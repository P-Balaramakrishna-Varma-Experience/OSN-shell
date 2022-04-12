#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include "../Data_Abstractions/StringB.h"
#include "../Managers/Built_M.h"

#include "input.h"

char *ReadLine(void);
String SpaceSeparated(char* String);



String Take_User_Input(void)
{
    char *Line = ReadLine();
    if(Line == NULL)
        return NULL;
    String Ans = SpaceSeparated(Line);
    free(Line);
    return Ans;
}


char *ReadLine(void)
{
    size_t n = 0;
    char *lineptr = NULL;
    int a = getline(&lineptr, &n, stdin);    

    char Buf[2];
    if( a == -1 )
    {
        if(errno == EINTR) //ctrlc + ctrlz
        {
            clearerr(stdin);
            printf("\n");
            lineptr == NULL;
            errno = 0;
        }
        else if(feof(stdin) != 0)  //When ctrl + D
        {
           printf("\n");
           Distributor_1("exit");  //termination.
        }
        else
        {
            printf("Cannot Take input for user getline error");
            exit(0);
        }
    }

    return lineptr;
}


String SpaceSeparated(char* line)
{
    String Input = String_Create(strlen(line));
    char *Token;

    Token = strtok(line, "\n\t ");

    while (Token != NULL)
    {
        strcat(Input, Token);
        strcat(Input, " ");
        Token = strtok(NULL, "\n\t ");
    }
    
    return Input;
}