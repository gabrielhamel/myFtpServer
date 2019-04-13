/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** utils
*/

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

#define EXIT_ERROR 84

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

char **tokenize(char *str);
void destroy_array(char **tab);
size_t array_lenght(char **tab);
void abort_prgm(void);

#endif