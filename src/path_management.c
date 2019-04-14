/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** path_management
*/

#include <stdlib.h>
#include <string.h>
#include "utils.h"

static char *get_new_path(char *real, char *absolute_root)
{
    char *new = strdup(real + strlen(absolute_root));

    free(absolute_root);
    if (!strcmp(new, "")) {
        free(new);
        new = strdup("/");
    }
    return (new);
}

char *change_dir(char *real_root, char *fake_root, char *path)
{
    char *real = get_path(real_root, fake_root, path);
    char *absolute_root = realpath(real_root, NULL);
    char *new;

    if (real == NULL) {
        free(absolute_root);
        return (NULL);
    }
    if (strstr(real, absolute_root) != real) {
        free(real);
        free(absolute_root);
        return (strdup("/"));
    }
    new = get_new_path(real, absolute_root);
    if (!is_directory(real)) {
        free(new);
        free(real);
        return (NULL);
    }
    free(real);
    return (new);
}

char *get_file(char *real_root, char *fake_root, char *path)
{
    char *real = get_path(real_root, fake_root, path);
    char *absolute_root = realpath(real_root, NULL);
    char *new;

    if (real == NULL) {
        free(absolute_root);
        return (NULL);
    }
    if (strstr(real, absolute_root) != real) {
        free(real);
        free(absolute_root);
        return (NULL);
    }
    new = get_new_path(real, absolute_root);
    if (!is_file(real)) {
        free(new);
        free(real);
        return (NULL);
    }
    free(real);
    return (new);
}