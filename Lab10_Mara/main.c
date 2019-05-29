#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
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
     int parentChild[2];
     int childParent[2];
     int pid;

     pipe(parentChild);
     pipe(childParent);

     pid = fork();

     if (pid > 0)
     {
          // parent code
          char* name = (char*)malloc(50 * sizeof(char));

          printf("Give the name of the unix machine : \n");
          scanf("%s", name);

          close(parentChild[0]);
          write(parentChild[1], name, strlen(name) + 1);
          close(parentChild[1]);

          close(childParent[1]);
          name = readWord(childParent[0]);
          close(childParent[0]);
          printf("%s\n", name);

          free(name);
     }
     if (pid == 0)
     {
          // child code
          int fd;
          char* name;
          close(parentChild[1]);
          name = readWord(parentChild[0]);
          close(parentChild[0]);

          system("chmod +x users.sh");
          system("./users.sh");

          close(childParent[0]);
          free(name);
          fd = open("logged.txt", O_RDONLY);
          char* user = readWord(fd);
          char* users = (char*)calloc(1000, sizeof(char));
          while(strcmp(user, "") != 0)
          {
               strcat(users, user);
               strcat(users, " ");
               free(user);
               user = readWord(fd);
          }

          write(childParent[1], users, strlen(users) + 1);
          close(childParent[1]);
          free(users);
          free(user);
          close(fd);
          exit(0);
     }

     return 0;
}
