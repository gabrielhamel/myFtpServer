/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** read_command
*/

#include <stdio.h>
#include <string.h>
#include "socket.h"
#include "myftp.h"

char *read_line(socket_t *socket)
{
    FILE *file = fdopen(socket->fd, "r");
    size_t readed = 0;
    char *str = NULL;

    if (getline(&str, &readed, file) == -1)
        return (NULL);
    if (strcmp("", str))
        str[strlen(str) - 1] = '\0';
    return (str);
}