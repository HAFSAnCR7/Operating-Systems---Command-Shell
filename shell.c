#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

struct Node { 
    char *cmd;
    struct Node* link; 
}; 

struct Node* head = NULL; 
struct Node* tail = NULL;
int size = 0;

// code to create and add to linked list
void link_to_list(char *cmd) {
    struct Node* x = (struct Node*)malloc(sizeof(struct Node));
    x->cmd = cmd;
    x->link = NULL;
    
    if (head == NULL) { // if empty list
        head = x; // set head to x
        tail = x; // set tail to head
        size++;
    }

    else { // if non-empty list
        tail->link = x; // set tail->link to x
        tail = x; // set tail to x

        if (size == 4) // if size of 4 is reached, move head to the right (similar to queue)
            head = head->link;
        else // if max size is not yet reached, keep incrementing list size
            size++;
    }
} 

// command to get updated history
char* updateHistory() {
    char *cmdData = malloc(50); // store history of commands in a string (separated by commas)
    strcpy(cmdData, "");

    struct Node* iterator = head;
    int count = 0;
    while (iterator != NULL) {
        if(count == 0)
        strcat(cmdData, iterator->cmd); // link command to end of cmdData
        else if(count > 0){
            strcat(cmdData, " --> "); // link comma to beginning of cmdData
            strcat(cmdData, iterator->cmd); // link command to end of cmdData
        }
        count++;
        iterator = iterator->link; 
    }

    return cmdData;
} 

int main(int argc, char *argv[]) {
    while(1) 
    { //loop will run until "exit" is types
        printf("\n♠️: ");
        char *buffer = NULL;
        size_t len = 0;
        ssize_t lineSize  = 0;    //ssize_t byte count for returns error function 
        lineSize  = getline(&buffer, &len, stdin); // use getline to store input into buffer
        
        if (lineSize  > 0 && buffer[lineSize -1] == '\n') // replace \n with \0
            buffer[--lineSize ] = '\0';

        link_to_list(buffer); // add command to linked list
        char* info = updateHistory(); // update history

        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Essentially, fork has failed");
            return 1;
        }
        else if (pid == 0) {
            if (strcmp(buffer, "tree") == 0) { // if user types tree, execute tree() command 
                char *args[] = {"./tree", buffer, NULL};
                execv("./objectFile/tree", args);
            }

            else if (strcmp(buffer, "list") == 0) { // if user types list, execute list() command
                if (chdir("Dir0") == -1) // change dir, otherwise print message that dir doesn't exist
                    printf("\033[1;31mDir0 does not exist!\033[0m\n");

                char *args[] = {"./list", buffer, NULL};
                execv("../objectFile/list", args);

            }
            else if (strcmp(buffer, "path") == 0) { // if user types path, execute path() command 
                if (chdir("Dir0") == -1) // change dir, otherwise print message that dir doesn't exist
                    printf("\033[1;31mDir0 does not exist!\033[0m\n");

                char *args[] = {"./path", buffer, NULL};
                execv("../objectFile/path", args);
            }
            else if (strcmp(buffer, "exit") == 0) { // if user types exit, execute exit() command
                printf("\033[1;34mTerminal Exit!\033[0m\n");
                char *args[] = {"./exit", info, NULL};

                if (chdir("Dir0") != -1) // try to change dir, otherwise execute in current dir
                    execv("../objectFile/exit", args);
                else
                    execv("./objectFile/exit", args);
            }

            else if (strcmp(buffer, "reference") == 0) { // if user types exit, execute exit() command
                char *args[] = {"./reference", buffer, NULL};
                execv("./objectFile/reference", args);
            }
            else { // if user types invalid command, execute error() command
                char *args[] = {"./issues", buffer, NULL};
                execv("./objectFile/issues", args);
            }
            exit(1);
        }
        
        wait(NULL); 
        if (strcmp(buffer, "exit") == 0){
            getchar();
            break;
        }
    }
    
    return 0;
}

