#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char message[] = "Hello World";
    for (int i = 0; i < 11; i++) {
		printf("%c %d\n", message[i], getpid());
		sleep(rand() % 4 + 1);
		if (fork() != 0) {
            wait(NULL);
			break;
		}
	}
	return 0;
}
