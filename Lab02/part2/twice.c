#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int foo(int ele) {
    return ele*2;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Impropper number of arguments");
        exit (1);
    }

    printf("%d\n", argc);
    for (int i=0; i<argc; i++){
        printf("%s\n", argv[i]);
    }

    int num = atoi(argv[argc-1]);
    printf("Number is: %d\n", num);
    return 0;

    char *argument_list[] = {"./temp", NULL};
    execvp(argument_list[0], argument_list);

    printf("This should not be printed");
    return 0;
}
