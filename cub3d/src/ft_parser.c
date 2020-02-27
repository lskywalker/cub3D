/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 11:01:32 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/26 19:27:31 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_mapparser(t_vars *vars, char *file, int j)
{
	int			i;
	int			x;

	i = 0;
	x = 0;
	vars->map = ft_reallocmap(vars->map, j + 1, vars);
	vars->maplinelen = ft_strlen(file) + 1;
	vars->linenumb = ft_realloc(vars->linenumb, j + 1);
	if (!vars->linenumb || !vars->map)
		ft_error("\e[33mMalloc failed\n\e[39m");
	vars->linenumb[j] = vars->maplinelen;
	vars->map[j] = malloc(sizeof(int) * vars->maplinelen);
	if (!vars->map[j])
		ft_error("\e[33mMalloc failed\n\e[39m");
	while (file[i])
	{
		if (file[i] == 'N' || file[i] == 'E' ||
		file[i] == 'S' || file[i] == 'W')
		{
			vars->pos->spawnpos = file[i];
			vars->pos->posx = x + 0.5;
			vars->pos->posy = j + 0.5;
			file[i] = '0';
			vars->error->pos_found++;
		}
		if (file[i] != ' ')
		{
			vars->map[j][x] = file[i] - '0';
			if (vars->map[j][x] == 2)
			{
				sprite(vars, x, j);
				vars->spr->numsprites++;
			}
			x++;
		}
		i++;
	}
	vars->mapheight = j + 1;
}

int		ft_outofmap(t_vars *vars, int x, int y)
{
	if (vars->linenumb[y + 1] < vars->linenumb[y] &&
	x > vars->linenumb[y + 1] && y >= vars->mapheight)
		return (1);
	return (0);
}

void	ft_checkmapvalid(t_vars *vars, int x, int y)
{
	if (ft_outofmap(vars, x, y))
		ft_error("\e[33mInvalid map\n\e[39m");
	if (vars->map[y][x] == 0)
	{
		if (x == 0 || x >= vars->linenumb[y] || y == 0 || y == vars->mapheight)
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

void	ft_resetmap(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->mapheight)
	{
		x = 0;
		while (x < vars->linenumb[y])
		{
			if (vars->map[y][x] == 9)
				vars->map[y][x] = 0;
			x++;
		}
		y++;
	}
}
