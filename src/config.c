#include <stdio.h>
#include <string.h>

int is_allowed(char *user, char *cmd){
    // TODO: Implement this function

    // read the file 
    FILE *fp = fopen("config/elevate.conf", "r");
    if(fp == NULL){
        perror("Error opening file");
        return 0;
    }
    

    char cfg_name[100];
    char cfg_operation[100];

    while(fscanf(fp, "%99s %99s", cfg_name, cfg_operation) == 2){
        if(strcmp(cfg_name, user) == 0 ){

            if (strcmp(cfg_operation, cmd) == 0 || strcmp(cfg_operation, "*") == 0){
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
    
}