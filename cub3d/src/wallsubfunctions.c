/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wallsubfunctions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 10:16:39 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/10 21:06:11 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		ft_move(t_vars *vars)
{
	vars->pos->hit = 0;
	while (vars->pos->hit == 0)
	{
		if (vars->pos->sidedistx < vars->pos->sidedisty)
		{
			if (vars->pos->stepx < 0)
				vars->pos->side = 1;
			else
				vars->pos->side = 0;
			vars->pos->sidedistx += vars->pos->deltadistx;
			vars->pos->mapx += vars->pos->stepx;
		}
		else
		{
			if (vars->pos->stepy < 0)
				vars->pos->side = 2;
			else
				vars->pos->side = 3;
			vars->pos->sidedisty += vars->pos->deltadisty;
			vars->pos->mapy += vars->pos->stepy;
		}
		if (vars->map[vars->pos->mapy][vars->pos->mapx] == 1)
			vars->pos->hit = 1;
	}
}

void		ft_getstepandsidedist(t_vars *vars, t_ray *r)
{
	if (r->raydirx < 0)
	{
		vars->pos->stepx = -1;
		vars->pos->sidedistx = (vars->pos->posx - vars->pos->mapx) *
		vars->pos->deltadistx;
	}
	else
	{
		vars->pos->stepx = 1;
		vars->pos->sidedistx = (vars->pos->mapx + 1.0 - vars->pos->posx) *
		vars->pos->deltadistx;
	}
	if (r->raydiry < 0)
	{
		vars->pos->stepy = -1;
		vars->pos->sidedisty = (vars->pos->posy - vars->pos->mapy) *
		vars->pos->deltadisty;
	}
	else
	{
		vars->pos->stepy = 1;
		vars->pos->sidedisty = (vars->pos->mapy + 1.0 - vars->pos->posy) *
		vars->pos->deltadisty;
	}
}

void		ft_wallcalc(t_vars *vars, t_ray *ray)
{
	if (vars->pos->side == 0 || vars->pos->side == 1)
		vars->pos->perpwalldist = (vars->pos->mapx - vars->pos->posx +
		(1 - vars->pos->stepx) / 2) / ray->raydirx;
	else
		vars->pos->perpwalldist = (vars->pos->mapy - vars->pos->posy +
		(1 - vars->pos->stepy) / 2) / ray->raydiry;
	ray->lineheight = (int)(vars->sc->screenheight / vars->pos->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + vars->sc->screenheight / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + vars->sc->screenheight / 2;
	if (ray->drawend >= vars->sc->screenheight)
		ray->drawend = vars->sc->screenheight - 1;
	vars->sc->texnum = vars->map[vars->pos->mapy][vars->pos->mapx] - 1;
	if (vars->pos->side == 0 || vars->pos->side == 1)
		vars->sc->wallx = vars->pos->posy + vars->pos->perpwalldist *
		ray->raydiry;
	else
		vars->sc->wallx = vars->pos->posx + vars->pos->perpwalldist *
		ray->raydirx;
	vars->sc->wallx -= floor((vars->sc->wallx));
	vars->sc->texx = (int)(vars->sc->wallx * vars->sc->nesw->img_width_n);
}

void		ft_drawwally(t_vars *vars, int drawend, int x, int y)
{
	int		colour;

	while (y < drawend)
	{
		vars->sc->texy = (int)vars->sc->texpos &
		(vars->sc->nesw->img_height_n - 1);
		vars->sc->texpos += vars->sc->step;
		if (vars->pos->side == 0)
			colour = *(int*)(vars->img->addr_e + (vars->sc->texy * vars->sc->
			nesw->line_e + vars->sc->texx * (vars->sc->nesw->bitspp_e / 8)));
		if (vars->pos->side == 1)
			colour = *(int*)(vars->img->addr_w + (vars->sc->texy * vars->sc->
			nesw->line_w + vars->sc->texx * (vars->sc->nesw->bitspp_w / 8)));
		if (vars->pos->side == 2)
			colour = *(int*)(vars->img->addr_n + (vars->sc->texy * vars->sc->
			nesw->line_n + vars->sc->texx * (vars->sc->nesw->bitspp_n / 8)));
		if (vars->pos->side == 3)
			colour = *(int*)(vars->img->addr_s + (vars->sc->texy * vars->sc->
			nesw->line_s + vars->sc->texx * (vars->sc->nesw->bitspp_s / 8)));
		colour = ft_shadow(colour, vars->pos->perpwalldist);
		my_mlx_pixel_put(vars->img, x, y, colour);
		y++;
	}
}

void		ft_wallcameracalc(t_vars *vars, t_ray *ray, int x)
{
	vars->sc->camerax = 2 * x / (double)vars->sc->screenwidth - 1;
	ray->raydirx = vars->sc->dirx + vars->sc->planex * vars->sc->camerax;
	ray->raydiry = vars->sc->diry + vars->sc->planey * vars->sc->camerax;
	vars->pos->mapx = (int)vars->pos->posx;
	vars->pos->mapy = (int)vars->pos->posy;
	vars->pos->deltadistx = fabs(1 / ray->raydirx);
	vars->pos->deltadisty = fabs(1 / ray->raydiry);
}
