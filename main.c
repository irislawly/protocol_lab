#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    fd_set rfds;
    int    retval;

    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    printf("A\n");

    while(1)
    {
        retval = select(1, &rfds, NULL, NULL, NULL);

        printf("B\n");

        if(retval == -1)
        {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // needs to be a real loop that stops when all fds have been processed
        for(;;)
        {
            if(FD_ISSET(STDIN_FILENO, &rfds))
            {
                char str[10];

                memset(str, 0, 10);
                read(STDIN_FILENO, str, 10);
                printf("%s\n", str);
            }
        }
    }

    return EXIT_SUCCESS;
}
