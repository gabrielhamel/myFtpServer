/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** ioutils
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void put_token(char ***tab, size_t *size, char **tok)
{
    if (strcmp(*tok, "")) {
        (*tab)[*size - 1] = strdup(*tok);
        *tab = realloc(*tab, ++(*size) * sizeof(char *));
        (*tab)[*size - 1] = NULL;
    }
}

char **tokenize(char *str)
{
    char **tab = realloc(NULL, 2 * sizeof(char *));
    char *tmp = strdup(str);
    char *tok = strtok(tmp, " ");
    size_t size = 2;

    if (tok == NULL) {
        free(tab);
        free(tmp);
        return (NULL);
    }
    tab[0] = strdup(tok);
    tab[1] = NULL;
    while (1) {
        tok = strtok(NULL, " ");
        if (tok == NULL)
            break;
        put_token(&tab, &size, &tok);
    }
    free(tmp);
    return (tab);
}

void destroy_array(char **tab)
{
    for (size_t i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

size_t array_lenght(char **tab)
{
    size_t i = 0;

    if (tab == NULL)
        return (0);
    for (; tab[i] != NULL; i++);
    return (i);
}