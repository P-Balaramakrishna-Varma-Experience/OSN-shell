#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../Data_Abstractions/StringB.h"
#include "../Prompt/prompt.h" //for macros
#include "Uls.h"

extern char HomeDirectory[PathLenght];


void ClsActual(char* DirPath, int Long, int HIdden);
void PrintStat(struct stat B, int check, char *path, char *FileName);
//long = 0  No long
//HIden = 0 No hidden
//Runs the command the other function is to parse the args

StringArray Get_FileNames(char *DirPath, int Hidden, int no);
int Get_NoofFiles(char* DirPath, int Hidden);
void PrintInLong(StringArray FileNames, int NoFiles, char* Dirpath);
void PrintInShort(StringArray FileNames, int NoFilesh);



void Cls(String Command)
{
    ///**** Debugging mistake
    Command = Space_in_Start_String(Command);
    if(Command == NULL)       //if input command is " "
        return;
    ///****


    //****
    //getting lenght
    String StoreCommand = String_Create(strlen(Command)+2);
    strcpy(StoreCommand, Command);
    int Length = No_of_Words(Command);
    if(Length == -1)
        return;
    strcpy(Command, StoreCommand);

    //getting the arguments
    StringArray Args = Generate_Format(Command, Length);
    strcpy(Command, StoreCommand);
    String_Delete(StoreCommand);
    StringArray ArgsS = Args;
    //****



    int Long = 0, Hidden = 0, opt, No_args = Length; 
    optind = 0;
    opterr = 0;
    while((opt = getopt(No_args, Args, "la")) != -1) 
    { 
        switch(opt) 
        { 
            case 'l': 
                Long = 1;
                break;
            case 'a': 
                Hidden = 1;
                break; 
            case '?': 
                printf("ls: unknown option: %c\n", optopt);
                break;
            default:
                printf("ls :unable to parse\n");
                break;
        } 

    } 
      
    if(optind == No_args)
        ClsActual(".", Long, Hidden);

    for(; optind < No_args; optind++)
    {
        if(Args[optind][0] == '~')
        {
            String Temp = String_Create(PathLenght);

            strcpy(Temp, HomeDirectory);
            strcat(Temp, &(Args[optind][1]) );

            ClsActual(Temp, Long, Hidden);
            String_Delete(Temp);
        }
        else
            ClsActual(Args[optind], Long, Hidden);
    }


    StringArray_Delete(ArgsS, No_args+1);
}



void ClsActual(char* DirPath, int Long, int HIdden)
{
   //printf("%s DirName   %d-long,  %d-hiddne\n",DirPath,Long, HIdden);

   int No_Files = Get_NoofFiles(DirPath, HIdden);
   StringArray File_Names = Get_FileNames(DirPath, HIdden, No_Files);

   if(Long == 0)
        PrintInShort(File_Names, No_Files);
    else
        PrintInLong(File_Names, No_Files, DirPath);

    if(File_Names != NULL)
        StringArray_Delete(File_Names, No_Files);
}


//no error handeling
int Get_NoofFiles(char* DirPath, int Hidden)
{
    DIR* Dir = opendir(DirPath);
    struct dirent *Entry;

   if(Dir == NULL)
    {
        if(errno == ENOTDIR)
            return 1;

        return 100;
    }

    int ans = 0;
    while(( Entry = readdir(Dir) ) != NULL)
    {
        if(Hidden == 1)
            ans++;
        
        if(Hidden == 0)
        {
            if( Entry->d_name[0] != '.' )
                ans++;
        }
    }

    closedir(Dir);
    return ans;
}


StringArray Get_FileNames(char *DirPath, int Hidden, int no)
{
    struct dirent *Entry;
    int i = 0; //index

    StringArray FileNames = StringArray_Create(no);
    DIR* Dir = opendir(DirPath);

    if(Dir == NULL)
    {
        if(errno == ENOTDIR)
        {
            char *lastfslash = strrchr(DirPath, (int)('/'));
            if(lastfslash == NULL)
                lastfslash = DirPath;
            else
                lastfslash++;
            StringArray_Add(FileNames, 0, lastfslash, 1);
            return FileNames;
        }
        StringArray_Delete(FileNames, no);
        printf("Some error opening the path %s\n",DirPath);
        return NULL;
    }

    while(( Entry = readdir(Dir) ) != NULL && i < no)
    {
        if(Hidden == 1)
        {
            StringArray_Add(FileNames, i, Entry->d_name , no);
            i++;
        }
        
        if(Hidden == 0)
        {
            if( Entry->d_name[0] != '.')
            {
                StringArray_Add(FileNames, i, Entry->d_name , no);
                i++;
            }
        }
    }

    closedir(Dir);
    return FileNames;
}

void PrintInShort(StringArray FileNames, int NoFiles)
{
    if(FileNames != NULL)
        for(int i = 0; i < NoFiles; i++)
            printf("%s\n",FileNames[i]);
}


void PrintInLong(StringArray FileNames, int NoFiles, char* Dirpath)
{
    if(FileNames == NULL)
        return;

    struct stat A;
    int check;


    DIR* Test = opendir(Dirpath);
    if(Test == NULL)
    {
        if(errno = ENOTDIR)
        {
            check = stat(Dirpath, &A);
            PrintStat(A, check, Dirpath, FileNames[0]);
        }

        return;
    }
    closedir(Test);

    char Path[PathLenght];
    for(int i = 0; i < NoFiles; i++)
    {
        strcpy(Path, Dirpath);
        strcat(Path, "/");
        strcat(Path, FileNames[i]);
        
        check = stat(Path, &A);
        PrintStat(A, check, Path, FileNames[i]);
    }
}

void PrintStat(struct stat B, int check, char * Path, char *FileName)
{
    if(check == -1)
    {
        perror("");
        printf("Unable to print the file %s\n", Path);
        return;
    }

    if(check == 0)
    {
        printf("%d ", B.st_mode);
        printf("%ld ", B.st_nlink);
        printf("%d ", B.st_uid);
        printf("%d ", B.st_gid);
        printf("%ld ", B.st_size);
        printf("%s\n", FileName );
    }
}