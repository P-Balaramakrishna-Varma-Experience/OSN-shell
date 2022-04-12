#ifndef __Jobs_H
#define __JObs_H

#include "../Data_Abstractions/StringB.h"
struct pros_record *Job_Table;

void CJobs(String A);
int  CSig(String A);
void Cfg(String A);
void Cbg(String A);

int Index_JobsTable(int JobNumber, int Size);
int Get_int(char *Token, char * CommName);
void TakeInputFgBg(int *job_no, String A, char *Command);
int SignalContinue(int JobNumber);
#endif