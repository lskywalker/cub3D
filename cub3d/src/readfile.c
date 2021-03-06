/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readfile.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 16:15:26 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 16:26:21 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		ft_resolutioncheck(t_vars *vars, char **sub, char *file)
{
	vars->error->r_found++;
	if (vars->error->r_found > 1)
		ft_error("\e[33mMultipule Resolutions\n\e[39m");
	sub = ft_split(file, ' ');
	if (ft_strcmp(sub[0], "R") > 0 || ft_strcmp(sub[0], "R") < 0)
		ft_error("\e[33mInvalid resoltion\n\e[39m");
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
	ft_free((void**)sub, 3);
	free(sub);
}

int			ft_pathcheck2(t_vars *vars, char **sub, char *file, int i)
{
	if (ft_southpath(file, sub, i, vars))
		return (1);
	if (file[i] == 'W' && file[i + 1] == 'E')
	{
		vars->error->we_found++;
		sub = ft_split(file, ' ');
		if (ft_strcmp(sub[0], "WE") > 0 || ft_strcmp(sub[0], "WE") < 0)
			ft_error("\e[33mInvalid input for WE texture\n\e[39m");
		if (sub[1] != '\0')
		{
			vars->sc->nesw->westtex = sub[1];
			ft_fdcheck(vars, vars->sc->nesw->westtex, 4);
		}
		else
			vars->error->we_found++;
		free(sub[0]);
		free(sub);
		return (1);
	}
	if (ft_spritecheck(vars, sub, file, i))
		return (1);
	return (0);
}

int			ft_pathcheck(t_vars *vars, char **sub, char *file, int i)
{
	if (ft_northpath(file, sub, i, vars))
		return (1);
	if (file[i] == 'E' && file[i + 1] == 'A')
	{
		vars->error->ea_found++;
		sub = ft_split(file, ' ');
		if (ft_strcmp(sub[0], "EA") > 0 || ft_strcmp(sub[0], "EA") < 0)
			ft_error("\e[33mInvalid input for EA texture\n\e[39m");
		if (sub[1] != '\0')
		{
			vars->sc->nesw->easttex = sub[1];
			ft_fdcheck(vars, vars->sc->nesw->easttex, 2);
		}
		else
			vars->error->ea_found++;
		free(sub[0]);
		free(sub);
		return (1);
	}
	if (ft_pathcheck2(vars, sub, file, i))
		return (1);
	return (0);
}

void		ft_floorcheck(t_vars *vars, char **sub, char *file)
{
	char	**str;

	sub = ft_split(file, ' ');
	if (ft_strcmp(sub[0], "F") > 0 || ft_strcmp(sub[0], "F") < 0)
		ft_error("\e[33mInvalid floorinput\n\e[39m");
	if (sub[1])
		str = ft_split(sub[1], ',');
	else
	{
		str = NULL;
		ft_error("\e[33mInvalid floorinput\n\e[39m");
	}
	ft_free((void**)sub, 2);
	free(sub);
	if (ft_floorcheck2(vars, str, 0) == -1)
		ft_error("\e[33mInvalid floorinput\n\e[39m");
	vars->bonus = 0;
}

void		ft_ceilingcheck(t_vars *vars, char **sub, char *file)
{
	char	**str;

	sub = ft_split(file, ' ');
	if (ft_strcmp(sub[0], "C") > 0 || ft_strcmp(sub[0], "C") < 0)
		ft_error("\e[33mInvalid ceilinginput\n\e[39m");
	if (sub[1])
		str = ft_split(sub[1], ',');
	else
	{
		str = NULL;
		ft_error("\e[33mInvalid ceilinginput\n\e[39m");
	}
	ft_free((void**)sub, 2);
	free(sub);
	if (ft_ceilingcheck2(vars, str, 0) == -1)
		ft_error("\e[33mInvalid ceilinginput\n\e[39m");
}
