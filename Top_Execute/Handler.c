#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Data_Abstractions/StringB.h"
#include "../Managers/Built_M.h"
#include "../Managers/System_M.h"
#include "../Managers/PipeM.h"

#include "Handler.h"


void MM(String Input)
{
    if(strlen(Input) == 0)  // when user press enter without a command
        return;

    String Temp = String_Create(strlen(Input));
    char *Token;

    Token = strtok(Input, ";");
    while (Token != NULL)
    {
        if(strlen(Token) == 0)
            continue;

        strcpy(Temp, Token);

        if(strchr(Temp, (int)('|')) == NULL)
            Distributor(Temp);
        else
            PipedCommand(Temp);

        Token = strtok(NULL, ";");
    }
    
    String_Delete(Temp);
    String_Delete(Input);
}