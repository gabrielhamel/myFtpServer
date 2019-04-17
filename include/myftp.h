/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** myftp
*/

#ifndef MYFTP_H
#define MYFTP_H

#include <stdbool.h>
#include "socket.h"

#define DEFAULT_USER "Anonymous"

typedef enum user_level_t {
    NOT_CONNECT,
    JUST_USER,
    CONNECTED
} user_level_t;

typedef enum user_mod_t {
    PASSIVE,
    ACTIVE
} user_mod_t;

typedef struct ftp_cli_t {
    user_level_t lvl;
    char *username;
    char *path;
    socket_t *data_chan;
    user_mod_t mode;
} ftp_cli_t;

typedef struct command_t {
    const char *name;
    void (*func)(socket_t *, socket_list_t *, char **, char *);
} command_t;

extern command_t commands_g[];

bool check_usage(int ac, const char **av);
char **read_lines(socket_t *socket);
void launch_ftp(char *path, uint16_t port);
void manage_event(socket_list_t *list, socket_t **evt_socks, char *path);
void *init_client(const socket_t *cli);
void end_client(const socket_t *cli, void *data);
void *init_cli_child(const socket_t *cli);
void end_cli_child(const socket_t *cli, void *data);
void *init_serv_child(const socket_t *cli);
void end_serv_child(const socket_t *cli, void *data);
void *init_server(const socket_t *cli);
void end_server(const socket_t *cli, void *data);
bool user_is_valid(char *username, char *password);
void exec_command(socket_t *cli, socket_list_t *list, char **arg, char *path);
char *change_dir(char *real_root, char *fake_root, char *path);
char *get_file(char *real_root, char *fake_root, char *path);
void destroy_ftp_child(socket_list_t *list, socket_t *cli);
void destroy_ftp_parent(socket_list_t *list, socket_t *cli);
bool wait_child_client(socket_list_t *list, socket_t *serv);
void *init_ftp_cli_child(const socket_t *cli);
void end_ftp_cli_child(const socket_t *cli, void *data);
void destroy_channel(socket_t *cli);

#endif