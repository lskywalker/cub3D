/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 20:27:57 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/26 19:27:27 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_floorcast(t_vars *vars)
{
	int		x;
	int		y;
	int		colour;

	y = 0;
	while (y < vars->sc->screenheight)
	{
		vars->floor->raydirx0 = vars->sc->dirx - vars->sc->planex;
		vars->floor->raydiry0 = vars->sc->diry - vars->sc->planey;
		vars->floor->raydirx1 = vars->sc->dirx + vars->sc->planex;
		vars->floor->raydiry1 = vars->sc->diry + vars->sc->planey;
		vars->floor->p = y - vars->sc->screenheight / 2;
		vars->floor->posz = 0.5 * vars->sc->screenheight;
		vars->floor->rowdistance = vars->floor->posz / vars->floor->p;
		vars->floor->floorstepx = vars->floor->rowdistance * (vars->floor->raydirx1 - vars->floor->raydirx0) / vars->sc->screenwidth;
		vars->floor->floorstepy = vars->floor->rowdistance * (vars->floor->raydiry1 - vars->floor->raydiry0) / vars->sc->screenwidth;
		vars->floor->floorx = vars->pos->posx + vars->floor->rowdistance * vars->floor->raydirx0;
		vars->floor->floory = vars->pos->posy + vars->floor->rowdistance * vars->floor->raydiry0;
		x = 0;
		while (x < vars->sc->screenwidth)
		{
			vars->floor->cellx = (int)(vars->floor->floorx);
			vars->floor->celly = (int)(vars->floor->floory);
			vars->floor->tx = (int)(vars->floor->f_width * (vars->floor->floorx - vars->floor->cellx)) & (vars->floor->f_width - 1);
			vars->floor->ty = (int)(vars->floor->f_height * (vars->floor->floory - vars->floor->celly)) & (vars->floor->f_height - 1);
			vars->floor->floorx += vars->floor->floorstepx;
			vars->floor->floory += vars->floor->floorstepy;
			if (vars->floor->tex == 1)
				colour = *(int *)(vars->img->addr_f + (vars->floor->ty * vars->floor->line_f + vars->floor->tx * (vars->floor->bitspp_f / 8)));
			else
				colour = vars->sc->colours->floor;
			colour = ft_shadow(colour, vars->floor->rowdistance);
			my_mlx_pixel_put(vars->img, x, y, colour);
			if (vars->floor->tex2 == 1)
				colour = *(int *)(vars->img->addr_c + (vars->floor->ty * vars->floor->line_c + vars->floor->tx * (vars->floor->bitspp_c / 8)));
			else
				colour = vars->sc->colours->ceiling;
			colour = ft_shadow(colour, vars->floor->rowdistance);
			my_mlx_pixel_put(vars->img, x, vars->sc->screenheight - y - 1, colour);
			x++;
		}
		y++;
	}
}

void	ft_wallcast(t_vars *vars)
{
	t_ray			r;
	int				x;
	int				y;
	unsigned int	colour;

	x = 0;
	while (x < vars->sc->screenwidth)
	{
		vars->sc->camerax = 2 * x / (double)vars->sc->screenwidth - 1;
		r.raydirx = vars->sc->dirx + vars->sc->planex * vars->sc->camerax;
		r.raydiry = vars->sc->diry + vars->sc->planey * vars->sc->camerax;
		vars->pos->mapx = (int)vars->pos->posx;
		vars->pos->mapy = (int)vars->pos->posy;
		vars->pos->deltadistx = fabs(1 / r.raydirx);
		vars->pos->deltadisty = fabs(1 / r.raydiry);
		vars->pos->hit = 0;
		ft_getstepandsidedist(vars, &r);
		ft_move(vars);
		if (vars->pos->side == 0 || vars->pos->side == 1)
			vars->pos->perpwalldist = (vars->pos->mapx - vars->pos->posx +
			(1 - vars->pos->stepx) / 2) / r.raydirx;
		else
			vars->pos->perpwalldist = (vars->pos->mapy - vars->pos->posy +
			(1 - vars->pos->stepy) / 2) / r.raydiry;
		r.lineheight = (int)(vars->sc->screenheight / vars->pos->perpwalldist);
		r.drawstart = -r.lineheight / 2 + vars->sc->screenheight / 2;
		if (r.drawstart < 0)
			r.drawstart = 0;
		r.drawend = r.lineheight / 2 + vars->sc->screenheight / 2;
		if (r.drawend >= vars->sc->screenheight)
			r.drawend = vars->sc->screenheight - 1;
		vars->sc->texnum = vars->map[vars->pos->mapy][vars->pos->mapx] - 1;
		if (vars->pos->side == 0 || vars->pos->side == 1)
			vars->sc->wallx = vars->pos->posy + vars->pos->perpwalldist * r.raydiry;
		else
			vars->sc->wallx = vars->pos->posx + vars->pos->perpwalldist * r.raydirx;
		vars->sc->wallx -= floor((vars->sc->wallx));
		vars->sc->texx = (int)(vars->sc->wallx * vars->sc->nesw->img_width_n);
		if ((vars->pos->side == 0 || vars->pos->side == 1) && r.raydirx > 0)
			vars->sc->texx = vars->sc->nesw->img_width_n - vars->sc->texx - 1;
		if ((vars->pos->side == 2 || vars->pos->side == 3) && r.raydiry < 0)
			vars->sc->texx = vars->sc->nesw->img_width_n - vars->sc->texx - 1;
		vars->sc->step = 1.0 * vars->sc->nesw->img_height_n / r.lineheight;
		vars->sc->texpos = (r.drawstart - vars->sc->screenheight / 2 + r.lineheight / 2) * vars->sc->step;
		y = r.drawstart;
		while (y < r.drawend)
		{
			vars->sc->texy = (int)vars->sc->texpos & (vars->sc->nesw->img_height_n - 1);
			vars->sc->texpos += vars->sc->step;
			if (vars->pos->side == 0)
				colour = *(unsigned int*)(vars->img->addr_e + (vars->sc->texy * vars->sc->nesw->line_e + vars->sc->texx * (vars->sc->nesw->bitspp_e / 8)));
			if (vars->pos->side == 1)
				colour = *(unsigned int*)(vars->img->addr_w + (vars->sc->texy * vars->sc->nesw->line_w + vars->sc->texx * (vars->sc->nesw->bitspp_w / 8)));
			if (vars->pos->side == 2)
				colour = *(unsigned int*)(vars->img->addr_n + (vars->sc->texy * vars->sc->nesw->line_n + vars->sc->texx * (vars->sc->nesw->bitspp_n / 8)));
			if (vars->pos->side == 3)
				colour = *(unsigned int*)(vars->img->addr_s + (vars->sc->texy * vars->sc->nesw->line_s + vars->sc->texx * (vars->sc->nesw->bitspp_s / 8)));
			colour = ft_shadow(colour, vars->pos->perpwalldist);
			my_mlx_pixel_put(vars->img, x, y, colour);
			y++;
		}
		if (x == 0)
			vars->spr->zbuffer = malloc(sizeof(int*) * vars->sc->screenwidth);
		if (!vars->spr->zbuffer)
			ft_error("\e[33mMalloc failed\n\e[39m");
		vars->spr->zbuffer[x] = vars->pos->perpwalldist;
		x++;
	}
}
