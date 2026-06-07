#include <stdio.h>
#include<unistd.h>
#include<pwd.h>
#include "audit.h"
#include "execute.h"
#include "config.h"



int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage: elevate <command>\n");
        return 1;
    }
    
    struct passwd *pwd = getpwuid(getuid());
    if(!pwd){
        perror("getpwuid failed");
        return 1;
    }

    char *user = pwd->pw_name;


    if(!is_allowed(user, argv[1])){
        printf("You are not allowed to execute this command\n");

        audit_log(user, argv[1], -1);
        return 1;
    }

    int status;
    status = execute_command(&argv[1]);
    audit_log(user, argv[1], status);
    // printf("Command returned %d\n", rc);
    

    return 0;
}