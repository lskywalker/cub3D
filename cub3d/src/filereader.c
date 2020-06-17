/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filereader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 11:27:10 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 17:04:10 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/get_next_line.h"

int			ft_getlinefunction2(char *file, int i, char **sub, t_vars *vars)
{
	if (file[i] == 'F')
	{
		vars->error->f_found++;
		ft_floorcheck(vars, sub, file);
		return (1);
	}
	if (file[i] == 'C')
	{
		vars->error->c_found++;
		ft_ceilingcheck(vars, sub, file);
		return (1);
	}
	return (0);
}

void		ft_getlinefunction(char *file, t_vars *vars)
{
	int			i;
	char		*sub;

	i = 0;
	while (file[i] != '\n' && file[i])
	{
		if (file[i] == 'R')
		{
			ft_resolutioncheck(vars, &sub, file);
			return ;
		}
		if (ft_pathcheck(vars, &sub, file, i))
			return ;
		if (ft_getlinefunction2(file, i, &sub, vars))
			return ;
		i++;
	}
}

void		ft_readfile(t_vars *vars)
{
	ft_filereader(vars, 0);
	if (vars->bonus == 1)
		vars->spr->spritetex2 = "./img/coin.png";
	ft_getdirection(vars);
	vars->spr->zbuffer = malloc(sizeof(int*) * vars->sc->screenwidth);
	if (!vars->spr->zbuffer)
		ft_error("\e[33mMalloc failed\n\e[39m");
	if (vars->error->map_found > 0)
	{
		ft_checkmapvalid(vars, (int)vars->pos->posx, (int)vars->pos->posy);
		ft_resetmap(vars);
	}
	ft_errorcheck(vars);
}

void		ft_filereader(t_vars *vars, int j)
{
	char	*file;
	int		res;

	res = 1;
	while (res > 0)
	{
		res = get_next_line(vars->fd, &file);
		if (vars->error->r_found == 0 || vars->error->no_found == 0 ||
		vars->error->ea_found == 0 || vars->error->so_found == 0 ||
		vars->error->we_found == 0 || vars->error->f_found == 0 ||
		vars->error->c_found == 0 || vars->error->s_found == 0)
			ft_getlinefunction(file, vars);
		else
		{
			if (!ft_emptyline(file))
			{
				vars->error->map_found++;
				ft_mapparser(vars, file, j);
				vars->mapheight = j;
				j++;
			}
		}
		free(file);
	}
}
