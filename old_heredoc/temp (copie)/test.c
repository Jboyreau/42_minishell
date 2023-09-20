#include <errno.h>
#include <stdio.h>

int main()
{
    for (int i = 0; i < 150; i++)
    {
        printf("%d\n", errno);
        perror("oups ");
        errno++;
    }
    errno = 0;
    perror("c moi");
    errno = 1;
    perror("c moi");
    printf("%lu\n", sizeof(errno));
    return (0);
}