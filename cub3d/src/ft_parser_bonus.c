/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 11:01:32 by lsmit         #+#    #+#                 */
/*   Updated: 2020/06/17 15:55:07 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		ft_mapparser2(t_vars *vars, char file, int j)
{
	if (file == 'N' || file == 'E' ||
	file == 'S' || file == 'W')
	{
		vars->pos->spawnpos = file;
		vars->pos->posx = vars->mapx + 0.5;
		vars->pos->posy = j + 0.5;
		file = '0';
		vars->error->pos_found++;
	}
	if (file == '1' || file == '2' || file == '0' || file == '3')
	{
		vars->map[j][vars->mapx] = file - '0';
		if (vars->map[j][vars->mapx] == 2)
		{
			sprite(vars, vars->mapx, j, 1.0);
			vars->spr->numsprites++;
		}
		if (vars->map[j][vars->mapx] == 3)
		{
			sprite(vars, vars->mapx, j, 2.0);
			vars->map[j][vars->mapx] = 0;
			vars->spr->numsprites++;
		}
		vars->mapx++;
	}
}

void		ft_mapparser(t_vars *vars, char *file, int j)
{
	int			i;

	i = 0;
	vars->mapx = 0;
	vars->map = ft_reallocmap(vars->map, j + 1, vars);
	vars->maplinelen = ft_strlen(file) + 1;
	vars->linelen = ft_realloc(vars->linelen, j + 1);
	if (!vars->linelen || !vars->map)
		ft_error("\e[33mMalloc failed\n\e[39m");
	vars->linelen[j] = vars->maplinelen;
	vars->map[j] = malloc(sizeof(int) * vars->maplinelen);
	if (!vars->map[j])
		ft_error("\e[33mMalloc failed\n\e[39m");
	while (file[i] != '\0')
	{
		if (ft_validchar(file[i], vars))
			ft_error("\e[33mInvalid character in map\n\e[39m");
		if (file[i] == ' ')
		{
			vars->map[j][vars->mapx] = 8;
			vars->mapx++;
		}
		ft_mapparser2(vars, file[i], j);
		i++;
	}
}

int			ft_outofmap(t_vars *vars, int x, int y)
{
	static int i = 0;

	i++;
	if (i > 80000)
		ft_error("\e[33mMap is too big\n\e[39m");
	if (vars->linelen[y + 1] < vars->linelen[y] &&
	x > vars->linelen[y + 1] && y > vars->mapheight)
		return (1);
	return (0);
}

void		ft_checkmapvalid(t_vars *vars, int x, int y)
{
	if (ft_outofmap(vars, x, y))
		ft_error("\e[33mInvalid map\n\e[39m");
	if (vars->map[y][x] == 0 || vars->map[y][x] == 8)
	{
		if (vars->map[y][x] == 8)
			ft_error("\e[33mInvalid map\n\e[39m");
		if (x == 0 || x >= vars->linelen[y] || y == 0 || y == vars->mapheight)
			ft_error("\e[33mInvalid map\n\e[39m");
		vars->map[y][x] = 9;
		ft_checkmapvalid(vars, x, y + 1);
		ft_checkmapvalid(vars, x, y - 1);
		ft_checkmapvalid(vars, x + 1, y);
		ft_checkmapvalid(vars, x - 1, y);
		ft_checkmapvalid(vars, x + 1, y + 1);
		ft_checkmapvalid(vars, x + 1, y - 1);
		ft_checkmapvalid(vars, x - 1, y + 1);
		ft_checkmapvalid(vars, x - 1, y - 1);
	}
	if (vars->map[y][x] == 2 && ft_outofmap(vars, x, y))
		ft_error("\e[33mInvalid map\n\e[39m");
}

void		ft_resetmap(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->mapheight)
	{
		x = 0;
		while (x < vars->linelen[y])
		{
			if (vars->map[y][x] == 9)
				vars->map[y][x] = 0;
			x++;
		}
		y++;
	}
}
