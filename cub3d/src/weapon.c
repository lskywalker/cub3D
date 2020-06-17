/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   weapon.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 14:51:44 by lsmit         #+#    #+#                 */
/*   Updated: 2020/06/17 13:43:50 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_knife(t_vars *vars)
{
	unsigned int	colour;
	int		x;
	int		y;
	int		texy;
	int		texx;
	int		padx;
	double	scalefactorx;
	double	scalefactory;

	scalefactorx = vars->sc->screenwidth / vars->weapon->width;
	scalefactory = vars->sc->screenheight / vars->weapon->height;
	padx = (vars->sc->screenwidth - vars->weapon->width) / 2;
	y = vars->sc->screenheight - vars->weapon->height - 1;
	y = 0.7 * vars->sc->screenheight;
	texy = 0;
	texx = 0;
	while (y < vars->sc->screenheight)
	{
		texy = (int)(256 * (y - 1));
		x = padx;
		while (x < vars->weapon->width + (padx - 1) && x < vars->sc->screenwidth)
		{
			colour = *(unsigned int *)(vars->weapon->addr + (texy * vars->weapon->line +
			texx * (vars->weapon->bitspp / 8)));
			if (colour != 0)
				my_mlx_pixel_put(vars->img, x, y, colour);
			x++;
			texx++;
		}
		y++;
		texy++;
	}
}
