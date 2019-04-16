/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** path
*/

#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

bool is_directory(char *path)
{
    struct stat info = {0};

    if (path == NULL)
        return (false);
    if (stat(path, &info) == -1)
        return (false);
    if (S_ISDIR(info.st_mode))
        return (true);
    return (false);
}

bool is_file(char *path)
{
    struct stat info = {0};

    if (path == NULL)
        return (false);
    if (stat(path, &info) == -1)
        return (false);
    if (S_ISREG(info.st_mode))
        return (true);
    return (false);
}

char *get_path(char *real_root, char *false_root, char *to_check)
{
    char *concat;
    char *test;

    if (to_check == NULL)
        return (NULL);
    if (strchr(to_check, '/') == to_check)
        false_root = "/";
    concat = str_add(5, real_root, "/", false_root, "/", to_check);
    test = realpath(concat, NULL);
    free(concat);
    return (test);
}

char *get_path_file(char *real_root, char *false_root, char *to_check)
{
    char *concat;
    char *test;

    if (to_check == NULL)
        return (NULL);
    if (strchr(to_check, '/') == to_check)
        false_root = "/";
    concat = str_add(5, real_root, "/", false_root, "/", to_check);
    test = realpath(dirname(concat), NULL);
    free(concat);
    concat = str_add(3, test, "/", to_check);
    free(test);
    return (concat);
}