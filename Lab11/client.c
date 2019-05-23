#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


int main()
{
     int fd;
     char* myFifo = "chanal";
     mkfifo(myFifo, 0666);
     char* fileName = (char*)malloc(200 * sizeof(char));

     while (1)
     {
          system("clear");
          printf("Enter 'exit()' for the name of the file if you want to exit the client : \n");
          printf("Give the path of the file : \n");
          scanf("%s", fileName);
          if (strcmp(fileName, "exit()") == 0)
          {
               fd = open(myFifo, O_WRONLY);
               write(fd, fileName, strlen(fileName) + 1);
               free(fileName);
               exit(0);
          }
          // printf("%s\n", fileName);

          fd = open(myFifo, O_WRONLY);
          write(fd, fileName, strlen(fileName) + 1);

          close(fd);
     }
     free(fileName);
     return 0;
}
