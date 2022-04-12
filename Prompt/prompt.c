#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "prompt.h"


void Get_UserName(char *Here);
void Get_SystemName(char *Here);
char* Get_Pwd(char *DirPath, char *Homedirectory);


void Init_Homedirectory(char *A)
{
    char* a = getcwd(A, PathLenght);
    if(a == NULL)
    {
        printf("Unable to get home directory\n");
        exit(0);
    }
}


void Print_Prompt(char *HomeDirectory)
{
    // "<username@systemnam:curr-Dir> "
    char DirPath[PathLenght], SystemName[MAXhostName], UserName[MAXUserName];

    Get_UserName(UserName);
    Get_SystemName(SystemName); 
    char *CurrDir = Get_Pwd(DirPath, HomeDirectory);
        
    printf("<%s@%s:%s> ",UserName, SystemName, CurrDir);
}




void Get_UserName(char *Here)
{
    char* User_Name = getenv("USER");

    if(User_Name != NULL)
        strcpy(Here, User_Name);
    else
    {
        printf("Unable take user name from evironment variables\n");
        exit(0);
    }

}


void Get_SystemName(char *Here)
{
    int ErrorCheck = gethostname(Here, MAXhostName);
    
    if(ErrorCheck < 0)
    {
        printf("unambe get get hostname\n");
        exit(0);
    }
}


char* Get_Pwd(char *DirPath, char *HomeDirectory)
{
    char* Ans;
    char* ErrorCheck = getcwd(DirPath, PathLenght);

    if(ErrorCheck == NULL)
    {
        printf("Unable to do getcwd systemcall");
        exit(0);
    }


    char* A = strstr(DirPath, HomeDirectory);
    
    if(A == NULL)
        Ans = DirPath;
    else
    {
        DirPath[strlen(HomeDirectory) - 1] = '~';
        Ans = &(DirPath[strlen(HomeDirectory) - 1]);
    }
        
    return Ans;
}