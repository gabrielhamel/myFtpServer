/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** commands
*/

#include <sys/types.h>
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
    {"NOOP", command_noop},
    {"PASS", command_pass},
    {"PASV", command_pasv},
    {"PORT", NULL},
    {"PWD", command_pwd},
    {"QUIT", command_quit},
    {"RETR", NULL},
    {"SIZE", command_size},
    {"STOR", NULL},
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
    for (size_t i = 0; i < commands_lenght(); i++) {
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