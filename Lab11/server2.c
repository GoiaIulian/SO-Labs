#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

char* readWord(int fd)
{
     char c;
     char* word = (char*)malloc(50 * sizeof(char));
     strcpy(word, "");
     int i = 0;
     while (1)
     {
          if (read(fd, &c, 1) == 0)
          {
               break;
          }
          if (c == ' ' || c == '\n')
          {
               break;
          }
          word[i] = c;
          i++;
     }
     word[++i] = '\0';
     return word;
}

int main()
{
     int fd,file;
     char* myFifo = "chanal";
     mkfifo(myFifo, 0666);
     char* fileName;
     system("clear");

     while(1)
     {
          fd = open(myFifo, O_RDONLY);
          fileName = readWord(fd);
          close(fd);

          if (strcmp(fileName, "exit()") == 0)
          {
               free(fileName);
               exit(0);
          }
          fd = open(myFifo, O_WRONLY);
          file = open(fileName, O_RDONLY);

          if (file < 0)
          {
               char* e = "The file doesn't exist";
               write(fd, e, strlen(e) + 1);
          }
          else
          {
               int count = 0;
               char* w;
               while(1)
               {
                    w = readWord(file);
                    if(strcmp(w, "") == 0)
                    {
                         free(w);
                         break;
                    }
                    count++;
                    free(w);
               }
               char tmp[12]={0x0};
               sprintf(tmp, "%d", count);
               write(fd, tmp, sizeof(tmp));
          }
          free(fileName);
          close(file);
          close(fd);
     }

     return 0;
}
