#include <stdio.h>
#include<unistd.h>

int main(int argc, int *argv[])
{
    printf("Elevate v0.1\n");
    printf("UID  = %d\n", getuid());
    printf("EUID = %d\n", geteuid());
    return 0;
}