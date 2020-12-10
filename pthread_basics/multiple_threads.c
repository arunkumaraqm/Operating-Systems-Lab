#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
/*
int pthread_create(
	pthread_t *thread, 
	const pthread_attr_t *attr, 
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

void* small_delay_1(void* arg)
{
	sleep(1);
	printf("After small delay #1.\n");
	return NULL;
}

void* small_delay_2(void* arg)
{
	sleep(1);
	printf("After small delay #2.\n");
	return NULL;
}

void* large_delay_1(void* arg)
{
	sleep(2);
	printf("After large delay #1.\n");
	return NULL;
}


void main()
{
	pthread_t tid1, tid2;
	printf("before threads round 1\n");
	
	pthread_create(
		&tid1, NULL, small_delay_1, NULL
		);		
	pthread_create(
		&tid2, NULL, small_delay_2, NULL
		);		
	pthread_join(
		tid1, NULL
		);
	pthread_join(
		tid2, NULL
		);

	printf("after threads round 1\n");

	printf("before threads round 2\n");
	
	pthread_create(
		&tid1, NULL, large_delay_1, NULL
		);		
	pthread_create(
		&tid2, NULL, small_delay_2, NULL
		);		
	pthread_join(
		tid1, NULL
		);
	pthread_join(
		tid2, NULL
		);

	printf("after threads round 2\n");


}
/*
out:
before threads round 1
After small delay #2.
After small delay #1.
after threads round 1
before threads round 2
After small delay #2.
After large delay #1.
after threads round 2
*/
