#include "../includes/header.h"

VarNode* create_var(const char* name, VarType type, const char* value) {
    VarNode *node = (VarNode*)malloc(sizeof(VarNode));
    if (!node) return NULL;
    strncpy(node->name, name, sizeof(node->name));
    node->type = type;
    strncpy(node->value, value, sizeof(node->value));
    node->next = NULL;
    return node;
}

void add_var(VarNode **head, VarNode *node) {
    if (*head == NULL) {
        *head = node;
    } else {
        VarNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

void print_vars(const VarNode *head) {
    while (head != NULL) {
        switch (head->type) {
            case TYPE_INT:
                printf("static int %s = %s;\n", head->name, head->value);
                break;
            case TYPE_FLOAT:
                printf("static float %s = %s;\n", head->name, head->value);
                break;
            case TYPE_DOUBLE:
                printf("static double %s = %s;\n", head->name, head->value);
                break;
            case TYPE_STRING:
                printf("static char* %s = \"%s\";\n", head->name, head->value);
                break;
            case TYPE_UNKNOWN:
                printf("static unknown %s = %s;\n", head->name, head->value);
                break;
        }
        head = head->next;
    }
}

VarNode* vars_pulse(const char* pulse_var)
{
    VarNode *head = NULL;

    const char *var_name = strchr(pulse_var, ' ') + 1;
    const char *assign = strchr(var_name, '=');
    const char *end_of_line = strchr(pulse_var, ':');
    if (end_of_line == NULL) {
        end_of_line = pulse_var + strlen(pulse_var);
    }

    char value[MAX_VALUE_LEN];
    size_t value_len = end_of_line - assign - 1;
    if (value_len >= MAX_VALUE_LEN) {
        value_len = MAX_VALUE_LEN - 1;
    }
    strncpy(value, assign + 1, value_len);
    value[value_len] = '\0';

    VarType type = TYPE_UNKNOWN;
    char *endptr;

    long long int_value = strtoll(value, &endptr, 10);
    if (*endptr == '\0' && endptr != value) {
        type = TYPE_INT;
    } else {
        double float_value = strtod(value, &endptr);
        if (*endptr == '\0' && endptr != value) {
            if (float_value > DBL_MAX || float_value < -DBL_MAX) {
                type = TYPE_DOUBLE;
            } else if (float_value > FLT_MAX || float_value < -FLT_MAX) {
                type = TYPE_FLOAT;
            }
        } else {
            size_t len = strlen(value);
            if (len > 1 && value[0] == '"' && value[len - 1] == '"') {
                type = TYPE_STRING;
                value[len - 1] = '\0';
                memmove(value, value + 1, len - 2);
                value[len - 2] = '\0';
            }
        }
    }

    const char *type_prefix = NULL;
    if (strstr(pulse_var, "local const") == pulse_var) {
        type_prefix = "static const";
    } else if (strstr(pulse_var, "const") == pulse_var) {
        type_prefix = "const";
    } else if (strstr(pulse_var, "local") == pulse_var) {
        type_prefix = "static";
    } else {
        type_prefix = "";
    }

    char name[MAX_VALUE_LEN];
    size_t var_name_len = assign - var_name;
    strncpy(name, var_name, var_name_len);
    name[var_name_len] = '\0';

    VarNode *node = create_var(name, type, value);
    if (node) {
        add_var(&head, node);
    }

    return head;
}