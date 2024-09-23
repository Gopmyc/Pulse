#include "../includes/header.h"

void print_vars_to_file(FILE *exec, VarNode *head) {
    while (head != NULL) {
        switch (head->type) {
            case TYPE_INT:
                fprintf(exec, "    static int %s = %s;\n", head->name, head->value);
                break;
            case TYPE_FLOAT:
                fprintf(exec, "    static float %s = %s;\n", head->name, head->value);
                break;
            case TYPE_DOUBLE:
                fprintf(exec, "    static double %s = %s;\n", head->name, head->value);
                break;
            case TYPE_STRING:
                fprintf(exec, "    static char* %s = \"%s\";\n", head->name, head->value);
                break;
            case TYPE_UNKNOWN:
                fprintf(exec, "    static unknown %s = %s;\n", head->name, head->value);
                break;
        }
        head = head->next;
    }
}

void make_exec(const char *file, char *exec_name) {
    int fd = open(file, O_RDONLY);
    if (fd < 0) display_errors(601);

    FILE *exec = fopen(exec_name, "w");
    if (!exec) display_errors(602);

    fprintf(exec, "#include <stdio.h>\n\n");
    fprintf(exec, "int main(void) {\n");

    char buffer[BUFFER_READER];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, BUFFER_READER)) > 0) {
        buffer[bytesRead] = '\0';
        char *line = strtok(buffer, "\n");
        while (line != NULL) {
            VarNode *vars = vars_pulse(line);
            print_vars_to_file(exec, vars);
            line = strtok(NULL, "\n");
        }
    }

    if (bytesRead < 0) display_errors(601);
    fprintf(exec, "    return 0;\n");
    fprintf(exec, "}\n");

    close(fd);
    fclose(exec);

    char compile_cmd[BUFFER_CMD];
    snprintf(compile_cmd, sizeof(compile_cmd), "gcc %s -o %s", exec_name, exec_name);
    if (system(compile_cmd) != 0) display_errors(603);
}