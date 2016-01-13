#include <unistd.h>

int main()
{
    link("./stat","aaaa");
    unlink("stat");
    return 0;
}
