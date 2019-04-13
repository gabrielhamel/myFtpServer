/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** myftp
*/

#ifndef MYFTP_H
#define MYFTP_H

#define EXIT_ERROR 84

#define MAX_CLI 1024
#define DEFAULT_USER "Anonymous"

#include <stdbool.h>
#include "socket.h"

bool check_usage(int ac, const char **av);
void abort_prgm(void);
char *read_line(socket_t *socket);
char **tokenize(char *str);
void destroy_array(char **tab);
void launch_ftp(char *path, uint16_t port);
void manage_event(socket_list_t *list, socket_t **evt_socks, char *path);

void *init_client(const socket_t *cli);
void end_client(const socket_t *cli, void *data);

void *init_server(const socket_t *cli);
void end_server(const socket_t *cli, void *data);

#endif