#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int replace_flag = 1;
    char buffer[4096];
    char exec_path[4096];
    char server_protocol[4096];
    char* str;
    scanf("%s", buffer);
    scanf("%s", buffer);
    scanf("%s", server_protocol);
    str = strtok(buffer, "?");
    strcpy(exec_path, str + 1);
    str = strtok(NULL, "?");
    if (access(exec_path, F_OK) == -1) {
        printf("%s 404 ERROR\n\n", server_protocol);
        return 0;
    } else if (access(exec_path, X_OK) == -1) {
        printf("%s 403 ERROR\n\n", server_protocol);
        return 0;
    } else {
        printf("%s 200 OK\n", server_protocol);
        fflush(stdout);
    }
    setenv("REQUEST_METHOD", "GET", replace_flag);
    setenv("SCRIPT_NAME", exec_path, replace_flag);
    if (str != NULL) {
        setenv("QUERY_STRING", str, replace_flag);
    } else {
        setenv("QUERY_STRING", "", replace_flag);
    }
    setenv("SERVER_PROTOCOL", server_protocol, replace_flag);
    while (fgets(buffer, 4096, stdin) != NULL) {
        if (strstr(buffer, "Host") != NULL) {
            strtok(buffer, " \n\t");
            str = strtok(NULL, " \n\t");
            setenv("HTTP_HOST", str, replace_flag);
        }
    }
    execl(exec_path, exec_path, NULL);
    return -1;
}