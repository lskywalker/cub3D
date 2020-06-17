/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subfunctions3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 18:05:29 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 01:16:18 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_validchar(char c, t_vars *vars)
{
	if (vars->bonus == 0)
	{
		if (c == '1' || c == '2' || c == '0' || c == ' ' || c == 'N' ||
		c == 'E' || c == 'S' || c == 'W' || c == ' ')
			return (0);
		return (1);
	}
	else
	{
		if (c == '1' || c == '2' || c == '0' || c == ' ' || c == 'N' ||
		c == 'E' || c == 'S' || c == 'W' || c == ' ' || c == '3')
			return (0);
		return (1);
	}
}

void	ft_declare(t_vars *vars)
{
	t_pos		pos;
	t_screen	sc;
	t_colours	colours;
	t_nesw		nesw;

	vars->pos = &pos;
	vars->sc = &sc;
	vars->sc->colours = &colours;
	vars->sc->nesw = &nesw;
	ft_declare2(vars);
}

void	ft_declare2(t_vars *vars)
{
	t_sprite	spr;
	t_floor		floor;
	t_weapon	weapon;
	t_error		error;

	vars->spr = &spr;
	vars->floor = &floor;
	vars->weapon = &weapon;
	vars->error = &error;
	ft_rungame(vars);
}

int		*ft_memcpy(int *dest, int *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void	ft_bzero(void *s, size_t l)
{
	unsigned long	i;
	char			*str;

	str = (char*)s;
	i = 0;
	while (i < l)
	{
		str[i] = 0;
		i++;
	}
}
