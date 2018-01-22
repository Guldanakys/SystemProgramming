#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd, nr;
    char text[1000], teee[20], command[20], filename[100];
    scanf("%s %s %s %s", text, teee, command, filename);
    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    nr = write(fd, text, strlen(text));
    if(nr == -1){
        perror("write");
    }
    if(close(fd) == -1){
        perror("close");
    }
    return 0;
}
