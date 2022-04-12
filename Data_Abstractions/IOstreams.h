#ifndef __IOstreams_H
#define __IOstreams_H

#include <stdbool.h>

struct IOstreams
{
    int Input;
    int Output;
};
typedef struct IOstreams IOstreams;

IOstreams Global;

//0 fine openeing
//-1 error in opening.

int ChangeIOstreams(IOstreams A);
void InitalizeGlobal(IOstreams* A);

#endif