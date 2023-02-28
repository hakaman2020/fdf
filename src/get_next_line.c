/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 18:46:34 by hakaman       #+#    #+#                 */
/*   Updated: 2021/06/22 16:56:37 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

/*
**	this function will check the remnant buffer for '\n'.
**	if found it will update *line and update the remnantbuffer and return 1.
** 	if not found it will copy everything into *line and return 0.
*/

static int	check_rmnnt_buff(char **line, char *rmnnt_buff)
{
	char	*tmp_pntr;
	char	*temp_string;

	tmp_pntr = gnl_strchr(rmnnt_buff, '\n');
	if (tmp_pntr != NULL)
	{
		*tmp_pntr = '\0';
		temp_string = *line;
		*line = gnl_strjoin(temp_string, rmnnt_buff);
		free(temp_string);
		if (*line == NULL)
			return (-1);
		gnl_strlcpy(rmnnt_buff, tmp_pntr + 1, gnl_strlen(tmp_pntr + 1) + 1);
		return (1);
	}
	else
	{
		temp_string = *line;
		*line = gnl_strjoin(temp_string, rmnnt_buff);
		free(temp_string);
		if (*line == NULL)
			return (-1);
		return (0);
	}
}

/*
** This function will look in the buffer for the '\n' if found it will add to
** *line, copy the remnant to the remnant buffer and return 1.
** If the buffer doesn't contain a '\n' it wil add to *line and return 0.
*/

static int	process_buffer(char **line, char *rmnnt_buff, char *buffer)
{
	char	*tmp_pntr;
	char	*temp_string;

	tmp_pntr = gnl_strchr(buffer, '\n');
	if (tmp_pntr != NULL)
		*tmp_pntr = '\0';
	temp_string = *line;
	*line = gnl_strjoin(temp_string, buffer);
	free(temp_string);
	if (*line == NULL)
		return (-1);
	if (tmp_pntr != NULL)
	{
		gnl_strlcpy(rmnnt_buff, tmp_pntr + 1, gnl_strlen(tmp_pntr + 1) + 1);
		return (1);
	}
	return (0);
}

/*
** This function will read from the file descriptor check the buffer
** and create the string until '\n' is found or EOF is reached.
*/

static int	read_and_create_line(char **line, char *rmnnt_buff, int fd)
{
	int		amount_read_char;
	char	buffer[BUFFER_SIZE + 1];
	int		done;

	done = 0;
	while (done == 0)
	{
		amount_read_char = read(fd, buffer, BUFFER_SIZE);
		if (amount_read_char == -1)
			return (-1);
		buffer[amount_read_char] = '\0';
		if (amount_read_char == 0)
			done = 1;
		else
			done = process_buffer(line, rmnnt_buff, buffer);
		if (done == -1)
			return (-1);
	}
	if (amount_read_char == 0)
		return (0);
	return (1);
}

/*
**	main function of the get_next_line.
**	making sure that *line is initialized to NULL first, because if *line is
**  not initialized, free-ing it might case undefined behaviour if it is
**	return in case of an error.
**	it will create a empty freeable string first,
**	then check the remnant buffer if there is something in it
**	accordingly.
**	empty the remnant buffer if no '\n' has been found, everything has
** 	been copied to *line.
**	read from the file descriptor to create the string and return the
** 	string and the right output.
*/

int	get_next_line(int fd, char **line)
{
	static char	rmnnt_buff[BUFFER_SIZE];
	int			result;

	if (line != NULL)
		*line = NULL;
	if (BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	*line = malloc(1);
	if (*line == NULL)
		return (-1);
	*line[0] = '\0';
	if (gnl_strlen(rmnnt_buff) > 0)
	{
		result = check_rmnnt_buff(line, rmnnt_buff);
		if (result == -1 || result == 1)
			return (result);
	}
	rmnnt_buff[0] = '\0';
	result = read_and_create_line(line, rmnnt_buff, fd);
	if (result == -1 && *line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	return (result);
}
