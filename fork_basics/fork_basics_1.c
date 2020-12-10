
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // for fork, getpid, getpid
#include <sys/wait.h> // for wait

void print_par_chi(pid_t par, pid_t chi)
{
	printf("(parent, child) = (%d, %d)\n", par, chi);
}

int main()
{
	pid_t pid;
	int temp = 2;
	/*
		fork returns
		negative value: creation of child not successful
		zero: newly created child
		positive: parent; value is pid of child
	*/
	printf("Before the fork call line.\n");
	pid = fork();
	if (pid < 0)
	{
		printf("Error.\n");
		return 1;
	}

	bool is_parent = pid;
	if (is_parent)
	{
		// If you skip the wait,
		// do not depend on the parent executing before the child. 
		// Doesn't always happen.
		wait(NULL); // Waits for child to terminate
		
		pid_t mypid = getpid(), mychildspid = pid;
		printf("Hello from the parent. My pid is %d and my child's pid is %d.\n", mypid, mychildspid);
	}
	else
	{
		pid_t mypid = getpid(), myparentspid = getppid();
		printf("Hello from the child. My pid is %d and my parent's pid is %d.\n", mypid, myparentspid);
	}
	
}

