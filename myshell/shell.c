#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#define PS1 "mage@mage$  "
typedef struct
{
    char *argv[1024];
    int in,out;
}comm;
int main()
{
    while(1)
    {
        write(STDOUT_FILENO,PS1,strlen(PS1));
        char buf[1024]={0};
        int count=read(STDIN_FILENO,buf,1024);
        buf[count-1]=0;
        int commcount =0;
        char* command=strtok(buf,"|");
        comm commlist[1024];
        int pipefd[2];
        while(command)
        {
            int len=strlen(command);
            int i=0;
            char* p= strtok(command," ");
            if(commcount==0)
            {
                commlist[commcount].in=0;
            }else
            {
                commlist[commcount].in=pipefd[0];
            }
            commlist[commcount].out=1;
            while(p)
            {
                if(*p=='<')
                {
                    p=strtok(NULL," ");
                    int fin = open(p,O_RDONLY);
                    if(fin==-1)
                    {
                        sleep(1);
                        perror("open");
                    }
                    commlist[commcount].in=fin;
                    break;
                }else if(*p=='>')
                {
                    p=strtok(NULL," ");
                    int fout = open(p,O_WRONLY|O_CREAT,0644);
                    if(fout==-1)
                    {
                        perror("open");
                    }
                    commlist[commcount].out=fout;
                    break;
                }else
                {
                    commlist[commcount].argv[i]=(char*)malloc(strlen(p));
                    //printf("%p\n",commlist[commcount].argv[i]);
                    strcpy(commlist[commcount].argv[i],p);
                    i++;
                    p=strtok(NULL," ");
                }
            }
            commlist[commcount].argv[i]=NULL;
            command=strtok(command+len+1,"|");
            if(command)
            {
                if(-1==pipe(pipefd))
                {
                    perror("pipe");
                }
                commlist[commcount].out=pipefd[1];
            }
            commcount++;
        }
        int j=0;
        while(j<commcount)
        {
            int ret=fork();
            if(ret==-1)
            {
                perror("fork");
            }
            else if(ret==0)
            {
                break;
            }
            j++;
        }
        if(j<commcount)
        {
            printf("in:%d,out:%d\n",commlist[j].in,commlist[j].out);
            dup2(commlist[j].in,STDIN_FILENO);
            dup2(commlist[j].out,STDOUT_FILENO);
            int fd=3;
            while(1)
            {
                if(-1== close(fd))
                    break;
                fd++;
            }
            //printf("%s\n",commlist[j].argv[0]);
            execvp(commlist[j].argv[0],commlist[j].argv);
        }else
        {
            int fd=3;
            while(1)
            {
                if(-1==close(fd))
                    break;
                fd++;
            }
            //printf("%d\n",fd);
            for(j=0;j<commcount;j++)
            {
                int k=0;
                while(commlist[j].argv[k]!=NULL)
                {
                    free(commlist[j].argv[k]);
                    //printf("%p\n",commlist[j].argv[k]);
                    k++;
                }
            }
            for(j=0;j<commcount;j++)
                wait(NULL);
        }



        /*   int j=0;
             while(j<commcount)
             {
             int k=0;
             printf("in:%d,out:%d\n",commlist[j].in,commlist[j].out);
             while(commlist[j].argv[k]!=NULL)
             {
             printf("%s\n",commlist[j].argv[k]);
             k++;
             }
             j++;
             }
             */
    }
}
