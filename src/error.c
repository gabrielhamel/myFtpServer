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
#include <myftp.h>

void abort_prgm(void)
{
    if (!errno)
        exit(EXIT_ERROR);
    dprintf(STDERR_FILENO, "%s\n", strerror(errno));
}