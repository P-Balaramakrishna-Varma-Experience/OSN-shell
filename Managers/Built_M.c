#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "Built_M.h"
#include "../Data_Abstractions/StringB.h"
#include "../Data_Abstractions/IOstreams.h"

// Including 7 Builit in commands headers. 1 system manager header.
// Not included Built M.h because it can be written independent of these. 
#include "../Built_in_Commands/pinfo.h"
#include "../Built_in_Commands/Ucd.h"
#include "../Built_in_Commands/Uecho.h"
#include "../Built_in_Commands/Uls.h"
#include "../Built_in_Commands/Upwd.h"
#include "../Built_in_Commands/Urepeat.h"
#include "../Built_in_Commands/Uexit.h"
#include "../Built_in_Commands/jobssimilar.h"
#include "System_M.h"

extern IOstreams Global;
String Extract_CommandName(String Command);
void Distributor_1(String Command);

//0 fine  -1 error
int OpenIOstreams(String Commad, IOstreams* A);
int InputStream(String Commad);
int OutputStream(String Commad);
void ClearString(String Command);



void Distributor(String Common)
{
    int error;
    IOstreams ToBe;

    error = OpenIOstreams(Common, &ToBe);
    if(error == -1)
    {
        printf("Unable to open files. Check if syntax is correct. Or if the file does not exits\n");
        return;
    }

    error = ChangeIOstreams(ToBe);
    if(error == 0)
        Distributor_1(Common);

    error = ChangeIOstreams(Global);
    if(error == -1)
    {
        printf("critical error io\n");
        exit(0);
    }
}

void Distributor_1(String Command)
{
    //get the first name
    String Command_Name = Extract_CommandName(Command);

    if(strcmp(Command_Name, "pinfo") == 0)
        Cpinfo(Command);

    else if(strcmp(Command_Name, "cd") == 0)
        Ccd(Command);

    else if(strcmp(Command_Name, "echo") == 0)
        Cecho(Command);

    else if(strcmp(Command_Name, "ls") == 0)
        Cls(Command);

    else if(strcmp(Command_Name, "pwd") == 0)
        Cpwd(Command);

    else if(strcmp(Command_Name, "repeat") == 0)
        Crepeat(Command);

    else if(strcmp(Command_Name, "exit") == 0)
        Cexit(Command);

    else if(strcmp(Command_Name, "jobs") == 0)
        CJobs(Command);
    
    else if(strcmp(Command_Name, "sig") == 0)
        CSig(Command);

     else if(strcmp(Command_Name, "bg") == 0)
        Cbg(Command);

    else if(strcmp(Command_Name, "fg") == 0)
        Cfg(Command);

    else //give to Distributor 2;;
        Distributor_2(Command);
    
    String_Delete(Command_Name);
}

String Extract_CommandName(String Command)
{
    String Ans = String_Create(strlen(Command));
    if(Command[0] == ' ')                            //bug fix (when strok on compresed input) space after colon and before command;leading to foreground execution
        Command = &Command[1];

    strcpy(Ans, Command);

    char* A = strchr(Command, (int)(' '));
    int index;
    
    if(A != NULL)
    {
        index = A - Command;
        Ans[index] = '\0';
        return Ans;
    }
    else // A == NULL // single word asnwer = Command
        return Ans;
}

void ClearString(String Command)
{
    char *A = strchr(Command, (int)('<'));
    char *B = strchr(Command, (int)('>'));
    char *First;

    if(A != NULL && B != NULL)
        First = A < B ? A : B;
    else if(A == NULL && B != NULL)
        First = B;
    else if(A != NULL & B ==  NULL)
        First = A;
    else
        return;
    
    if(strchr(Command, (int)('&')) == NULL)
        *First = '\0';
    else
    {
        *First = '&';
        First++;
        *First = '\0';
    }
}

int OpenIOstreams(String Command, IOstreams* A)
{
    A->Input = InputStream(Command);
    A->Output = OutputStream(Command);
    ClearString(Command);

    if(A->Input < 0 || A->Output < 0)
        return -1;
}

int InputStream(String Commad)
{
    String (*Get_First_Word)(String) = &Extract_CommandName;
    char A[2] = {'\0'};
    String fileName = A;

    int InputStream = 0;
    char *Loc = strchr(Commad, (int)('<'));
    if(Loc != NULL)
    {
        Loc++;
        if(Loc != NULL)
            fileName = (*Get_First_Word)(Loc);
    }


    if(fileName[0] != '\0')
        InputStream = open(fileName, O_RDONLY);

    return InputStream;
}

int OutputStream(String Commad)
{
    String (*Get_First_Word)(String) = &Extract_CommandName;
    char A[2] = {'\0'};
    String fileName = A;

    int OutputStream = 1, Append = -1, len;
    char *Loc = strchr(Commad, (int)('>'));
    if(Loc != NULL)
    {
        if(strlen(Loc) > 1 && *(Loc + 1) == '>')
        {
            Loc++;
            Append = 1;
        }

        Loc++;
        if(Loc != NULL)
            fileName = (*Get_First_Word)(Loc);
    }
    
    if(fileName[0] != '\0')
    {
        if(Append == -1)
            OutputStream = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if(Append == 1)
            OutputStream = open(fileName, O_WRONLY | O_CREAT, 0666);

        if(OutputStream < 0)
            return -1;

        if(Append == 1)
            lseek(OutputStream, 0, SEEK_END);
    }
        
    return OutputStream;
}
