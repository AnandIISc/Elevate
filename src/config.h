#ifndef CONFIG_H
#define CONFIG_H
char *validate_command(char *cmd);
char* get_command_basename(char *cmd);
int is_allowed(char *user, char *command);


#endif  // CONFIG_H