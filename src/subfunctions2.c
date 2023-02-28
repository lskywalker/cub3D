/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subfunctions2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 10:04:03 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/09 17:10:22 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_intlen(int in)
{
	int		count;

	count = 1;
	while (in > 9)
	{
		in /= 10;
		count++;
	}
	return (count);
}

void	ft_free(void **sub, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		free(sub[i]);
		sub[i] = NULL;
		i++;
	}
}

int		ft_emptyline(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[j])
		j++;
	if (i == j)
		return (1);
	return (0);
}

void	ft_getdirection2(t_vars *vars)
{
	if (vars->pos->spawnpos == 'S')
	{
		vars->sc->dirx = 0;
		vars->sc->diry = 1;
		vars->sc->planex = -0.66;
		vars->sc->planey = 0;
	}
	if (vars->pos->spawnpos == 'W')
	{
		vars->sc->dirx = -1;
		vars->sc->diry = 0;
		vars->sc->planex = 0;
		vars->sc->planey = -0.66;
	}
}

void	ft_getdirection(t_vars *vars)
{
	if (vars->pos->spawnpos == 'N')
	{
		vars->sc->dirx = 0;
		vars->sc->diry = -1;
		vars->sc->planex = 0.66;
		vars->sc->planey = 0;
	}
	if (vars->pos->spawnpos == 'E')
	{
		vars->sc->dirx = 1;
		vars->sc->diry = 0;
		vars->sc->planex = 0;
		vars->sc->planey = 0.66;
	}
	ft_getdirection2(vars);
}
