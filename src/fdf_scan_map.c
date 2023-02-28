/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_scan_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 16:31:19 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 17:22:24 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../lib/libft/libft.h"
#include "get_next_line.h"
#include "errors.h"
#include "fdf_scan_map.h"

#define GNL_HAS_LINES 1
#define ERROR -1
#define SUCCESS 1

/*
**	it will quickly scan the basic properties of the given file,
**	the amount of lines, the amount of rows. It assumes the file is in the
**	the correct format.
**	will return rows and lines of the file through the arguments
**	RETURN	1 is it was succesfull
**			-1 if there was a error
*/

int	scan_file(char *filename, int *cols, int *rows)
{
	int		fd;
	char	*line;
	int		gnl_return;

	*cols = 0;
	*rows = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_on_error("Something went wrong opening the file");
	gnl_return = GNL_HAS_LINES;
	while (gnl_return == GNL_HAS_LINES)
	{
		gnl_return = get_next_line(fd, &line);
		if (gnl_return == ERROR)
			exit_on_error_fd("Something went wrong reading the file", fd);
		if (gnl_return != 0)
		{
			process_line(line, cols, fd);
			*rows += 1;
		}
		free(line);
		line = NULL;
	}
	close(fd);
	return (SUCCESS);
}

/*
**	this function will count the amount of rows in the line
**	and exit if the file format is not correct in this case
**	each line should have the same amount of rows.
*/

void	process_line(char *line, int *cols, int fd)
{
	static int	set_cols = 0;
	int			amount_cols;

	amount_cols = count_cols(line, fd);
	if (*cols == 0)
		set_cols = amount_cols;
	else if (amount_cols != set_cols)
		exit_on_error_fd("File format is not correct", fd);
	*cols = amount_cols;
}

/*
**	this function will quickly count the amount of rows in the line 
**	RETURN	amount of rows
*/

int	count_cols(char *line, int fd)
{
	char	**numbers;
	int		amount_cols;

	amount_cols = 0;
	numbers = ft_split(line, ' ');
	if (numbers == NULL)
		exit_on_error_fd("Something went wrong during malloc", fd);
	while (numbers[amount_cols] != NULL)
		amount_cols++;
	free_split(numbers);
	return (amount_cols);
}

/*
**	this will free the malloced space from ft_split
*/

void	free_split(char **numbers)
{
	int	i;

	i = 0;
	while (numbers[i] != NULL)
	{
		free(numbers[i]);
		i++;
	}
	free(numbers);
}
