#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "PipeM.h"
#include "Built_M.h"
#include "../Data_Abstractions/StringB.h"
#include "../Data_Abstractions/IOstreams.h"

extern IOstreams Global;

void Swap(int **A, int **B);
void StdPipe(int **A);


void PipedCommand(String A)
{
    //potential error in between execution. //ignore
    //potetial error in system calls.
    //new for last should be stdoutput
    String Sub_Command, Store_Tofree;
    Sub_Command = String_Create(strlen(A));
    Store_Tofree = Sub_Command;
    char *local = A, *Token;
    Token = strtok_r(A, "|", &local);
    strcpy(Sub_Command, Token);



    int Aa[2], B[2];
    int *New = B, *Old = Aa;
    StdPipe(&Old);

    //create new pipe. Closes and existing pipe.
    //Write to new pipe. Reads from old pipe.
    bool FirstRun = true;
    while(Sub_Command != NULL)
    {
        char *Next_Token = strtok_r(NULL, "|", &local);
        pipe(New);        //so that child can write
        close(Old[1]);  //so that the child can read.

        int id = fork();
        if(id > 0)
        {
            waitpid(id, NULL, 0);
            close(Old[0]);

            Swap(&Old, &New);
            FirstRun = false;
            if(Next_Token != NULL)
                strcpy(Sub_Command, Next_Token);
            else
                Sub_Command = NULL;
        }
        if(id == 0)
        {
            dup2(Old[0], 0);  //stdinput is the olpine read end.
            dup2(New[1], 1);  //stdout is new pipe write end.

            if(Next_Token == NULL)
            {
                dup2(Global.Output, 1);
                int Outputfd = OutputStream(Sub_Command);
                if(Outputfd != -1)            
                    dup2(Outputfd, 1);
            }
            if(FirstRun == true)
            {
                int Inputfd = InputStream(Sub_Command);
                if(Inputfd != -1)
                    dup2(Inputfd, 0);
            }

            ClearString(Sub_Command);
            Distributor_1(Sub_Command);
            exit(0);
        }
    }

    close(Old[1]); 
    close(Old[0]);
    String_Delete(Store_Tofree);
}


void Swap(int **A, int **B)
{
    int *C;
    C = *A;
    *A = *B;
    *B = C;
}

void StdPipe(int **A)
{
    (*A)[0] = dup(Global.Input);
    (*A)[1] = dup(Global.Output);
}