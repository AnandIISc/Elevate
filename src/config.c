#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char *resolve_command(char *cmd){

    char *env_p = getenv("PATH");

    if(env_p == NULL){
        return NULL;
    }

    char *path = strdup(env_p);
    char *token = strtok(path, ":");

    while(token != NULL){
        char *full_path = malloc(strlen(token) + strlen(cmd) + 2);
        sprintf(full_path, "%s/%s", token, cmd);
        if(access(full_path, X_OK) == 0){
            free(path);
            return full_path;
        }
        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path);
    return NULL;
}


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
    
    
    char *full_path = resolve_command(cmd);
    if(full_path == NULL){
        fclose(fp);
        return 0;
    }

    char *resolved_command = get_command_basename(full_path);

    if(resolved_command == NULL){
        fclose(fp);
        free(full_path);
        return 0;  
    }


    char cfg_name[100];
    char cfg_operation[100];

    while(fscanf(fp, "%99s %99s", cfg_name, cfg_operation) == 2){
        if(strcmp(cfg_name, user) == 0 ){
            if (strcmp(cfg_operation, resolved_command) == 0 || strcmp(cfg_operation, "*") == 0){
                free(full_path);
                fclose(fp);
                return 1;
            }
        }
    }

    free(full_path);
    fclose(fp);
    return 0;
    
}