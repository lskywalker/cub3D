/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   points.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 18:04:03 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 13:59:37 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char		*ft_itoa(int nbr)
{
	long	n;
	size_t	len;
	char	*str;

	n = nbr;
	len = (n > 0) ? 0 : 1;
	n = (n > 0) ? n : -n;
	while (nbr)
		nbr = len++ ? nbr / 10 : nbr / 10;
	str = (char *)malloc(sizeof(str) * len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	while (n > 0)
	{
		*(str + len--) = n % 10 + '0';
		n /= 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
	return (str);
}

void		drawblacksquare2(t_vars *vars, int x, int y, int thickness)
{
	x = (vars->sc->screenwidth * 0.4) - thickness;
	while (x < vars->sc->screenwidth * 0.4)
	{
		y = vars->sc->screenheight * 0.94 - thickness;
		while (y < (vars->sc->screenheight * 0.95) + thickness + 1)
		{
			my_mlx_pixel_put(vars->img, x, y, 0);
			y++;
		}
		x++;
	}
	x = vars->sc->screenwidth * 0.4 + 200;
	while (x < (vars->sc->screenwidth * 0.4 + 200) + thickness + 1)
	{
		y = vars->sc->screenheight * 0.94 - thickness;
		while (y < (vars->sc->screenheight * 0.95) + thickness + 1)
		{
			my_mlx_pixel_put(vars->img, x, y, 0);
			y++;
		}
		x++;
	}
}

void		drawblacksquare(t_vars *vars, int x, int y, int thickness)
{
	y = (vars->sc->screenheight * 0.94) - thickness;
	while (y < vars->sc->screenheight * 0.94)
	{
		x = (vars->sc->screenwidth * 0.4) - thickness;
		while (x < (vars->sc->screenwidth * 0.4 + 200) + thickness + 1)
		{
			my_mlx_pixel_put(vars->img, x, y, 0);
			x++;
		}
		y++;
	}
	y = vars->sc->screenheight * 0.95 + 1;
	while (y < (vars->sc->screenheight * 0.95) + thickness + 1)
	{
		x = (vars->sc->screenwidth * 0.4) - thickness;
		while (x < (vars->sc->screenwidth * 0.4 + 200) + thickness + 1)
		{
			my_mlx_pixel_put(vars->img, x, y, 0);
			x++;
		}
		y++;
	}
	drawblacksquare2(vars, 0, 0, thickness);
}

void		ft_health(t_vars *vars)
{
	int x;
	int	xend;
	int y;
	int	yend;

	y = vars->sc->screenheight * 0.94;
	yend = vars->sc->screenheight * 0.95;
	xend = vars->sc->screenwidth * 0.6;
	while (y < yend)
	{
		x = vars->sc->screenwidth * 0.4;
		xend = x + vars->health * 2;
		while (x < xend)
		{
			my_mlx_pixel_put(vars->img, x, y, 0x0008a828);
			x++;
		}
		while (x < ((vars->sc->screenwidth * 0.4) + 200))
		{
			my_mlx_pixel_put(vars->img, x, y, 0x00a10808);
			x++;
		}
		y++;
	}
	drawblacksquare(vars, 0, 0, 2);
}

void		ft_points(t_vars *vars)
{
	char	*str;

	str = ft_itoa(vars->points);
	mlx_string_put(vars->run->mlx, vars->run->win, vars->sc->screenwidth / 2,
	vars->sc->screenheight * 0.1, 0x0000FF00, str);
	if (vars->points == 100)
	{
		write(1, "\e[32myay 100 points\n\e[39m", 28);
		ft_quit(vars);
	}
	free(str);
}
