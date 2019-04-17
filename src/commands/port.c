/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** port
*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "commands.h"
#include <stdbool.h>
#include <regex.h>
#include "utils.h"
#include "responses.h"
#include "socket.h"
#include "myftp.h"

static int regex_test(char *str)
{
    int res;
    regex_t preg = {0};
    char *str_regex = "^[0-9]{1,3},[0-9]{1,3},[0-9]{1,3}," \
    "[0-9]{1,3},[0-9]{1,3},[0-9]{1,3}$";

    regcomp(&preg, str_regex, REG_NOSUB | REG_EXTENDED);
    res = regexec(&preg, str, 0, NULL, 0);
    regfree(&preg);
    return (res);
}

static bool command_valid(char **arg, socket_t *cli)
{    
    if (array_lenght(arg) < 2 || regex_test(arg[1])) {
        write(cli->fd, CODE_500_PORT, sizeof(CODE_500_PORT) - 1);
        return (false);
    }
    return (true);
}

static in_addr_t get_addr(char *arg)
{
    int t[6] = {0};
    in_addr_t addr = 0;

    sscanf(arg, "%d,%d,%d,%d,%d,%d", &t[0], &t[1], &t[2], &t[3],
    &t[4], &t[5]);
    addr += t[3] * 1 << 24;
    addr += t[2] * 1 << 16;
    addr += t[1] * 1 << 8;
    addr += t[0];
    return (addr);
}

static in_port_t get_port(char *arg)
{
    int t[6] = {0};

    sscanf(arg, "%d,%d,%d,%d,%d,%d", &t[0], &t[1], &t[2], &t[3], &t[4],
    &t[5]);
    return (htons(t[4] * 256 + t[5]));
}

void command_port(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    socket_t *new;

    (void)list;
    (void)path;
    if (!user_connected(cli) || !command_valid(arg, cli))
        return;
    if (((ftp_cli_t *)cli->data)->data_chan) {
        socket_destroy(((ftp_cli_t *)cli->data)->data_chan);
        ((ftp_cli_t *)cli->data)->data_chan = NULL;
    }
    ((ftp_cli_t *)cli->data)->data_chan = socket_create(init_ftp_cli_child,
    end_ftp_cli_child);
    new = ((ftp_cli_t *)cli->data)->data_chan;
    new->data = new;
    new->info.sin_port = get_port(arg[1]);
    new->info.sin_family = AF_INET;
    new->info.sin_addr.s_addr = get_addr(arg[1]);
    ((ftp_cli_t *)cli->data)->mode = ACTIVE;
    write(cli->fd, CODE_200_PORT, sizeof(CODE_200_PORT) - 1);
}