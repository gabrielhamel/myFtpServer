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
#include "myftp.h"

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

char **tokenize(char *str)
{
    char **tab = realloc(NULL, 2 * sizeof(char *));
    char *tok = strtok(str, " ");
    size_t size = 2;

    if (tok == NULL) {
        free(tab);
        return (NULL);
    }
    tab[0] = strdup(tok);
    tab[1] = NULL;
    while (1) {
        tok = strtok(NULL, " ");
        if (tok == NULL)
            break;
        if (strcmp(tok, "")) {
            tab[size - 1] = strdup(tok);
            tab = realloc(tab, ++size * sizeof(char *));
            tab[size - 1] = NULL;
        }
    }
    return (tab);
}

void destroy_array(char **tab)
{
    for (size_t i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}