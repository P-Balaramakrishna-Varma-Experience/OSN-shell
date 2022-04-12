
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Data_Abstractions/StringB.h"

#include "System_M.h"
#include "../System_Commands/Foreground.h"
#include "../System_Commands/background.h"


int IsBackground(String Command)
{
    char *First = strchr(Command, (int)('&'));
    char *Last = strrchr(Command, (int)('&'));
    
    // No & is present
    if(First == NULL)
        return 1;

    if(First != Last)  // case when two or more & exit
    {
        printf("BKSH: \"%s\" has more than one '&', expected only one & at the end\n", Command);
        return -1;
    }
    
    if(strlen(First) > 2)  //first == last somewere in midle
    {
        printf("BKSH: \"%s\" has '&' not in the end expected to be in end\n", Command);
        return -1;
    }

    return 0;
}
// 0-Backgour 1-foregour -1-noground :)
// More than one exit with error, or run with one &.
// Should be present at last.


void Distributor_2(String Command)
{
    int Result = IsBackground(Command);

    if(Result == 0)
        Run_in_background(Command);

    else if(Result == 1)
        Run_In_Foreground(Command);

    else //cannot run in foregourn or background
        return;
}