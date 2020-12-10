#include <stdio.h>
#include <unistd.h>
//#include <sys/types.h>
#include <fcntl.h> // for all O_ and S_


/*
int open(const char *pathname, int flags); or
int open(const char *pathname, int flags, int mode); 
The parameter flags must include one of the following access modes: O_RDONLY, O_WRONLY, or O_RDWR. These request opening the file read-only, write-only, or read/write, respectively.
In addition, zero or more file creation flags and file status flags can be bitwise-or’d in flags. The file creation flags are O_CREAT, O_EXCL, O_NOCTTY, and O_TRUNC.
open() return the new file descriptor, or -1 if an error occurred.
*/
/*
ssize_t read(int fd, void *buf, size_t count); // under unistd.h
read() attempts to read up to `count` bytes from file descriptor `fd` into the buffer starting at `buf`. On success, the number of bytes read is returned. Else -1.
*/

void main()
{
	char buf;
	int fd_one, fd_two;

	fd_one = open("first_file", O_RDONLY);
	
	//fd_two = open("second_file", O_WRONLY | O_CREAT);
	// creates second_file with perms ---sr-x--T
	// so, specify mode explicitly

	fd_two = open("second_file", 
				  O_WRONLY | O_CREAT,
				  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	// -rw-r--r-- is the default permission for new files
	// From the table given here:  https://www.tutorialspoint.com/unix_system_calls/open.htm
	// irusr or iwusr or irgrp or iroth = rw-r--r--
	
	while(read(fd_one, &buf, 1))
	{
		write(fd_two, &buf, 1);
	}

	printf("Successful copy");

	close(fd_one);
	close(fd_two);

}
