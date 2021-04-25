#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


int list(child1)
{
    
    if(child1 < 0)
    {
        printf(" Child 1 not created! \n");
        return 1;
    }

    if(child1 == 0)
    {
        system("clear"); // Clears the terminal 
        execlp("ls", "ls", "-l", NULL); // '-l' is used to see all the information of each file in the directory
        printf("EXECLP Failed\n");
        _exit(0);
    }

    wait(NULL);
    char old [] = "t1.txt";
    char new [] = "tree.txt";
    rename (old, new); // Renames t1.txt to tree.txt

    return 0;
}


int main(int argc, char *argv[])
{
    char c [50]; // Array of string to hold user input.
    while(scanf("%s", c)) // Loop to stay in terminal until "exit" is called. 
    {   
        /* The "lsit and "exit" command can be named as anything, i just labeled them as such to show the code works. */
        if (strcmp(c,"exit") == 0) 
            break;
        else if (strcmp(c,"list") == 0) 
        {   
            int child1 = fork();
            list(child1);  
        }
        else
        {
            printf("Invalid Command\n");
        }

    }; /* Could put a while loop on the shell code and allow it to leave the terminal only when "exit" is called. 
        Ill leave the while loop as an example, but i can also take it out. */
    

    return 0;
}