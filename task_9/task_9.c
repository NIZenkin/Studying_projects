#include <signal.h>
#include <stdio.h>

void my_handler(int nsig)
{
    printf(" %d Signal recieved!\n", nsig);
}

int main(void)
{
    for(int i = 1; i <= 30; i++)
    {
        (void)signal(i, my_handler);
    }

    while(1);

    return 0;
}
