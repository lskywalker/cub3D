/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 11:25:24 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/13 19:20:36 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_press_w_s(t_vars *vars)
{
	if (vars->key->w == 1)
	{
		if (vars->map[(int)vars->pos->posy]
		[(int)(vars->pos->posx + vars->sc->dirx * 0.5)] == 0)
			vars->pos->posx += vars->sc->dirx * vars->pos->movespeed;
		if (vars->map[(int)(vars->pos->posy + vars->sc->diry * 0.5)]
		[(int)vars->pos->posx] == 0)
			vars->pos->posy += vars->sc->diry * vars->pos->movespeed;
	}
	if (vars->key->s == 1)
	{
		if (vars->map[(int)vars->pos->posy][(int)(vars->pos->posx -
		vars->sc->dirx * 0.5)] == 0)
			vars->pos->posx -= vars->sc->dirx * vars->pos->movespeed;
		if (vars->map[(int)(vars->pos->posy - vars->sc->diry * 0.5)]
		[(int)vars->pos->posx] == 0)
			vars->pos->posy -= vars->sc->diry * vars->pos->movespeed;
	}
}

void	ft_press_a_d(t_vars *vars)
{
	if (vars->key->a == 1)
	{
		if (vars->map[(int)(vars->pos->posy - vars->sc->planey * 0.5)]
		[(int)vars->pos->posx] == 0)
			vars->pos->posy -= vars->sc->dirx * vars->pos->movespeed;
		if (vars->map[(int)vars->pos->posy][(int)(vars->pos->posx -
		vars->sc->planex * 0.5)] == 0)
			vars->pos->posx += vars->sc->diry * vars->pos->movespeed;
	}
	if (vars->key->d == 1)
	{
		if (vars->map[(int)(vars->pos->posy + vars->sc->planey * 0.5)]
		[(int)vars->pos->posx] == 0)
			vars->pos->posy += vars->sc->dirx * vars->pos->movespeed;
		if (vars->map[(int)vars->pos->posy][(int)(vars->pos->posx +
		vars->sc->planex * 0.5)] == 0)
			vars->pos->posx -= vars->sc->diry * vars->pos->movespeed;
	}
}

void	ft_rotateleft(t_vars *vars)
{
	if (vars->key->left == 1)
	{
		vars->sc->olddirx = vars->sc->dirx;
		vars->sc->dirx = vars->sc->dirx * cos(-vars->pos->rotspeed) -
		vars->sc->diry * sin(-vars->pos->rotspeed);
		vars->sc->diry = vars->sc->olddirx * sin(-vars->pos->rotspeed) +
		vars->sc->diry * cos(-vars->pos->rotspeed);
		vars->sc->oldplanex = vars->sc->planex;
		vars->sc->planex = vars->sc->planex * cos(-vars->pos->rotspeed) -
		vars->sc->planey * sin(-vars->pos->rotspeed);
		vars->sc->planey = vars->sc->oldplanex * sin(-vars->pos->rotspeed) +
		vars->sc->planey * cos(-vars->pos->rotspeed);
	}
}

void	ft_rotateright(t_vars *vars)
{
	if (vars->key->right == 1)
	{
		vars->sc->olddirx = vars->sc->dirx;
		vars->sc->dirx = vars->sc->dirx * cos(vars->pos->rotspeed) -
		vars->sc->diry * sin(vars->pos->rotspeed);
		vars->sc->diry = vars->sc->olddirx * sin(vars->pos->rotspeed) +
		vars->sc->diry * cos(vars->pos->rotspeed);
		vars->sc->oldplanex = vars->sc->planex;
		vars->sc->planex = vars->sc->planex * cos(vars->pos->rotspeed) -
		vars->sc->planey * sin(vars->pos->rotspeed);
		vars->sc->planey = vars->sc->oldplanex * sin(vars->pos->rotspeed) +
		vars->sc->planey * cos(vars->pos->rotspeed);
	}
}
