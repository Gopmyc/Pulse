#include "../includes/header.h"

int main(int ac, char **av) {
	char		*exec_name = "exec";

    if (ac >= 2)
	{
		if (av[2])
			exec_name = av[2];

		if (strstr(av[1], ".pulse") != NULL)
        	make_exec(av[1], exec_name);
		else
			display_errors(102);
    }
	else
		display_errors(101);
    return 0;
}
