/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 10:51:13 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/10 16:49:47 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_swaparray(t_vars *vars, int i)
{
	double *temp;

	temp = vars->spr->sprite[i];
	vars->spr->sprite[i] = vars->spr->sprite[i - 1];
	vars->spr->sprite[i - 1] = temp;
}

void	ft_sortsprites(t_vars *vars)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (done == 0)
	{
		done = 1;
		while (i < vars->spr->numsprites - 1)
		{
			i++;
			if (vars->spr->sprite[i][2] > vars->spr->sprite[i - 1][2])
			{
				ft_swaparray(vars, i);
				done = 0;
			}
		}
	}
}

double	sprite(t_vars *vars, int x, int y, double type)
{
	vars->spr->sprite = ft_reallocsprit(vars->spr->sprite,
	vars->spr->numsprites + 1);
	if (!vars->spr->sprite)
		ft_error("\e[33mMalloc failed\n\e[39m");
	vars->spr->sprite[vars->spr->numsprites] = malloc(sizeof(double*) * 5);
	if (!vars->spr->sprite[vars->spr->numsprites])
		ft_error("\e[33mMalloc failed\n\e[39m");
	vars->spr->sprite[vars->spr->numsprites][0] = x + 0.5;
	vars->spr->sprite[vars->spr->numsprites][1] = y + 0.5;
	vars->spr->sprite[vars->spr->numsprites][3] = type;
	vars->spr->sprite[vars->spr->numsprites][4] = 0;
	return (0);
}
