/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** utils
*/

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define EXIT_ERROR 84
#define READ_SIZE 4096

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

char **tokenize(char *str, char *delim);
void destroy_array(char **tab);
size_t array_lenght(char **tab);
void abort_prgm(void);
char *str_add(int nb, ...);
char *get_path(char *real_root, char *false_root, char *to_check);
char *get_path_file(char *real_root, char *false_root, char *to_check);
bool is_directory(char *path);
bool is_file(char *path);

#endif