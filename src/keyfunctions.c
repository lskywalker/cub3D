/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyfunctions.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 11:19:39 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 21:02:30 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_quit(t_vars *vars)
{
	char	command[256];
	int		status;

	mlx_destroy_window(vars->run->mlx, vars->run->win);
	if (vars->bonus == 1)
	{
		sprintf(command, "killall afplay");
		status = system(command);
	}
	exit(0);
}

int		ft_keypress(int keycode, t_vars *vars)
{
	if (keycode == 53)
		ft_quit(vars);
	if (keycode == 13)
		vars->key->w = 1;
	if (keycode == 1)
		vars->key->s = 1;
	if (keycode == 0)
		vars->key->a = 1;
	if (keycode == 2)
		vars->key->d = 1;
	if (keycode == 123)
		vars->key->left = 1;
	if (keycode == 124)
		vars->key->right = 1;
	if (keycode == 49 && vars->bonus == 1 && vars->key->space == 0)
	{
		vars->key->space = 1;
		ft_playsound("./sound/slice.wav");
	}
	return (0);
}

int		ft_keyrelease(int keycode, t_vars *vars)
{
	if (keycode == 13)
		vars->key->w = 0;
	if (keycode == 1)
		vars->key->s = 0;
	if (keycode == 0)
		vars->key->a = 0;
	if (keycode == 2)
		vars->key->d = 0;
	if (keycode == 123)
		vars->key->left = 0;
	if (keycode == 124)
		vars->key->right = 0;
	if (keycode == 49)
		vars->key->space = 0;
	return (0);
}

int		ft_keycheck(t_vars *vars)
{
	vars->pos->movespeed = 0.08;
	vars->pos->rotspeed = 0.06;
	if (vars->key->w == 1 || vars->key->s == 1 ||
	vars->key->a == 1 || vars->key->d == 1 ||
	vars->key->left == 1 || vars->key->right == 1)
	{
		ft_press_w_s(vars);
		ft_press_a_d(vars);
		ft_rotateleft(vars);
		ft_rotateright(vars);
		ft_render_frame(vars);
	}
	return (0);
}

void	ft_init(t_vars *vars)
{
	vars->key->w = 0;
	vars->key->a = 0;
	vars->key->s = 0;
	vars->key->d = 0;
	vars->key->left = 0;
	vars->key->right = 0;
	vars->sc->screenwidth = 0;
	vars->sc->screenheight = 0;
	vars->error->r_found = 0;
	vars->error->f_found = 0;
	vars->error->c_found = 0;
	vars->error->fcol_found = 0;
	vars->error->ccol_found = 0;
	vars->error->no_found = 0;
	vars->error->so_found = 0;
	vars->error->ea_found = 0;
	vars->error->we_found = 0;
	vars->error->pos_found = 0;
	vars->error->map_error = 0;
	vars->error->s_found = 0;
	vars->pos->spawnpos = 'U';
	vars->error->map_found = 0;
	vars->maplinelen = 0;
	vars->points = 0;
	vars->health = 100;
}
