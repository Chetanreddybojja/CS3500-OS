#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "stddef.h"

int main()
{
    int v = fork();
    if (v == 0){
        printf("\nChild process: \n");
        pcbread();
    }
    else{
        wait(NULL);
        printf("\nParent process: \n");
        pcbread();
    }
    exit(0);
}
