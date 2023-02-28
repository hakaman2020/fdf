/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/15 16:40:47 by hman          #+#    #+#                 */
/*   Updated: 2021/07/29 14:24:29 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../lib/libft/libft.h"
#include "errors.h"

/*
**	this function will be called to exit the program if there is an error
*/

void	exit_on_error(char *s)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(1);
}

/*
**	this function will be called to exit the program if there is an error
**	it will also attempt to close the file descriptor if the file descriptor 
**	is >= 0.
*/

void	exit_on_error_fd(char *s, int fd)
{
	if (fd != -1)
		close(fd);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(1);
}
