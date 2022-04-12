#include "IOstreams.h"
#include <unistd.h>


int ChangeIOstreams(IOstreams A)
{
    int a = dup2(A.Input, 0);
    int b = dup2(A.Output, 1); 

    if(a*b < 0)
        return -1;
    else
        return 0;
}

void InitalizeGlobal(IOstreams* A)
{
    A->Input = dup(0);
    A->Output = dup(1);
}

