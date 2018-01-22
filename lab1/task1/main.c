#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#define MAX_READ 100


int main()
{
    int fd1, fd2, len=MAX_READ;
    char filename1[100], filename2[100], buf[MAX_READ];
    ssize_t ret1, ret2;
    scanf("%s" "%s", filename1, filename2);
    if(strcmp(filename1, filename2) == 0){
        printf("Cannot copy the same file\n");
        exit(EXIT_FAILURE);
    }
    fd1 = open (filename1, O_RDONLY);
    if(fd1 == -1){
        perror("open");
        exit(EXIT_FAILURE);                             //Do not continue next steps: read(), close()
    }
    fd2 = creat (filename2, S_IRWXU);
    if(fd2 == -1){
        perror("create");
    }

     while((ret1 = read (fd1, &buf, len)) != 0){
     if(ret1 == -1){                                  //from the file associated with the open file descriptor,
            if(errno == EINTR)                          //fildes, into the buffer pointed to by buf.
                continue;
            perror("read");
            break;
        }
        ret2 = write (fd2, &buf, ret1);
        if(ret2 != ret1)
            perror("write");
    }

    if(close(fd1) == -1){
        perror("close");
    }
    if(close(fd2) == -1){
        perror("close");
    }
    printf("File copied successfully!\n");


    return 0;
}
