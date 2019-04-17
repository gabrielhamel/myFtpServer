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

typedef enum socket_type_t {
    SERVER,
    CLIENT
} socket_type_t;

typedef struct socket_t {
    int fd;
    struct sockaddr_in info;
    socket_type_t type;
    void *data;
    void *(*ctor)(const struct socket_t *);
    void (*dtor)(const struct socket_t *, void *);
} socket_t;

typedef struct socket_node_t {
    socket_t *socket;
    struct socket_node_t *next;
} socket_node_t;

typedef struct socket_list_t {
    fd_set fdlist;
    socket_node_t *start;
    socket_t **tab;
} socket_list_t;

socket_t *socket_server_create(uint16_t port,
void *(*ctor)(const socket_t *), void (*dtor)(const socket_t *, void *));
socket_t *socket_server_accept_cli(socket_t *server,
void *(*ctor)(const socket_t *), void (*dtor)(const socket_t *, void *));
socket_t *socket_client_create(uint16_t port, uint32_t ipaddr,
void *(*ctor)(const socket_t *), void (*dtor)(const socket_t *, void *));
socket_t *socket_create(void *(*ctor)(const socket_t *),
void (*dtor)(const socket_t *, void *));
uint32_t convert_ip(char *ip);
int socket_destroy(socket_t *socket);
int socket_destroy_no_close(socket_t *socket);
int socket_list_destroy_no_close(socket_list_t *list);
int socket_list_remove_no_close(socket_list_t *list, socket_t *socket);
socket_list_t *socket_list_create(void);
int socket_list_add(socket_list_t *list, socket_t *socket);
int socket_list_remove(socket_list_t *list, socket_t *socket);
int socket_list_destroy(socket_list_t *list);
socket_t *socket_list_get_socket(socket_list_t *list, int fd);
socket_t **socket_list_get_event(socket_list_t *list);

#endif