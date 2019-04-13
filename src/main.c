/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** main
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "myftp.h"
#include "socket.h"

int main(int ac, char **av)
{
    uint16_t port;
    char *buff;
    socket_list_t *list = socket_list_create();
    socket_t *tmp;
    socket_t **tab;
    bool loop = true;

    if (check_usage(ac, (const char **)av) == false)
        abort_prgm();
    port = strtol(av[1], NULL, 10);
    tmp = socket_server_create(port, MAX_CLI);
    if (tmp == NULL)
        abort_prgm();
    printf("New server %d\n", tmp->fd);
    socket_list_add(list, tmp);
    while (loop) {
        tab = socket_list_get_event(list);
        if (tab == NULL)
            continue;
        for (size_t i = 0; tab[i] != NULL; i++) {
            tmp = tab[i];
            if (tmp->type == SERVER) {
                tmp = socket_server_accept_cli(tmp);
                if (tmp != NULL) {
                    printf("New client %d\n", tmp->fd);
                    socket_list_add(list, tmp);
                    write(tmp->fd, "220 (vsFTPd 3.0.0)\n", 20);
                }
            } else {
                buff = read_line(tmp);
                if (buff == NULL) {
                    printf("Client %d disconnected\n", tmp->fd);
                    socket_list_remove(list, tmp);
                }
                else {
                    printf("Client %d: %s\n", tmp->fd, buff);
                    if (!strcmp(buff, "stop\n"))
                        loop = false;
                }
            }
        }
        free(tab);
    }
    socket_list_destroy(list);
    return (EXIT_SUCCESS);
}