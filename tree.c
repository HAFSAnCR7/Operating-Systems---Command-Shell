#include <stdio.h>
#include <unistd.h> // Use of chdir
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> // Use of mkdir
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    
    int fd = fork(); // Child
    
    // Case 1: If the fork fails, then print the error message below
    if(fd < 0) {
        print("Fork has failed...");
    }
    // Case 2: If fork() == 0, then make a new directory, "Dir0" and give it all access
    else if (fd == 0) {
        mkdir("Dir0",0777); // Creates a new directory with the name path
                            // The mode is 0777 which gives it the most possibile access
        exit(0);            // Terminates the child
    }
    // Case 3: If fork() > 0, then complete the task below
    else {
        wait(NULL); // Waiting for this child
        chdir("Dir0"); // Make "Dir0" the current working directory
        // w = write, Creates the empty file
        // b = open file as binary file
        FILE *t1 = fopen("t1.txt","w+b"); // Creates filename t1.txt
        fclose(t1); // Closes file t1
        FILE *t2 = fopen("t2.txt","w+b"); // Creates filename t2.txt
        fclose(t2); // Closes file t2
        FILE *t3 = fopen("t3.txt","w+b"); // Creates filename t3.txt
        fclose(t3); // Closes file t3
        mkdir("Dir1",0777); // Creates a new directory with the name path inside "Dir0"
                            // The mode is 0777 which gives it the most possibile access
    }
    
}


