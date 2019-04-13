/*
** EPITECH PROJECT, 2019
** bootstrap
** File description:
** socket
*/

#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdbool.h>

#define SERVER_REFRESH_USEC 1000000

typedef enum socket_type_t {
    SERVER,
    CLIENT
} socket_type_t;

typedef struct socket_t {
    int fd;
    FILE *file;
    struct sockaddr_in info;
    socket_type_t type;
} socket_t;

typedef struct socket_node_t {
    socket_t *socket;
    struct socket_node_t *next;
} socket_node_t;

typedef struct socket_list_t {
    fd_set fdlist;
    socket_node_t *start;
} socket_list_t;

socket_t *socket_server_create(uint16_t port, int max_cli);
socket_t *socket_server_accept_cli(const socket_t *server);
int socket_destroy(socket_t *server);

socket_list_t *socket_list_create(void);
int socket_list_add(socket_list_t *list, socket_t *socket);
int socket_list_remove(socket_list_t *list, socket_t *socket);
int socket_list_destroy(socket_list_t *list);
socket_t *socket_list_get_socket(socket_list_t *list, int fd);
socket_t **socket_list_get_event(socket_list_t *list);

#endif