#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "StringB.h"



String String_Create(int Size)
{
    String A = malloc(Size + 1);
    
    if(A == NULL)
    {
        printf("Unable to allocate memory malloc");
        exit(0);
    }
    A[0] = '\0';

    return A;
}


void String_Delete(String A)
{
    free(A);
}


String Space_in_Start_String(String A)
{
    if(A[0] == ' ')
    {
        A = &(A[1]);
        if(A[0] == '\0')
            return NULL;
    }
    
    return A;
}


StringArray StringArray_Create(int Size)
{
    StringArray Ans = malloc(sizeof(String)*Size);

    if(Ans == NULL)
    {
        printf("Malloc not able to allocate memory");
        exit(0);
    }

    for(int i = 0; i < Size; i++)
        Ans[i] = NULL;

    return Ans;
}


void StringArray_Delete(StringArray A, int Size)
{
    for(int i = 0; i < Size; i++)
        free(A[i]);             //Null no work is done
    
    free(A);
}


//make sure index is fine other wise segfault
void StringArray_Add(StringArray A, int At_index, char * What_toPut, int Size)
{
    if(At_index >= Size || At_index < 0 || A[At_index] != NULL)
    {
        printf("Index error please check the index");
        exit(0);
    }

    A[At_index] = String_Create(strlen(What_toPut)); 
    strcpy(A[At_index], What_toPut);
}


int No_of_Words(String A)
{
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return -1;
    
    char* local;
    char* Token = strtok_r(A," ", &local);
    int Ans = 0;

    while(Token != NULL)
    {
        Ans++;
        Token = strtok_r(NULL, " ", &local);
    }
    
    return Ans;
}

//To dete afterwarrds
//Bug fix creat Size + 1  (last one for NULL) last for specific to execvp
//ounly other use case in ls.
StringArray Generate_Format(String A, int Size)
{
    A = Space_in_Start_String(A);
    if(A == NULL)       //if input command is " "
        return NULL;
    

    StringArray Arguments = StringArray_Create(Size + 1);

    int index = 0;
    char* local;
    char* Token = strtok_r(A," ", &local);

    while(Token != NULL)
    {
        StringArray_Add(Arguments, index, Token, Size);
        index++;
        Token = strtok_r(NULL, " ", &local);
    }

    return Arguments;
}