#ifndef _Singal_H
#define _Signal_H

#include <signal.h>

void Signal_Init_ctrl_c(struct sigaction *A);
void Signal_Init_ctrl_z(struct sigaction *A);
void Signal_Child(struct sigaction *A);

void transfer_ctrlc(int a);
void transfer_ctrlz(int a);
void Child_sig_handler(int a);

#endif