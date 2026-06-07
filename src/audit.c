#include <time.h>
#include <stdio.h>
#include <unistd.h>

void audit_log(char *user, char *commmad, int status){
    FILE *fp = fopen("log/elevate.log", "a");

    if(fp == NULL){ 
        perror("Error opening file"); 
    }

    time_t now = time(NULL);
    fprintf(fp, "Time=%ld user=%s STATUS=%d CMD=%s", now, user, status, commmad);
    // for(int i = 1; i < argc; i++){
    //     fprintf(fp, "%s ", argv[i]);
    // }

    fprintf(fp, "\n");
    fclose(fp);
}
