#include <stdio.h>
#include <unistd.h>
#include <pthread.h> // use -lpthread
/*
int pthread_create(
	pthread_t *thread, 
	const pthread_attr_t *attr, // default args will be chosen if null
	void *(*start_routine) (void *),
	void *arg
	);

The pthread_create() function starts a new thread in the calling
process.  The new thread starts execution by invoking
start_routine(); arg is passed as the sole argument of
start_routine().

The new thread terminates in one of the following ways:

* It calls pthread_exit(3), specifying an exit status value that is
 available to another thread in the same process that calls
 pthread_join(3).

* It returns from start_routine().  This is equivalent to calling
 pthread_exit(3) with the value supplied in the return statement.

* It is canceled (see pthread_cancel(3)).

* Any of the threads in the process calls exit(3), or the main thread
 performs a return from main().  This causes the termination of all
 threads in the process.
*/
/*
int pthread_join(
	pthread_t thread, 
	void **retval
	);

The pthread_join() function waits for the thread specified by thread
to terminate.  If that thread has already terminated, then
pthread_join() returns immediately.  The thread specified by thread
must be joinable.

If retval is not NULL, then pthread_join() copies the exit status of
the target thread (i.e., the value that the target thread supplied to
pthread_exit(3)) into the location pointed to by retval.  If the
target thread was canceled, then PTHREAD_CANCELED is placed in the
location pointed to by retval.

If multiple threads simultaneously try to join with the same thread,
the results are undefined.  If the thread calling pthread_join() is
canceled, then the target thread will remain joinable (i.e., it will
not be detached).
*/

void* my_function(void* arg)
{
	sleep(1);
	printf("Printing from my_function\n");
	return NULL;
}

void main()
{
	pthread_t thread_id;
	printf("before thread\n");
	
	pthread_create(
		&thread_id, NULL, my_function, NULL
		);		
	pthread_join(
		thread_id, NULL
		);

	printf("after thread\n");


}

/*
Out:
before thread
Printing from my_function
after thread
*/