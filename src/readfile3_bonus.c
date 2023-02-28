/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readfile3_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 16:15:26 by lsmit         #+#    #+#                 */
/*   Updated: 2023/02/28 15:11:06 by lukesmit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int			ft_northpath(char *file, char **sub, int i, t_vars *vars)
{
	if (file[i] == 'N' && file[i + 1] == 'O')
	{
		vars->error->no_found++;
		sub = ft_split(file, ' ');
		if (ft_strcmp(sub[0], "NO") > 0 || ft_strcmp(sub[0], "NO") < 0)
			ft_error("\e[33mInvalid input for NO texture\n\e[39m");
		if (sub[1] != (void *)0)
		{
			vars->sc->nesw->northtex = sub[1];
			ft_fdcheck(vars, vars->sc->nesw->northtex, 1);
		}
		else
			vars->error->no_found++;
		free(sub[0]);
		free(sub);
		return (1);
	}
	return (0);
}

int			ft_southpath(char *file, char **sub, int i, t_vars *vars)
{
	if (file[i] == 'S' && file[i + 1] == 'O')
	{
		vars->error->so_found++;
		sub = ft_split(file, ' ');
		if (ft_strcmp(sub[0], "SO") > 0 || ft_strcmp(sub[0], "SO") < 0)
			ft_error("\e[33mInvalid input for SO texture\n\e[39m");
		if (sub[1] != (void *)0)
		{
			vars->sc->nesw->southtex = sub[1];
			ft_fdcheck(vars, vars->sc->nesw->southtex, 3);
		}
		else
			vars->error->so_found++;
		free(sub[0]);
		free(sub);
		return (1);
	}
	return (0);
}

int			ft_checkxpm(char *tex)
{
	int i;

	i = 0;
	while (tex[i])
	{
		if (tex[i] == '.' && tex[i + 1])
		{
			if (tex[i + 1] == 'x' && tex[i + 2])
			{
				if (tex[i + 2] == 'p' && tex[i + 3])
				{
					if (tex[i + 3] == 'm')
						return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
