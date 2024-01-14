#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int foo(int ele) {
    return ele*2;
}

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Impropper number of arguments");
        exit (1);
    }

    int num = atoi(argv[argc-1]);

    int res = foo(num);
    printf("Current process id: %d, Current result: %d", (int) getpid(), res);

    char *argument_list[argc-1];
    for (int i=1; i<argc; i++) {
        argument_list[i-1] = argv[i];
    }

    argument_list[argc-1] = NULL;
    // printf("Working till here\n");
    tostring(argument_list[argc-2], res);

    for (int i=0; i<argc; i++){
        printf("%s\n", argument_list[i]);
    }
    printf("\n\n\n");

    int status_code = execvp(argument_list[0], argument_list);

    if (status_code == -1) {
        printf("Execution Complete\n");
        return 1;
    }

    printf("This should not be printed\n");
    return 0;
}
