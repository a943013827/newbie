#include <stdio.h>
#include <unistd.h>

int main()
{
    char * c[]={"./test.sh",NULL};
    execvp("./test.sh",c);
}


