/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** responses
*/

#ifndef RESPONSES_H
#define RESPONSES_H

#define CODE_150 "150 Here comes the directory listing.\r\n"
#define CODE_150_UP "150 Ok to send data.\r\n"
#define CODE_150_BIN "150 Opening BINARY mode data" \
" connection for %s (%ld bytes).\r\n"
#define CODE_200_NOOP "200 NOOP ok.\r\n"
#define CODE_200_BIN "200 Switching to Binary mode.\r\n"
#define CODE_200_ASC "200 Switching to ASCII mode.\r\n"
#define CODE_200_PORT "200 PORT command successful. Consider using PASV.\r\n"
#define CODE_213 "213 %ld\r\n"
#define CODE_214_START "214-The following commands are recognized."
#define CODE_214_END "214 Help OK.\r\n"
#define CODE_215 "215 UNIX Type: L8\r\n"
#define CODE_220 "220 (vsFTPd 3.0.0)\r\n"
#define CODE_221 "221 Goodbye.\r\n"
#define CODE_226 "226 Directory send OK.\r\n"
#define CODE_226_UP "226 Transfer complete.\r\n"
#define CODE_227 "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n"
#define CODE_230 "230 Login successful.\r\n"
#define CODE_230_ALREADY "230 Already logged in.\r\n"
#define CODE_250 "250 Directory successfully changed.\r\n"
#define CODE_250_DEL "250 Requested file action okay, completed.\r\n"
#define CODE_257 "257 \"%s\"\r\n"
#define CODE_331 "331 Please specify the password.\r\n"
#define CODE_425 "425 Use PORT or PASV first.\r\n"
#define CODE_500 "500 Unknown command.\r\n"
#define CODE_500_TYPE "500 Unrecognised TYPE command.\r\n"
#define CODE_500_PORT "500 Illegal PORT command.\r\n"
#define CODE_503 "503 Login with USER first.\r\n"
#define CODE_530 "530 Please login with USER and PASS.\r\n"
#define CODE_530_CHANGE "530 Can't change from guest user.\r\n"
#define CODE_530_DENIED "530 Permission denied.\r\n"
#define CODE_530_PASS "530 Login incorrect.\r\n"
#define CODE_550 "550 Failed to change directory.\r\n"
#define CODE_550_FILE "550 Could not get file size.\r\n"
#define CODE_550_OPEN "550 Failed to open file.\r\n"
#define CODE_550_DELE "550 Permission denied.\r\n"
#define CODE_553 "553 Could not create file.\r\n"

#endif