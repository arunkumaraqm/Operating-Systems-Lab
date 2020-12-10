#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
 #include <unistd.h>
/*
 int execlp(const char *path, const char *arg0, ..., NULL);
 
DESCRIPTION
Like all of the exec functions, execlp replaces the calling process image with a new process image. This has the effect of running a new program with the process ID of the calling process. Note that a new process is not started; the new process image simply overlays the original process image. The execlp function is most commonly used to overlay a process image that has been created by a call to the fork function.
path
identifies the location of the new process image within the hierarchical file system (HFS). If the path argument contains a slash (/), it is assumed that either an absolute or a relative pathname has been specified. If the path argument does not contain a slash, the directories specified by the PATH environment variable are searched in an attempt to locate the file.
arg0, ..., NULL
is a variable length list of arguments that are passed to the new process image. Each argument is specified as a null-terminated string, and the list must end with a NULL pointer. The first argument, arg0, is required and must contain the name of the executable file for the new process image. If the new process image is a normal SAS/C main program, the list of arguments will be passed to argv as a pointer to an array of strings. The number of strings in the array is passed to the main() function as argc.
*/
int main(){

	pid_t pid = fork();

	if (pid < 0)
	{
		printf("Failed\n");
		exit(1);
	}

	else if (pid == 0)
	{
		execlp("/bin/ls", "ls", NULL);
		exit(0);
	}

	else
	{
		wait(NULL);

	}
}