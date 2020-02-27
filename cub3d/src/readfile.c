/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readfile.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 16:15:26 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/26 19:36:17 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_resolutioncheck(t_vars *vars, char **sub, char *file)
{
	vars->error->r_found++;
	if (vars->error->r_found > 1)
		ft_error("\e[33mMultipule Resolutions\n\e[39m");
	sub = ft_split(file, ' ');
	if (sub[1] != '\0' && sub[2] != '\0')
	{
		if (ft_isnumbers(sub[1], 1) == 1)
		{
			vars->sc->screenwidth = getscreenwidth(sub[1], 0);
			if (vars->sc->screenwidth > 2560)
				vars->sc->screenwidth = 2560;
			vars->error->r_found++;
		}
		if (ft_isnumbers(sub[2], 1) == 1)
		{
			vars->sc->screenheight = getscreenwidth(sub[2], 0);
			if (vars->sc->screenheight > 1440)
				vars->sc->screenheight = 1440;
			vars->error->r_found++;
		}
	}
}

void	ft_pathcheck2(t_vars *vars, char **sub, char *file, int i)
{
	if (file[i] == 'S' && file[i + 1] == 'O')
	{
		vars->error->so_found++;
		sub = ft_split(file, ' ');
		if (sub[1] != '\0')
		{
			vars->sc->nesw->southtex = sub[1];
			ft_fdcheck(vars, vars->sc->nesw->southtex, 3);
		}
		else
			vars->error->so_found++;
	}
	if (file[i] == 'W' && file[i + 1] == 'E')
	{
		vars->error->we_found++;
		sub = ft_split(file, ' ');
		if (sub[1] != '\0')
		{
			vars->sc->nesw->westtex = sub[1];
			ft_fdcheck(vars, vars->sc->nesw->westtex, 4);
		}
		else
			vars->error->we_found++;
	}
	ft_spritecheck(vars, sub, file, i);
}

void	ft_pathcheck(t_vars *vars, char **sub, char *file, int i)
{
	if (file[i] == 'N' && file[i + 1] == 'O')
	{
		vars->error->no_found++;
		sub = ft_split(file, ' ');
		if (sub[1] != '\0')
		{
			vars->sc->nesw->northtex = sub[1];
			ft_fdcheck(vars, vars->sc->nesw->northtex, 1);
		}
		else
			vars->error->no_found++;
	}
	if (file[i] == 'E' && file[i + 1] == 'A')
	{
		vars->error->ea_found++;
		sub = ft_split(file, ' ');
		if (sub[1] != '\0')
		{
			vars->sc->nesw->easttex = sub[1];
			ft_fdcheck(vars, vars->sc->nesw->easttex, 2);
		}
		else
			vars->error->ea_found++;
	}
	ft_pathcheck2(vars, sub, file, i);
}

int		ft_floorcheck(t_vars *vars, char **sub, char *file)
{
	int a;

	a = 0;
	sub = ft_split(file, ' ');
	if (sub[1])
		sub = ft_split(sub[1], ',');
	else
		return (-1);
	if (sub[0] && sub[1] && sub[2] && vars->error->f_found == 1)
	{
		while (a < 3)
			a = (ft_validcolours(sub[a]) == 1) ? a += 1 : 10;
		if (a == 3)
		{
			ft_sortcolours(sub, vars, 1);
			if (vars->sc->colours->floor == -10)
				return (-1);
		}
		else
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int		ft_ceilingcheck(t_vars *vars, char **sub, char *file)
{
	int a;

	a = 0;
	sub = ft_split(file, ' ');
	if (sub[1])
		sub = ft_split(sub[1], ',');
	else
		return (-1);
	if (sub[0] && sub[1] && sub[2] && vars->error->c_found == 1)
	{
		while (a < 3)
			a = (ft_validcolours(sub[a]) == 1) ? a += 1 : 10;
		if (a == 3)
		{
			ft_sortcolours(sub, vars, 2);
			if (vars->sc->colours->ceiling == -10)
				return (-1);
		}
		else
			return (-1);
	}
	else
		return (-1);
	return (0);
}
