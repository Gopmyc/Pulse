#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>

#define BUFFER_READER			4096
#define BUFFER_CMD				2048
#define MAX_VALUE_LEN 256

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_UNKNOWN
} VarType;

typedef struct VarNode {
    char name[MAX_VALUE_LEN];
    VarType type;
    char value[MAX_VALUE_LEN];
    struct VarNode *next;
} VarNode;

/* Declarations functions of utils.c */
char							*strcpy(char *dest, const char *src);
char							*strstr(const char *haystack, const char *needle);


/* Declarations functions of errors.c */
void							error(const char *msg);
void							display_errors(int code);

/* Declarations functions of reader.c */
void							make_exec(const char *file, char *exec_name);

/* Declarations functions of vars.c */
VarNode*						vars_pulse(const char* pulse_var);