/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** read_command
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "socket.h"

char *read_line(socket_t *socket)
{
    size_t readed = 0;
    char *str = NULL;
    char *test;

    if (getline(&str, &readed, socket->file) == -1) {
        if (str != NULL)
            free(str);
        return (NULL);
    }
    test = strstr(str, "\r\n");
    if (test)
        test[0] = '\0';
    test = strstr(str, "\n");
    if (test)
        test[0] = '\0';
    return (str);
}