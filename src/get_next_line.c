/*
** EPITECH PROJECT, 2018
** Get_next_line
** File description:
** Get the next line in a file descriptor
*/

#include <stdlib.h>
#include <unistd.h>
#include "myftp.h"

static int check_end(char *buffer, int mode)
{
	int counter = -1;
	int size = -1;

	if (buffer == NULL)
		size = 0;
	else
		while (buffer[++size] != '\0');
	if (mode)
		return (size);
	while (++counter < size)
		if (buffer[counter] == '\n')
			return (1);
	return (0);
}

static char *clean_buffer(char *str)
{
	int counter = -1;
	char *buffer = NULL;

	if (str == NULL) {
		buffer = malloc(sizeof(char) * (READ_SIZE + 1));
		if (!buffer)
			return (NULL);
		while (++counter < READ_SIZE + 1)
			buffer[counter] = '\0';
		return (buffer);
	}
	else
		while (str[++counter] != '\0')
			str[counter] = '\0';
	return (NULL);
}

char *add_str(char *base, char *to_add, char fre)
{
	char *end = NULL;
	int counter = -1;
	int size_b = check_end(base, 1);
	int size_a = check_end(to_add, 1);

	end = malloc(sizeof(char) * (size_a + size_b + 1));
	if (!end)
		return (NULL);
	end[size_a + size_b] = '\0';
	while (++counter < size_b)
		end[counter] = base[counter];
	if (base != NULL)
		free(base);
	counter = -1;
	while (++counter < size_a)
		end[size_b + counter] = to_add[counter];
	(fre == 'f') ? free(to_add) : clean_buffer(to_add);
	return (end);
}

static char *init_next(char *line, char *str)
{
	int i;
	char *res = NULL;
	int size = check_end(line, 1);

	if (str != NULL)
		free(str);
	if (line == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
		if (line[i] == '\n') {
			(i != size - 1) ? res =
			add_str(NULL, line + 1 + i, 0) : 0;
			line[i] = '\0';
			break;
		}
	if (res != NULL)
		return (res);
	return (NULL);
}

char *get_next_line(int fd)
{
	char *line = NULL;
	char *buffer = clean_buffer(NULL);
	int readed = READ_SIZE;
	static char *res = NULL;

	if (fd < 0 || READ_SIZE < 1 || !buffer) {
		(buffer != NULL) ? free(buffer) : 0;
		return (NULL);
	}
	else if (res != NULL)
		line = add_str(line, res, 'f');
	while (!check_end(line, 0) && readed == READ_SIZE) {
		readed = read(fd, buffer, READ_SIZE);
		line = (readed != 0) ? add_str(line, buffer, 0) : line;
		if (!line || readed == -1) {
			(buffer != NULL) ? free(buffer) : 0;
			return (NULL);
		}
	}
	res = init_next(line, buffer);
	return (line);
}