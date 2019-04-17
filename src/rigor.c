/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** rigor
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include "myftp.h"

static void check_sudo(void)
{
    int id = getuid();

    if (id != 0)
        printf("Warning you doesn't run with root user. " \
        "Cannot check linux users.\n");
}

static size_t get_short_len(void)
{
    size_t len = 1;
    __uint16_t nb = __UINT16_MAX__;

    while (nb > 9) {
        nb /= 10;
        len++;
    }
    return (len);
}

static bool check_server_directory(const char *directory)
{
    struct stat info = {0};

    if (lstat(directory, &info) == -1 || !S_ISDIR(info.st_mode) ||
        !(info.st_mode & S_IRUSR) || !(info.st_mode & S_IWUSR))
        return (false);
    return (true);
}

static bool check_server_port(const char *port)
{
    size_t offset = 0;
    size_t len;

    if (!strlen(port))
        return (false);
    for (size_t idx = 0; port[idx] != '\0'; idx++)
        if (isdigit(port[idx]) == false)
            return (false);
    for (; port[offset] == '0'; offset++);
    len = strlen(port + offset);
    if (len == 0 || len > get_short_len() ||
    strtol(port, NULL, 10) > __UINT16_MAX__)
        return (false);
    return (true);
}

bool check_usage(int ac, const char **av)
{
    if (ac == 3) {
        if (check_server_port(av[1]) == false) {
            dprintf(STDERR_FILENO, "Invalid port %s\n", av[1]);
            return (false);
        }
        if (check_server_directory(av[2]) == false) {
            dprintf(STDERR_FILENO, "Cannot access at %s\n", av[2]);
            return (false);
        }
        check_sudo();
        return (true);
    }
    printf("USAGE:\t%s port path\n\t" \
        "port is the port number on which the server socket listens\n\t" \
        "path is the path to the home directory for" \
        " the " DEFAULT_USER " user\n", av[0]);
    return (false);
}