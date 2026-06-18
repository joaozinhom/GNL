#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int fd, sz;
	char* c = malloc(100 * sizeof(char));

	//to read and print use fd 2!!!
	fd = open("foo.txt", 2);
	if (fd < 0) {
		perror("r1");
		exit(1);
	}

	sz = read(fd, c, 34);
	c[sz] = '\0';
	printf("Bytes findend in the gived buffer: %s \n", c);

	return 0;
}