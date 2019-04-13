/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "myftp.h"

static bool *loop(void)
{
    static bool loop = true;

    return (&loop);
}

static void forcequit(int sig)
{
    bool *test = loop();

    (void)sig;
    *test = false;
}

static void ftp_loop(socket_list_t *list, char *path)
{
    socket_t **tab;

    while (*loop()) {
        tab = socket_list_get_event(list);
        if (tab == NULL)
            continue;
        manage_event(list, tab, path);
        free(tab);
    }
}

void launch_ftp(char *path, uint16_t port)
{
    socket_list_t *list = socket_list_create();
    socket_t *tmp;

    tmp = socket_server_create(port, MAX_CLI, NULL, NULL);
    if (tmp == NULL)
        abort_prgm();
    socket_list_add(list, tmp);
    signal(SIGINT, forcequit);
    ftp_loop(list, path);
    socket_list_destroy(list);
}