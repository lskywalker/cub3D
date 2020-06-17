/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 09:38:37 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/25 12:08:14 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		get_r(unsigned int trgb)
{
	return (trgb & 0XFF00);
}

int		get_g(unsigned int trgb)
{
	return (trgb & 0XFF0000);
}

int		get_b(unsigned int trgb)
{
	return (trgb & 0XFF000000);
}

int		create_trgb(int r, int g, int b)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		return (r << 16 | g << 8 | b);
	else
		return (-10);
}

int		ft_validcolours(char *col)
{
	int i;

	i = 0;
	while (col[i])
	{
		if (ft_isdigit(col[i]))
			i++;
		else
			return (0);
	}
	if (i <= 3)
		return (1);
	return (0);
}
