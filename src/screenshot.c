/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screenshot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:57:41 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/10 21:03:58 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int			ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void		ft_screenshotcheck(char *input, t_vars *vars)
{
	if (ft_strcmp(input, "--save") != 0)
		ft_error("\e[33mInvalid parameter after filename\n\e[39m");
	vars->screenshot = 1;
}
