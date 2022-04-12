#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "hash.h"
#include "proc.h"




int hash(pros_record A, int Prime)
{
    return A->pid % Prime;
}

int Equal(pros_record A, pros_record B)
{
    return A->pid == B->pid && strcmp(A->Name, B->Name) == 0 && A->status == B->status && A->JobNumber == B->JobNumber;
}


//do not use rehash by keeping the size more.. a large prime number.
void Rehash_increas(Hash_quad* ptrH)
{
    Hash_quad Old = *ptrH;
    Hash_quad New = Init_quad(2*(Old->tableSize));

    for(int i = 0 ; i < Old->tableSize ; i++)
    {
        if(Old->Array[i].condition == filled)
            Insert_quad(&New,Old->Array[i].data);
    }

    Delete_Hash_quad(&Old);
    *ptrH = New;
}

void Insert_quad(Hash_quad* ptrH , pros_record X)
{
    Hash_quad H = *ptrH;
    if(Search_quad(H,X) != -1)
        return;  //already present
    //Elemtent does not exit

    if(H->filled *2 >= H->tableSize)
    {
        Rehash_increas(&H);
        *ptrH = H;
    }
    
    int a = hash(X,H->tableSize);
    int N = H->tableSize,i;
    for(i = 0 ; ;i ++)
    {
        if(H->Array[(a + i*i)%N].condition != filled)
           break; 
    }

    H->Array[(a + i*i)%N].condition = filled;
    cpyProc(&(H->Array[(a + i*i)%N].data) , X);
    H->filled++;
}


void Delete_quad(Hash_quad* ptrH , pros_record X)
{
    Hash_quad H = *ptrH;
    int loc = Search_quad(H,X);

    if(loc == -1)
        return; // the element does not exit

    //The element is present
    H->Array[loc].condition = used; 
    FreeProc(H->Array[loc].data);
    H->filled--;
}


int Search_quad(Hash_quad H , pros_record X)
{
    int a = hash(X,H->tableSize),i;
    int N = H->tableSize, found = 0;

    for(i = 0 ; i < N ; i ++)
    {
        NodeQ present = H->Array[(a+i*i)%N];

        if(present.condition == filled)
            if(present.data->pid == X->pid)
            {
                found = 1;
                break;
            }

        if(present.condition == used)
            continue;
        if(present.condition == unused)
            break;
    }

    if(found == 1)
        return (a+i*i)%N;
    if(found == 0)
        return -1;
}


Hash_quad Init_quad(int N)
{
    Hash_quad H = malloc(sizeof(struct Hash_quad));
    H->tableSize = N;
    H->filled = 0;
    H->Array = malloc(N*sizeof(NodeQ));

    for(int i = 0 ; i < N ; i++)
        H->Array[i].condition = unused;
    
    return H;
}


void Delete_Hash_quad(Hash_quad* ptrH)
{
    Hash_quad H = *ptrH;

    for(int i = 0; i < H->tableSize; i++)
        if(H->Array[i].condition == filled)
            FreeProc(H->Array[i].data);

    free(H->Array);
    free(H);

    *ptrH = NULL;
}