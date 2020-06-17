/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spritecalc2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 15:43:44 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/12 12:17:17 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_sprite2castcalc(t_vars *vars, int i)
{
	vars->spr->spritex = vars->spr->sprite[i][0] - vars->pos->posx;
	vars->spr->spritey = vars->spr->sprite[i][1] - vars->pos->posy;
	vars->spr->invdet = 1.0 / (vars->sc->planex * vars->sc->diry -
	vars->sc->dirx * vars->sc->planey);
	vars->spr->transformx = vars->spr->invdet * (vars->sc->diry *
	vars->spr->spritex - vars->sc->dirx * vars->spr->spritey);
	vars->spr->transformy = vars->spr->invdet * (-vars->sc->planey *
	vars->spr->spritex + vars->sc->planex * vars->spr->spritey);
	vars->spr->vmovescreen = (vars->spr->vmove / vars->spr->transformy);
	vars->spr->spritescreenx = (int)((vars->sc->screenwidth / 2) * (1 +
	vars->spr->transformx / vars->spr->transformy));
	vars->spr->spriteheight = abs((int)(vars->sc->screenheight /
	(vars->spr->transformy))) / vars->spr->vdiv;
	vars->spr->drawstarty = -vars->spr->spriteheight / 2
	+ vars->sc->screenheight / 2 + vars->spr->vmovescreen;
	if (vars->spr->drawstarty < 0)
		vars->spr->drawstarty = 0;
	vars->spr->drawendy = vars->spr->spriteheight / 2
	+ vars->sc->screenheight / 2 + vars->spr->vmovescreen;
	if (vars->spr->drawendy >= vars->sc->screenheight)
		vars->spr->drawendy = vars->sc->screenheight - 1;
	vars->spr->spritewidth = abs((int)(vars->sc->screenheight /
	(vars->spr->transformy))) / vars->spr->udiv;
	vars->spr->drawstartx = -vars->spr->spritewidth / 2
	+ vars->spr->spritescreenx;
}

void	ft_getspritedist2(t_vars *vars, int i)
{
	if (vars->spr->sprite[i][3] == 1.0 && vars->spr->sprite[i][2] < 3)
	{
		if (vars->spr->sprite[i][4] == 1 && vars->bonus == 1)
			ft_playsound("./sound/scream.wav");
		if (vars->spr->sprite[i][2] < 1 && vars->bonus == 1)
			vars->health -= 2;
		if (vars->spr->sprite[i][2] < 1 && vars->key->space == 1 && vars->bonus == 1)
		{
			ft_playsound("./sound/slice.wav");
			vars->map[(int)vars->spr->sprite[i][1]][(int)vars->spr->sprite[i][0]] = 0;
			vars->spr->sprite[i][0] = 1000;
			vars->spr->sprite[i][1] = 1000;
			vars->spr->sprite[i][2] = 1000;
		}
		if (vars->health <= 0)
		{
			write(1, "\e[31mYou are dead\n\e[39m", 26);
			ft_quit(vars);
		}
		vars->spr->sprite[i][4] += 1;
	}
	if (vars->spr->sprite[i][2] < 0.4 && vars->spr->sprite[i][3] == 2.0)
	{
		ft_playsound("./sound/mariocoin.wav");
		vars->points += 10;
		vars->spr->sprite[i][0] = 0;
		vars->spr->sprite[i][1] = 0;
		vars->spr->sprite[i][2] = 1000;
	}
}

void	ft_getspritedist(t_vars *vars)
{
	double		distx;
	double		disty;
	int			i;

	i = 0;
	while (i < vars->spr->numsprites)
	{
		distx = vars->pos->posx - vars->spr->sprite[i][0];
		if (distx < 0)
			distx *= -1;
		disty = vars->pos->posy - vars->spr->sprite[i][1];
		if (disty < 0)
			disty *= -1;
		vars->spr->sprite[i][2] = sqrt((distx * distx) + (disty * disty));
		if (vars->spr->sprite[i][2] < 3 && vars->spr->sprite[i][4] < 1)
			vars->spr->sprite[i][4] = 1;
		if (vars->spr->sprite[i][2] > 3)
			vars->spr->sprite[i][4] = 0;
		ft_getspritedist2(vars, i);
		i++;
	}
}
