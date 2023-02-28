/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 17:18:55 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 17:25:05 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../lib/libft/libft.h"
#include "get_next_line.h"
#include "errors.h"
#include "fdf_parser.h"
#include "fdf_scan_map.h"

#define GNL_HAS_LINES 1
#define ERROR -1

/*
**	process the file and create a 2d array of the map and link it to map_data 
*/

int	fdf_parser(char *filename, t_map_data *map_data)
{
	int		cols;
	int		rows;

	cols = 0;
	rows = 0;
	if (scan_file(filename, &cols, &rows) == ERROR)
		return (-1);
	map_data->map = create_map(filename, &cols, &rows);
	map_data->cols = cols;
	map_data->rows = rows;
	return (1);
}

/*
**	this will attempt to create the 2d integer array that represent the map
**	RETURN	2d integer array representing the map
**			NULL if something went wrong
*/

int	**create_map(char *filename, int *cols, int *rows)
{
	int	fd;
	int	**map;

	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		exit_on_error("Something went wrong opening the file.");
	map = malloc((*rows) * sizeof(int *));
	if (map == NULL)
		exit_on_error("Something went wrong opening the file.");
	map = fill_map(fd, cols, map);
	return (map);
}

/*
**	fill_map will fill the 2d integer array by converting the text into integers
*/

int	**fill_map(int fd, int *cols, int **map)
{
	int		gnl_return;
	int		i;
	char	*line;

	gnl_return = GNL_HAS_LINES;
	i = 0;
	line = NULL;
	while (gnl_return == GNL_HAS_LINES)
	{
		gnl_return = get_next_line(fd, &line);
		if (gnl_return == ERROR)
			exit_on_error_fd("Something went wrong reading the file.", fd);
		if (gnl_return != 0)
			map[i] = create_line_values(line, cols, fd);
		free(line);
		line = NULL;
		i++;
	}
	return (map);
}

/*
**	create an array of integers with the line given.
*/

int	*create_line_values(char *line, int *cols, int fd)
{
	char	**values;
	int		*integers;
	int		i;

	integers = malloc(*cols * sizeof(int));
	if (integers == NULL)
		exit_on_error_fd("Something went wrong with malloc", fd);
	values = ft_split(line, ' ');
	if (values == NULL)
		exit_on_error_fd("Something went wrong processing the numbers.", fd);
	i = 0;
	while (values[i] != NULL)
	{
		integers[i] = ft_atoi(values[i]);
		i++;
	}
	free_split(values);
	return (integers);
}

void	parser_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
