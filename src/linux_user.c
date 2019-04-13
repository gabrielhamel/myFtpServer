/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** linux_user
*/

#include <stdbool.h>
#include <sys/types.h>
#include <pwd.h>
#include <shadow.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>

bool user_is_valid(char *username, char *password)
{
    struct passwd *user;
    struct spwd *pwd;
    char *to_cmp;
    char *tmp;

    user = getpwnam(username);
    endpwent();
    if (user == NULL)
        return (false);
    pwd = getspnam(user->pw_name);
    endspent();
    to_cmp = pwd ? pwd->sp_pwdp : user->pw_passwd;
    tmp = crypt(password, to_cmp);
    if (tmp == NULL || to_cmp == NULL)
        return (false);
    if (!strcmp(tmp, to_cmp))
        return (true);
    return (false);
}