#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "../Data_Abstractions/StringB.h"
#include "pinfo.h"
#include "../Data_Abstractions/hash.h"

extern Hash_quad HashTable;

void Cexit(String A)
{
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return;
    
    char* local = A;
    char *Token = strtok_r(A, " ", &local);
    assert(strcmp(Token, "exit") == 0);

    
    //This while testing
    Delete_Hash_quad(&HashTable);
//    Cpinfo("pinfo");
    exit(0);
}
