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
#include "myftp.h"
#include "utils.h"

static bool compare(char *password, char *to_cmp)
{
    char *tmp;

    if (to_cmp == NULL)
        return (false);
    tmp = crypt(password, to_cmp);
    if (tmp == NULL)
        return (false);
    if (!strcmp(tmp, to_cmp))
        return (true);
    return (false);
}

static bool user_is_valid_linux(char *username, char *password)
{
    struct passwd user = {0};
    struct spwd pwd = {0};
    char *to_cmp;
    void *lambda = NULL;
    int ret;
    char user_buff[READ_SIZE] = {0};
    char pwd_buff[READ_SIZE] = {0};

    ret = getpwnam_r(username, &user, user_buff, READ_SIZE,
    (struct passwd **)&lambda);
    endpwent();
    if (ret != 0)
        return (false);
    ret = getspnam_r(user.pw_name, &pwd, pwd_buff, READ_SIZE,
    (struct spwd **)&lambda);
    endspent();
    to_cmp = !ret ? pwd.sp_pwdp : user.pw_passwd;
    return (compare(password, to_cmp));
}

bool user_is_valid(char *username, char *password)
{
    if (password == NULL)
        password = "";
    if (!strcasecmp(username, DEFAULT_USER))
        return (true);
    if (user_is_valid_linux(username, password))
        return (true);
    return (false);
}