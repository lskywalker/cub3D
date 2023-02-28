/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floorsubfunctions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 10:51:27 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/10 20:59:54 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		ft_floorcalc(t_vars *vars, int y)
{
	vars->floor->raydirx0 = vars->sc->dirx - vars->sc->planex;
	vars->floor->raydiry0 = vars->sc->diry - vars->sc->planey;
	vars->floor->raydirx1 = vars->sc->dirx + vars->sc->planex;
	vars->floor->raydiry1 = vars->sc->diry + vars->sc->planey;
	vars->floor->p = y - vars->sc->screenheight / 2;
	vars->floor->posz = 0.5 * vars->sc->screenheight;
	vars->floor->rowdistance = vars->floor->posz / vars->floor->p;
	vars->floor->floorstepx = vars->floor->rowdistance *
	(vars->floor->raydirx1 - vars->floor->raydirx0) / vars->sc->screenwidth;
	vars->floor->floorstepy = vars->floor->rowdistance *
	(vars->floor->raydiry1 - vars->floor->raydiry0) / vars->sc->screenwidth;
	vars->floor->floorx = vars->pos->posx +
	vars->floor->rowdistance * vars->floor->raydirx0;
	vars->floor->floory = vars->pos->posy +
	vars->floor->rowdistance * vars->floor->raydiry0;
}

void		ft_floordrawxcalc(t_vars *vars)
{
	vars->floor->cellx = (int)(vars->floor->floorx);
	vars->floor->celly = (int)(vars->floor->floory);
	vars->floor->tx = (int)(vars->floor->f_width * (vars->floor->floorx -
	vars->floor->cellx)) & (vars->floor->f_width - 1);
	vars->floor->ty = (int)(vars->floor->f_height * (vars->floor->floory -
	vars->floor->celly)) & (vars->floor->f_height - 1);
	vars->floor->floorx += vars->floor->floorstepx;
	vars->floor->floory += vars->floor->floorstepy;
}

void		ft_floordrawx(t_vars *vars, int x, int y)
{
	int		colour;

	while (x < vars->sc->screenwidth)
	{
		ft_floordrawxcalc(vars);
		if (vars->floor->tex == 1)
			colour = *(int *)(vars->img->addr_f + (vars->floor->ty * vars->
			floor->line_f + vars->floor->tx * (vars->floor->bitspp_f / 8)));
		else
			colour = vars->sc->colours->floor;
		colour = ft_shadow(colour, vars->floor->rowdistance);
		my_mlx_pixel_put(vars->img, x, y, colour);
		if (vars->floor->tex2 == 1)
			colour = *(int *)(vars->img->addr_c + (vars->floor->ty *
		vars->floor->line_c + vars->floor->tx * (vars->floor->bitspp_c / 8)));
		else
			colour = vars->sc->colours->ceiling;
		colour = ft_shadow(colour, vars->floor->rowdistance);
		my_mlx_pixel_put(vars->img, x, vars->sc->screenheight - y - 1, colour);
		x++;
	}
}
