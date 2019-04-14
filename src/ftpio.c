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
#include "utils.h"

static bool test_str(char *str, size_t *i, FILE *file)
{
    char *test;
    int ret = fgetc(file);

    if (ret == EOF) {
        str[*i] = '\0';
        return (true);
    }
    str[(*i)++] = ret;
    test = strstr(str, "\r\n");
    if (test) {
        test[0] = '\0';
        return (true);
    }
    test = strstr(str, "\n");
    if (test) {
        test[0] = '\0';
        return (true);
    }
    return (false);
}

char *read_line(socket_t *socket)
{
    int ret = fgetc(socket->file);
    char *str;
    size_t i = 0;
    size_t max_size = BUFF_SIZE;

    if (ret == EOF)
        return (NULL);
    str = malloc(sizeof(char) * max_size);
    memset(str, 0, sizeof(char) * max_size);
    str[i++] = ret;
    while (1) {
        if (i == max_size - 1) {
            max_size += BUFF_SIZE;
            str = realloc(str, sizeof(char) * max_size);
            memset(str, 0, sizeof(char) * max_size);
        }
        if (test_str(str, &i, socket->file))
            break;
    }
    return (str);
}