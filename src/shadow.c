/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shadow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 11:07:05 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 02:26:51 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

unsigned int	ft_shadow(unsigned int colour, double distance)
{
	int			r;
	int			g;
	int			b;
	double		multi;

	r = (colour >> 16) & 255;
	g = (colour >> 8) & 255;
	b = (colour) & 255;
	multi = 0.7 * (distance / 2);
	if (multi > 1)
		multi = 1;
	r = (multi * 2) + ((1 - multi) * r);
	g = (multi * 2) + ((1 - multi) * g);
	b = (multi * 2) + ((1 - multi) * b);
	return (r << 16 | g << 8 | b);
}
