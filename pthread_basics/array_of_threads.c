#include <stdio.h>
#include <stdlib.h>
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

typedef struct MyThread
{
	pthread_t tid;
	int myid;
} MyThread;

void* my_function(void* given_thr)
{
	MyThread* thr = (MyThread*) given_thr;

	// If myid = 1, there is a 3 second delay in that thread.
	sleep(4 - thr->myid);
	printf("Inside thread. tid = %d, myid = %d\n",
			thr->tid, thr->myid
			);
	return NULL;
}

void main()
{
	MyThread threads[3];
	printf("Before threads are created.\n");
	
	for (int i = 0; i < 3; ++i)
	{
		threads[i].myid = i;
		int failure = pthread_create(
			&threads[i].tid, NULL, 
			my_function, (void*) &threads[i]
			);	
		if (failure)
		{
			fprintf(stderr, "Create Failure\n");
			exit(1);
		}
	}

	sleep(3);
	printf("Before joining.\n");

	for (int i = 0; i < 3; ++i)
	{
		int failure = pthread_join(
			threads[i].tid, NULL
			);	
		if (failure)
		{
			fprintf(stderr, "Join Failure\n");
			exit(1);
		}
	}
	printf("After threads complete.\n"); 
}
/*
Out #1:
Before threads are created.
Inside thread. tid = 296656, myid = 2
Inside thread. tid = 296400, myid = 1
Before joining.
Inside thread. tid = 296144, myid = 0
After threads complete.

Out #2:
Before threads are created.
Inside thread. tid = 296656, myid = 2
Before joining.
Inside thread. tid = 296400, myid = 1
Inside thread. tid = 296144, myid = 0
After threads complete.
*/

/*
code from w3schools
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_exit(NULL);
}

int main () {
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;
   
   for( i = 0; i < NUM_THREADS; i++ ) {
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
      
      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
*/