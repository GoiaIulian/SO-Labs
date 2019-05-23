#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

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
     int pipefd[2];
     int pid;

     pipe(pipefd);

     pid = fork();
     if (pid > 0)
     {
          char* f = (char*)malloc(50 * sizeof(char));
          char* r = (char*)malloc(50 * sizeof(char));
          printf("Give the file name : \n");
          scanf("%s", f);
          printf("Give the access rights : \n");
          scanf("%s", r);
          strcat(f, " ");
          strcat(f, r);
          close(pipefd[0]);
          write(pipefd[1], f, strlen(f) + 1);
          close(pipefd[1]);
          free(f);
          free(r);
     }
     else
     {
          char* fileName;
          char* rights;
          close(pipefd[1]);
          fileName = readWord(pipefd[0]);
          rights = readWord(pipefd[0]);
          close(pipefd[0]);
          int r = atoi(rights);
          if (r == 0 || strlen(rights) != 3)
          {
               printf("Invalid input for the permission \n");
               exit(0);
          }
          char* command = (char*)malloc(200 * sizeof(char));
          strcpy(command, "./change_perm.sh");
          strcat(command, " ");
          strcat(command, fileName);
          strcat(command, " ");
          strcat(command, rights);
          system(command);
          char* res;
          int fd = open("in.txt", O_RDONLY);
          res = readWord(fd);
          if (strcmp(res, "") != 0)
          {
               printf("Totul e OK! \n");
          }
          else
          {
               strcpy(command, "./find_file.sh ");
               strcat(command, fileName);
               system(command);
               res = readWord(fd);
               if (strcmp(res, "") != 0)
               {
                    strcpy(command, "chmod ");
                    strcat(command, rights);
                    strcat(command, " ");
                    strcat(command, fileName);
                    system(command);
                    printf("Drepturile au fost modificate \n");
               }
               else
               {
                    printf("The file does not exist \n");
                    exit(0);
               }
          }
          close(fd);
          free(res);
          free(fileName);
          free(command);
          free(rights);
          exit(0);
     }
     return 0;
}
