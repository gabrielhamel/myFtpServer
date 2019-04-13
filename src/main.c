/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** main
*/

#include <stdlib.h>
#include "myftp.h"

int main(int ac, char **av)
{
    if (check_usage(ac, (const char **)av) == false)
        abort_prgm();
    launch_ftp(av[2], strtol(av[1], NULL, 10));
    return (EXIT_SUCCESS);
}