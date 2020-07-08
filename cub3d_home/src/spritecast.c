/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spritecast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 11:40:52 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/06 15:11:06 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_spritecastcalc(t_vars *vars, int i)
{
	vars->spr->spritex = vars->spr->sprite[i][0] - vars->pos->posx;
	vars->spr->spritey = vars->spr->sprite[i][1] - vars->pos->posy;
	vars->spr->invdet = 1.0 / (vars->sc->planex * vars->sc->diry -
	vars->sc->dirx * vars->sc->planey);
	vars->spr->transformx = vars->spr->invdet * (vars->sc->diry *
	vars->spr->spritex - vars->sc->dirx * vars->spr->spritey);
	vars->spr->transformy = vars->spr->invdet * (-vars->sc->planey *
	vars->spr->spritex + vars->sc->planex * vars->spr->spritey);
	vars->spr->spritescreenx = (int)((vars->sc->screenwidth / 2) * (1 +
	vars->spr->transformx / vars->spr->transformy));
	vars->spr->spriteheight = abs((int)(vars->sc->screenheight /
	(vars->spr->transformy)));
	vars->spr->drawstarty = -vars->spr->spriteheight / 2
	+ vars->sc->screenheight / 2;
	if (vars->spr->drawstarty < 0)
		vars->spr->drawstarty = 0;
	vars->spr->drawendy = vars->spr->spriteheight / 2
	+ vars->sc->screenheight / 2;
	if (vars->spr->drawendy >= vars->sc->screenheight)
		vars->spr->drawendy = vars->sc->screenheight - 1;
	vars->spr->spritewidth = abs((int)(vars->sc->screenheight /
	vars->spr->transformy));
	vars->spr->drawstartx = -vars->spr->spritewidth / 2
	+ vars->spr->spritescreenx;
}

void	ft_spritedrawy(t_vars *vars, int stripe, int i)
{
	int d;
	int	y;
	int colour;

	if (vars->spr->transformy > 0 && stripe > 0 && stripe <
	vars->sc->screenwidth && vars->spr->transformy < vars->spr->zbuffer[stripe])
	{
		y = vars->spr->drawstarty + 1;
		while (y < vars->spr->drawendy)
		{
			d = (y) * 256 - vars->sc->screenheight * 128 +
			vars->spr->spriteheight * 128;
			vars->spr->texy = ((d * vars->spr->img_height) /
			vars->spr->spriteheight) / 256;
			colour = *(int*)(vars->img->addr_spr + (vars->spr->texy * vars->
			spr->line_spr + vars->spr->texx * (vars->spr->bitspp_spr / 8)));
			if (colour != 0)
			{
				colour = ft_shadow(colour, vars->spr->sprite[i][2]);
				my_mlx_pixel_put(vars->img, stripe, y, colour);
			}
			y++;
		}
	}
}

void	ft_spritedrawy_2(t_vars *vars, int stripe, int i)
{
	int d;
	int	y;
	int colour;

	if (vars->spr->transformy > 0 && stripe > 0 && stripe <
	vars->sc->screenwidth && vars->spr->transformy < vars->spr->zbuffer[stripe])
	{
		y = vars->spr->drawstarty + 1;
		while (y < vars->spr->drawendy)
		{
			d = (y - vars->spr->vmovescreen) * 256 - vars->sc->screenheight *
			128 + vars->spr->spriteheight * 128;
			vars->spr->texy = ((d * vars->spr->img_height2) /
			vars->spr->spriteheight) / 256;
			colour = *(int*)(vars->img->addr_spr2 + (vars->spr->texy * vars->
			spr->line_spr2 + vars->spr->texx * (vars->spr->bitspp_spr2 / 8)));
			if (colour != 0)
			{
				colour = ft_shadow(colour, vars->spr->sprite[i][2]);
				my_mlx_pixel_put(vars->img, stripe, y, colour);
			}
			y++;
		}
	}
}

void	ft_spritecastx(t_vars *vars, int stripe, int i)
{
	if (vars->spr->sprite[i][3] == 2.0)
	{
		while (stripe < vars->spr->drawendx)
		{
			vars->spr->texx = (int)(256 * (stripe -
			(-vars->spr->spritewidth / 2 + vars->spr->spritescreenx))
			* vars->spr->img_width2 / vars->spr->spritewidth) / 256;
			ft_spritedrawy_2(vars, stripe, i);
			stripe++;
		}
	}
	else
	{
		while (stripe < vars->spr->drawendx)
		{
			vars->spr->texx = (int)(256 * (stripe -
			(-vars->spr->spritewidth / 2 + vars->spr->spritescreenx))
			* vars->spr->img_width / vars->spr->spritewidth) / 256;
			ft_spritedrawy(vars, stripe, i);
			stripe++;
		}
	}
}

void	ft_spritecast(t_vars *vars, int i)
{
	int	stripe;

	if (vars->error->s_found != 0)
	{
		vars->spr->udiv = 3;
		vars->spr->vdiv = 3;
		vars->spr->vmove = 128;
		if (vars->spr->sprite[i][3] == 1.0)
			ft_spritecastcalc(vars, i);
		else
			ft_sprite2castcalc(vars, i);
		if (vars->spr->drawstartx < 0)
			vars->spr->drawstartx = 0;
		vars->spr->drawendx = vars->spr->spritewidth / 2
		+ vars->spr->spritescreenx;
		if (vars->spr->drawendx >= vars->sc->screenwidth)
			vars->spr->drawendx = vars->sc->screenwidth - 1;
		stripe = vars->spr->drawstartx;
		ft_spritecastx(vars, stripe, i);
	}
}
