/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 20:27:39 by lsmit         #+#    #+#                 */
/*   Updated: 2020/06/17 13:44:42 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		ft_renderframe2(t_vars *vars, int i)
{
	while (i < vars->spr->numsprites)
	{
		ft_spritecast(vars, i);
		i++;
	}
	if (vars->bonus == 1)
	{
		// ft_knife(vars);
		ft_health(vars);
	}
	if (vars->screenshot == 0)
		mlx_put_image_to_window(vars->run->mlx, vars->run->win,
	vars->img->img, 0, 0);
	else
		make_screenshot(vars);
	if (vars->bonus == 1)
		ft_points(vars);
}

void		ft_render_frame(t_vars *vars)
{
	vars->img->img = mlx_new_image(vars->run->mlx, vars->sc->screenwidth,
	vars->sc->screenheight);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
	&vars->img->bits_per_pixel, &vars->img->line_length, &vars->img->endian);
	ft_floorcast(vars);
	ft_wallcast(vars);
	ft_getspritedist(vars);
	ft_sortsprites(vars);
	ft_renderframe2(vars, 0);
	mlx_destroy_image(vars->run->mlx, vars->img->img);
}

void		ft_rungame(t_vars *vars)
{
	t_run		run;
	t_keycheck	key;
	t_data		img;

	vars->run = &run;
	vars->key = &key;
	vars->img = &img;
	ft_init(vars);
	vars->key->space = 0;
	ft_readfile(vars);
	vars->run->mlx = mlx_init();
	vars->run->win = mlx_new_window(vars->run->mlx,
	vars->sc->screenwidth, vars->sc->screenheight, "My Cub3D Game bruv");
	ft_getimgaddr(vars, &img);
	ft_render_frame(vars);
	if (vars->bonus == 1)
		ft_playsound("./sound/scarymusic.wav");
	mlx_loop_hook(vars->run->mlx, ft_keycheck, vars);
	mlx_hook(vars->run->win, 2, 1L << 0, ft_keypress, vars);
	mlx_hook(vars->run->win, 17, 0L, ft_quit, vars);
	mlx_hook(vars->run->win, 3, 1L << 1, ft_keyrelease, vars);
	mlx_loop(vars->run->mlx);
}

int			ft_checkcub(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1])
		{
			if (str[i + 1] == 'c' && str[i + 2])
			{
				if (str[i + 2] == 'u' && str[i + 3])
				{
					if (str[i + 3] == 'b')
						return (0);
				}
			}
		}
		i++;
	}
	return (1);
}

int			main(int amount, char **argv)
{
	t_vars		vars;

	if (amount < 2 || amount > 3)
		ft_error("\e[33mInvalid runcommand\n\e[39m");
	if (amount == 3)
		ft_screenshotcheck(argv[2], &vars);
	else
		vars.screenshot = 0;
	if (ft_checkcub(argv[1]))
		ft_error("\e[33mInvalid filetype\n\e[39m");
	vars.fd = open(argv[1], O_RDONLY);
	if (vars.fd == -1)
		ft_error("\e[33mInvalid filename\n\e[39m");
	ft_declare(&vars);
}
