#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
// we need these headers

int main(int argc, char *argv[]) {
    printf("\033[1;34m"); // gives a bold blue color
    // will make it look nicer
    printf("\nEnter a valid command \n"); //print
    printf("\nTo see the list of all the valid commands, type reference \n"); //print
    printf("\033[1;37m"); // going to use: bold white
    // will make it look nicer
    return 0;
}
