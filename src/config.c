#include <stdio.h>
#include <string.h>

char* get_command_basename(char* cmd){
    char* base = strrchr(cmd, '/');
    if(base == NULL){
        return cmd;
    }
    return base + 1;
}

int is_allowed(char *user, char *cmd){
    // TODO: Implement this function

    // read the file 
    FILE *fp = fopen("config/elevate.conf", "r");
    if(fp == NULL){
        perror("Error opening file");
        return 0;
    }
    
    char *resolved_command = get_command_basename(cmd);

    char cfg_name[100];
    char cfg_operation[100];

    while(fscanf(fp, "%99s %99s", cfg_name, cfg_operation) == 2){
        if(strcmp(cfg_name, user) == 0 ){

            if (strcmp(cfg_operation, resolved_command) == 0 || strcmp(cfg_operation, "*") == 0){
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
    
}