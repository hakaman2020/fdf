/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_parser.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 21:56:45 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 17:25:15 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_PARSER_H
# define FDF_PARSER_H

# include "fdf_structs.h"

int		fdf_parser(char *filename, t_map_data *map_data);
int		**create_map(char *filename, int *cols, int *rows);
int		**fill_map(int fd, int *cols, int **map);
int		*create_line_values(char *line, int *cols, int fd);
void	parser_free_split(char **split);
#endif