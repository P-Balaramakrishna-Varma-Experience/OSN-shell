#ifndef _Foreground_H
#define _Foreground_H

#include "../Data_Abstractions/StringB.h"
//Tries to run Coommand foreground
//Command is granted to not be a builiting command.
//Command can be invalid Command. (cannot be run)
void Run_In_Foreground(String Command);

#endif