/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** main
*/

#include <stdlib.h>
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

    if (check_usage(ac, (const char **)av) == false)
        abort_prgm();
    port = strtol(av[1], NULL, 10);
    tmp = socket_server_create(port, MAX_CLI);
    if (tmp == NULL)
        abort_prgm();
    printf("New server %d\n", tmp->fd);
    socket_list_add(list, tmp);
    while (1) {
        tmp = socket_list_get_event(list);
        if (tmp != NULL) {
            if (tmp->type == SERVER) {
                tmp = socket_server_accept_cli(tmp);
                if (tmp != NULL) {
                    printf("New client %d\n", tmp->fd);
                    socket_list_add(list, tmp);
                }
            } else {
                buff = get_next_line(tmp->fd);
                if (buff) {
                    printf("Client %d: %s\n", tmp->fd, buff);
                    if (!strcmp(buff, "stop")) {
                        free(buff);
                        break;
                    }
                    free(buff);
                }
                else {
                    printf("Client %d disconnected\n", tmp->fd);
                    socket_list_remove(list, tmp);
                }
            }
        }
    }
    socket_list_destroy(list);
    return (EXIT_SUCCESS);
}