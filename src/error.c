/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** error
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void abort_prgm(void)
{
    if (errno)
        dprintf(STDERR_FILENO, "%s\n", strerror(errno));
    exit(EXIT_ERROR);
}