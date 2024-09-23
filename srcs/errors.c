#include "../includes/header.h"

void    error(const char *msg)
{
    const char *error_prefix;

	error_prefix = "PULSE ERROR 	: ";
	
    write(1, error_prefix, 15);
    write(1, msg, strlen(msg));
    write(1, "\n", 1);
}

void    display_errors(const int code)
{
    switch (code) {
        case 301:
            error("Incorrect conditional expression");
            break;
        case 302:
            error("Incorrect function syntax");
            break;
        case 303:
            error("Incorrect loop syntax");
            break;
        case 304:
            error("Incorrect variable declaration");
            break;
        case 601:
            error("Unable to read file");
            break;
        case 602:
            error("Unable to create executable file");
            break;
        case 603:
            error("Dynamic memory allocation failed");
            break;
        case 604:
            error("The executable file was not found");
            break;
        case 605:
            error("Command buffer memory space exceeded");
            break;
        case 101:
            error("You must specify a pulse file to compile");
            break;
        case 102:
            error("The specified file is not a Pulse file");
            break;
        default:
            error("Unknown error code");
            break;
    }
    exit(1);
}