#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int foo(int ele) {
    return ele*ele;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Impropper number of arguments");
        exit (1);
    }

    int num = atoi(argv[argc-1]);

    int res = foo(num);
    printf("Square: Current process id: %d, Current result: %d\n", (int) getpid(), res);

    sprintf(argv[argc-1], "%d", res);

    int status_code;
    if (argc > 2){
        status_code = execvp(argv[1], argv+1);
    } else {
        return 0;
    }

    if (status_code == -1) {
        printf("Execution Complete\n");
        return 1;
    }

    printf("This should not be printed\n");
    return 0;
}
