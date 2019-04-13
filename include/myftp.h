/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** myftp
*/

#ifndef MYFTP_H
#define MYFTP_H

#define EXIT_ERROR 84

#define MAX_CLI 10
#define READ_SIZE 15
#define DEFAULT_USER "Anonymous"

#include <stdbool.h>

bool check_usage(int ac, const char **av);
void abort_prgm(void);
char *get_next_line(int fd);

#endif