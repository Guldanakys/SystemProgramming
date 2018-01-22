#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

char buf1[] = "lets write file"; //15
char buf2[] = "with holes"; //10


int main()
{
    int fd, size, sizer, n = 82, i = 0, m = 0;
    char filename[100];
    scanf("%s", filename);
    strcat(filename, ".txt");
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd == -1){
        perror("open");
    }while( i < n){
        if(write(fd, buf1, strlen(buf1)) != 15) // offset 15
            perror("buf1 write error");

        if(lseek(fd, 40 + m, SEEK_SET) == -1)  // offset 40
            perror("lseek error");

        if(write(fd, buf2, strlen(buf2)) != 10) //offset 50
            perror("buf2 write error");
        i++;
        m += 51;
    }

    int ret;
    ret = lseek (fd, 0, SEEK_END);
    if (ret == -1)
    fclose(fd);
    printf("%d\n", ret);
    struct stat st;
    stat(filename, &st);
    size = st.st_size;
    sizer = st.st_blksize;
    printf("%d\n", size);
    printf("%d\n", sizer);


    /*
    char buf[100];
    int fd1, fd2, len=100;
    ssize_t ret1, ret2;
    fd1 = open (filename, O_RDONLY);
    if(fd1 == -1){
        perror("open");
        exit(EXIT_FAILURE);                             //Do not continue next steps: read(), close()
    }
    fd2 = creat ("copy.txt", S_IRWXU);
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
    }*/
    return 0;
}
