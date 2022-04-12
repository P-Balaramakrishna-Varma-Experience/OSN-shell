## Signals

* The code for all the signals are present in signals.h
* The handlers are initialized in the main.c
* clearerr() is used to remove the fags set by getline on input stream.

### ctrl + c, ctrl + z 
* Sigaction is used over-witting the default handler for **SIGINT**, **SIGSTP**.
* Global variables **Foreground_running** and **Foreground_pid** are used. 
* The basically send the same signal to the Foreground process if any else do nothing.
* The code for storing the stopped process is handled by the handler for **SIGCHILD**.

### ctrl + d
* End of file is detected by feof(stdin).
* In the case of EOF detection the shell program is exited. //to work
* Code for this is written in *Input.c*. In the function *ReadLine*

---

## Jobs and related.
* **bg** all we do is run the implemented command **sig**. Arguments for *sig* being *SIGCONT* and *JobNumber* passed to *bg*. We then update the status of the process to *running* in hash table.
* **fg** we do similar to **bg** and then *wait* on the process corresponding to the jobNumber given to *fg*. And deleting its entry from hash table.

* The background process are stored in a global hash table. When a background process is created it is added to the hash table. We also book keep whether each process's state running or stopped. The entity is deleted when a background process is terminated.
* We assign a number to each background process when we fork them.
* We create a array of current valid background process sorted alphabetically with their command names at the invocation of **jobs** or **sig** and delete it after completion.
* The implementation of **jobs** and **sig** is trivial in this setup.
* The code for **fg, bg, sig, jobs** are present in *Built_in_Commands* directory. One header file for all and one code file for each.
* The code for **hash table** **Job Table** is present in *Data_Abstractions* directory. One header and code file each.
* Some abstractions/functions needed for more than part is stored in *jobsimilar.c*

---

## Input Output redirection
### Simple < >, >> redirection.
* The entire code related to is in the *Built_M.c* which is in *Managers* Directory.
* We take the filenames and open them with appropriate arguments.
* Before calling the *Distributor_1* We just **dup2** the file descriptors we have opened for **0, 1**.
* After finishing of execution we restore **stdin and stdout** in **0, 1**.

### Pipe without redirection.
* The entire code is present in *pipe.c* which is in *Managers* Directory.
* We create two intermediary pipes logically equal to files.
* For each sub_command we fork (make parent wait and child execute).
* For the child we change **0, 1** file descriptors with the pipes using **dup2**.
* Pipe is not designed to handle &.
* Much error checking is not for the following reasons.
  * There a lot of system in a span of 20-30 lines. Checking error for each sys call will confuse and make the code unmanageable.
  * Error correction when one of the sub command fails is not done because doing it have a change a lot code. Which might cause more bugs. Considering all that to be the part of previous assingment they are not done.

### Pipe with redirection.
* The entire code is present in *pipe.c* which is in *Managers* Directory.
* All we have to do is in while executing the first sub_command apply simple input redirection.
* In the last sub_command apply standard output redirection.
* Any where else is an error. It is simply ignored.
 
---