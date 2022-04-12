#ifndef __JOBTables_H
#define __JOBTables_H

#include "hash.h"
#include "proc.h"

int Make_Jobs_Table(Hash_quad H, struct pros_record** Table_Ans);
void Clear_Jobs_Table(struct pros_record* A, int size);

#endif