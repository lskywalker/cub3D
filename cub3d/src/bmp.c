/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 00:44:52 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 01:24:05 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	int_to_char(unsigned char *c, int i)
{
	c[0] = (unsigned char)(i);
	c[1] = (unsigned char)(i >> 8);
	c[2] = (unsigned char)(i >> 16);
	c[3] = (unsigned char)(i >> 24);
}

int		bmp_header(int fd, int h, int w, int padsize)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (w * 3 * h) + (padsize * h);
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_to_char(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_to_char(header + 18, w);
	int_to_char(header + 22, h);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

int		bmp_data(int fd, int padsize, t_vars *vars)
{
	unsigned char	zero[3];
	int				x;
	int				y;
	int				pixel;

	y = vars->sc->screenheight - 1;
	ft_bzero(zero, 3);
	while (y >= 0)
	{
		x = 0;
		while (x < vars->sc->screenwidth)
		{
			pixel = *(int *)(vars->img->addr + (y * vars->img->line_length + x *
			(vars->img->bits_per_pixel / 8)));
			if (write(fd, &pixel, 3) < 0)
				return (0);
			if (padsize > 0 && write(fd, &zero, padsize) < 0)
				return (0);
			x++;
		}
		y--;
	}
	return (1);
}

int		take_screenshot(t_vars *vars)
{
	int padsize;
	int fd;

	padsize = (4 - (vars->sc->screenwidth * 3) % 4) % 4;
	if ((fd = open("screenshot.bmp", O_WRONLY |
	O_CREAT, 0777 | O_TRUNC | O_APPEND)) < 0)
		return (0);
	bmp_header(fd, vars->sc->screenheight, vars->sc->screenwidth, padsize);
	bmp_data(fd, padsize, vars);
	close(fd);
	return (1);
}

void	make_screenshot(t_vars *vars)
{
	write(1, "\e[33mSaving screenshot...\n\e[39m", 34);
	if (!take_screenshot(vars))
		ft_error("\e[33mCouldn't create/open screenshot.bmp\n\e[39m");
	write(1, "\e[32mScreenshot saved!\n\e[39m", 31);
	ft_quit(vars);
}
