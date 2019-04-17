/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** read_command
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "socket.h"
#include "utils.h"
#include "myftp.h"

static char *cleanup(char *str)
{
    char *ptr = strchr(str, '\n');

    if (ptr)
        *ptr = '\0';
    if (ptr && *(str + 1) && *(ptr - 1) == '\r')
        *(ptr - 1) = '\0';
    return (str);
}

static char *get_buff(socket_t *socket)
{
    char *tmp = ((ftp_cli_t *)socket->data)->buff;

    ((ftp_cli_t *)socket->data)->buff = strdup("");
    return (tmp);
}

static char *concat_buff(socket_t *socket, char *buff)
{
    char *tmp = ((ftp_cli_t *)socket->data)->buff;

    ((ftp_cli_t *)socket->data)->buff = str_add(2, tmp, buff);
    free(tmp);
    return (((ftp_cli_t *)socket->data)->buff);
}

char *read_line(socket_t *socket)
{
    char buff[READ_SIZE] = {0};
    char *tmp;

    if (!read(socket->fd, buff, READ_SIZE)) {
        tmp = ((ftp_cli_t *)socket->data)->buff;
        if (!strcmp("", tmp))
            return (NULL);
        return (get_buff(socket));
    }
    tmp = concat_buff(socket, buff);
    if (!strcmp("", tmp))
        return (NULL);
    if (strchr(tmp, '\n'))
        return (cleanup(get_buff(socket)));
    return (strdup(""));
}