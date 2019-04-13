/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** ioutils
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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