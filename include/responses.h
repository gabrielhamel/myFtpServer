/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** responses
*/

#ifndef RESPONSES_H
#define RESPONSES_H

#define CODE_220 "220 (vsFTPd 3.0.0)\r\n"
#define CODE_221 "221 Goodbye.\r\n"
#define CODE_230 "230 Login successful.\r\n"
#define CODE_230_ALREADY "230 Already logged in.\r\n"
#define CODE_331 "331 Please specify the password.\r\n"
#define CODE_500 "500 Unknown command.\r\n"
#define CODE_503 "503 Login with USER first.\r\n"
#define CODE_530 "530 Please login with USER and PASS.\r\n"
#define CODE_530_CHANGE "530 Can't change from guest user.\r\n"
#define CODE_530_DENIED "530 Permission denied.\r\n"
#define CODE_530_PASS "530 Login incorrect.\r\n"

#endif