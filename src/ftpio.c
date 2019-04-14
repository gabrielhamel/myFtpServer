/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** read_command
*/

#include <unistd.h>
#include <stdlib.h>
#include "socket.h"
#include "utils.h"

char **read_lines(socket_t *socket)
{
    char buff[READ_SIZE] = {0};

    if (read(socket->fd, buff, READ_SIZE - 1) == 0)
        return (NULL);
    return (tokenize(buff, "\r\n"));
}