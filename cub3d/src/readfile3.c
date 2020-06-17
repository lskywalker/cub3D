/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readfile3.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 01:27:39 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 16:14:57 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_floorcheck2(t_vars *vars, char **str, int a)
{
	if (str[0] && str[1] && str[2] && vars->error->f_found == 1)
	{
		while (a < 3)
			a = (ft_validcolours(str[a]) == 1) ? a += 1 : 10;
		if (a == 3)
		{
			ft_sortcolours(str, vars, 1);
			if (vars->sc->colours->floor == -10)
				return (-1);
		}
		else
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int		ft_ceilingcheck2(t_vars *vars, char **str, int a)
{
	if (str[0] && str[1] && str[2] && vars->error->c_found == 1)
	{
		while (a < 3)
			a = (ft_validcolours(str[a]) == 1) ? a += 1 : 10;
		if (a == 3)
		{
			ft_sortcolours(str, vars, 2);
			if (vars->sc->colours->ceiling == -10)
				return (-1);
		}
		else
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int		ft_checkxpm(char *tex)
{
	int i;

	i = 0;
	while (tex[i])
	{
		if (tex[i] == '.' && tex[i + 1])
		{
			if (tex[i + 1] == 'x' && tex[i + 2])
			{
				if (tex[i + 2] == 'p' && tex[i + 3])
				{
					if (tex[i + 3] == 'm')
						return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
