#ifndef Hash_H
#define Hash_H

#include "proc.h"
typedef enum state state;
enum state{filled,used,unused};

typedef struct NodeQ NodeQ;
typedef NodeQ* PtrNodeQ;
struct NodeQ
{
    pros_record data;
    state condition;
};

typedef struct Hash_quad* Hash_quad; 
struct Hash_quad
{
    int tableSize;
    PtrNodeQ Array;
    int filled;
};


void Insert_quad(Hash_quad* ptrH , pros_record X);
void Delete_quad(Hash_quad* ptrH , pros_record X);
int Search_quad(Hash_quad H , pros_record X);

Hash_quad Init_quad(int N);
void Delete_Hash_quad(Hash_quad* ptrH);
void Print_Hash_quad(Hash_quad H);

#endif