/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   playsound.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:08:23 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/05 19:32:32 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int			ft_playsound(char *filename)
{
	char	command[256];
	int		status;

	sprintf(command, "afplay %s &", filename);
	status = system(command);
	return (0);
}
