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
    return (EXIT_SUCCESS);
}