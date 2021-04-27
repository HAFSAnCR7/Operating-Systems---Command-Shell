#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // print the current directory to the terminal
    char cwd[200];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current Directory: %s\n", cwd);
    }
    // error occured
    else
    {
        perror("Error");
        return 1;
    }

    // write the printed current directory to t2.txt
    FILE *file;
    //open t2 file
    file = fopen("./t2.txt", "w");
    // error occured
    if (file == NULL)
    {
        perror("Error with file");
    }
    fputs(cwd, file);
    fclose(file);
    printf("Current directory written to t2.txt\n");

    // changes the name of text file t2.txt to path.txt
    int val = rename("./t2.txt", "./path.txt");
    printf("Changed text file t2.txt to path.txt\n");
    // error occured
    if (val)
    {
        perror("Error");
    }

    //Concatenate the content of tree.txt and path.txt into t3.txt
    FILE *ftree = fopen("./tree.txt", "r");
    FILE *fp = fopen("./path.txt", "r");
    FILE *ft3 = fopen("./t3.txt", "w");
    char c;

    // error occured with files
    if (ftree == NULL)
    {
        perror("Error with file");
        exit(0);
    }

    if (fp == NULL)
    {
        perror("Error with file");
        exit(0);
    }

    if (ft3 == NULL)
    {
        perror("Error with file");
        exit(0);
    }

    while ((c = fgetc(ftree)) != EOF)
        fputc(c, ft3);
    while ((c = fgetc(fp)) != EOF)
        fputc(c, ft3);

    //closes
    fclose(ftree);
    fclose(fp);
    fclose(ft3);
    printf("Concatenated the content of tree.txt and path.txt into t3.txt\n");

    // changes the name of text file t3.txt to log.txt
    int nval = rename("./t3.txt", "./log.txt");
    printf("Changed text file t3.txt to log.txt\n");
    // error occured
    if (nval)
    {
        perror("Error");
    }

    //delete tree.txt and path.txt.
    if (remove("./path.txt") != 0)
        perror("Error");
    printf("Deleted path.txt\n");
    if (remove("./tree.txt") != 0)
        perror("Error");
    printf("Deleted tree.txt\n");

    return 0;
}