#ifndef proc_H
#define proc_H

#include <stdbool.h>
enum STATUS_pros {running_p, stopped_p};
typedef enum STATUS_pros STATUS_pros;

struct pros_record
{
    int pid;
    char* Name;
    STATUS_pros status; 
    int JobNumber;
};
typedef struct pros_record* pros_record;

void cpyProc(pros_record *A, pros_record B);
void FreeProc(pros_record A);
pros_record InitProc(int pid, char * Command, STATUS_pros s, bool First);

#endif