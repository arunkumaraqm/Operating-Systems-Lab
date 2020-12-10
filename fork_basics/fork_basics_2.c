#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // for fork, getpid, getpid
#include <sys/wait.h> // for wait

void print_par_chi(pid_t par, pid_t chi)
{
	printf("(parent, child) = (%d, %d)\n", par, chi);
    fflush(stdout);
}

char names[3][50] = {"parent_Bob", "child_Derek", "grandchild_John"};

int foo(char parent_name[50], char child_name[50])
{
	static int noof_times_this_func_is_called = 0;
	noof_times_this_func_is_called++;

	pid_t pid;
	int temp = 2;
	/*
		fork returns
		negative value: creation of child not successful
		zero: newly created child
		positive: parent; value is pid of child
	*/
	pid = fork();
	if (pid < 0)
	{
		printf("Error.\n");
    	fflush(stdout);
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
		printf("Inside if: Hello from %s. My pid is %d and my child, %s's pid is %d.\n", 
			    parent_name, mypid, child_name, mychildspid);
	    fflush(stdout);

	}
	else
	{
		pid_t mypid = getpid(), myparentspid = getppid();
		printf("Inside else: Hello from %s. My pid is %d and my parent, %s's pid is %d.\n", 
			    child_name, mypid, parent_name, myparentspid);
	    fflush(stdout);

		if (noof_times_this_func_is_called == 1)
		{
			int ret = foo(names[1], names[2]);
			if (ret == 1) return 1;
		}
	}

	return 0;
	
}

int main()
{
	int ret = foo(names[0], names[1]);
	if (ret == 1) return 1;
	return 0;
}

