#ifndef __BuiltMangaer
#define __BuiltMangaer

#include "../Data_Abstractions/StringB.h"

//Given command (name + arguments). (may or may not be valid command)
//extra scpace newlines extra are removed.
//See if that is a Built in Command if yes run it. (function call)
// if it is not Give it to System manager. (may or maynot be valid command)
// No returnvalue
void Distributor(String Common);
void Distributor_1(String Common);

//used only for pipe
void ClearString(String Command);  
int OutputStream(String Commad);
int InputStream(String Commad);

#endif