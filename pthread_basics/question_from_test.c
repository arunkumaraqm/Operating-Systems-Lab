// which will print first, Sanfoundry or Linux?
#include <stdio.h>
#include <pthread.h>

void *fun_t(void* arg)
{
	printf("Sanfoundry\n");
	pthread_exit("bye");	
}

int main(int argc, char const *argv[])
{
	pthread_t pt;
	void* res_t;

	if (pthread_create(&pt, NULL, fun_t, NULL) != 0)
	{
		perror("pthread_create");
	}
	printf("Linux\n");

	if (pthread_join(pt, &res_t) != 0)
	{
		perror("pthread_join");
	}
	return 0;
}