#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

char* readLine(int fd)
{
     char c;
     char* line = (char*)malloc(255 * sizeof(char));
     strcpy(line, "");
     int i = 0;
     while (1)
     {
          if (read(fd, &c, 1) == 0)
          {
               break;
          }
          if (c == '\n')
          {
               break;
          }
          line[i] = c;
          i++;
     }
     line[++i] = '\0';
     return line;
}

int main()
{
     system("clear");
     int fd;
     char* myFifo = "chanal";
     mkfifo(myFifo, 0666);
     char* fileName;
     printf("Enter 'exit()' for the name of the file if you want to exit the client : \n");
     printf("Give the path of the file : \n");

     while (1)
     {
          scanf("%s", fileName);
          fd = open(myFifo, O_WRONLY);
          if (strcmp(fileName, "exit()") == 0)
          {
               write(fd, fileName, strlen(fileName) + 1);
               close(fd);
               exit(0);
          }

          write(fd, fileName, strlen(fileName) + 1);
          close(fd);


          fd = open(myFifo, O_RDONLY);
          char* nr;
          nr = readLine(fd);
          close(fd);

          printf("%s\n", nr);
          free(nr);
     }
     return 0;
}
