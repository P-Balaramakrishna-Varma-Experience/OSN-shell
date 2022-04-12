#ifndef _String_HB
#define _Stirng_HB



typedef char* String;
typedef char** StringArray;
//String Data type is an array.!! pointer to first element in char array

String String_Create(int Size);
//Creates a array of size Size + 1

void String_Delete(String A);
//Only frees the memory leaving a dangling pointer.

String Space_in_Start_String(String A);
//removes any starting space if any otherwis returns A.

StringArray StringArray_Create(int Size);
//Creates an array size=Size of poites to strings 

void StringArray_Delete(StringArray A, int Size);
//Deltes the stringArray A form memory

void StringArray_Add(StringArray A, int At_index, char * What_toPut, int Size);

StringArray Generate_Format(String Command, int Size);
//creates a array of null terminated pointers for Command given its Size.
//to be deleted later.

int No_of_Words(String Command);
//Return number of words in Commads

#endif