/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** commands
*/

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myftp.h"
#include "responses.h"
#include "utils.h"
#include "commands.h"

command_t commands_g[] = {
    {"CDUP", command_cdup},
    {"CWD", command_cwd},
    {"DELE", command_dele},
    {"HELP", command_help},
    {"LIST", command_list},
    {"MKD", command_mkd},
    {"NOOP", command_noop},
    {"PASS", command_pass},
    {"PASV", command_pasv},
    {"PORT", command_port},
    {"PWD", command_pwd},
    {"QUIT", command_quit},
    {"RETR", command_retr},
    {"RMD", command_rmd},
    {"SIZE", command_size},
    {"STOR", command_stor},
    {"SYST", command_syst},
    {"TYPE", command_type},
    {"USER", command_user}
};

size_t commands_lenght(void)
{
    return (ARRAY_SIZE(commands_g));
}

pid_t duplicate(void)
{
    return (fork());
}

void exec_command(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    for (size_t i = 0; i < commands_lenght() && arg[0]; i++) {
        if (!strcasecmp(commands_g[i].name, arg[0]) && commands_g[i].func) {
            commands_g[i].func(cli, list, arg, path);
            return;
        }
    }
    if (((ftp_cli_t *)cli->data)->lvl != CONNECTED)
        write(cli->fd, CODE_530, sizeof(CODE_530) - 1);
    else
        write(cli->fd, CODE_500, sizeof(CODE_500) - 1);
}

void destroy_ftp_child(socket_list_t *list, socket_t *cli, char **arg)
{
    if (((ftp_cli_t *)cli->data)->mode == ACTIVE)
        socket_destroy(((ftp_cli_t *)cli->data)->data_chan);
    else {
        socket_list_remove(list, ((socket_t *)(((ftp_cli_t *)cli->data)
        ->data_chan->data)));
        socket_list_remove(list, ((ftp_cli_t *)cli->data)->data_chan);
    }
    ((ftp_cli_t *)cli->data)->data_chan = NULL;
    free(list->tab);
    socket_list_destroy_no_close(list);
    destroy_array(arg);
    exit(0);
}

void destroy_ftp_parent(socket_list_t *list, socket_t *cli)
{
    if (((ftp_cli_t *)cli->data)->mode == ACTIVE) {
        socket_destroy_no_close(((ftp_cli_t *)cli->data)->data_chan);
        ((ftp_cli_t *)cli->data)->data_chan = NULL;
        return;
    }
    socket_list_remove_no_close(list, ((socket_t *)(((ftp_cli_t *)cli->data)
    ->data_chan->data)));
    socket_list_remove_no_close(list, ((ftp_cli_t *)cli->data)->data_chan);
    ((ftp_cli_t *)cli->data)->data_chan = NULL;
}