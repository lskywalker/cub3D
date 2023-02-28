/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readfile2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 10:24:50 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 16:16:24 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int			ft_spritecheck(t_vars *vars, char **sub, char *file, int i)
{
	if (file[i] == 'S' && file[i + 1] != 'O')
	{
		vars->error->s_found++;
		sub = ft_split(file, ' ');
		if (ft_strcmp(sub[0], "S") > 0 || ft_strcmp(sub[0], "S") < 0)
			ft_error("\e[33mInvalid input for sprite texture\n\e[39m");
		if (sub[1])
		{
			vars->spr->spritetex = sub[1];
			ft_fdcheck(vars, vars->spr->spritetex, 5);
		}
		else
			vars->error->s_found++;
		free(sub[0]);
		free(sub);
		return (1);
	}
	return (0);
}

void		ft_fdcheck(t_vars *vars, char *tex, int type)
{
	int		fd;

	if (ft_checkxpm(tex))
		ft_error("\e[33mI don't accept XPM files\n\e[39m");
	fd = open(tex, O_RDONLY);
	if (fd == -1)
	{
		if (type == 1)
			vars->error->no_found = 10;
		if (type == 2)
			vars->error->ea_found = 10;
		if (type == 3)
			vars->error->so_found = 10;
		if (type == 4)
			vars->error->we_found = 10;
		if (type == 5)
			vars->error->s_found = 10;
		if (type == 6)
			vars->error->f_found = 10;
		if (type == 7)
			vars->error->c_found = 10;
	}
	close(fd);
}

void		ft_sortcolours(char **sub, t_vars *vars, int f_or_c)
{
	if (f_or_c == 1)
	{
		vars->sc->colours->r = ft_atoi(sub[0]);
		vars->sc->colours->g = ft_atoi(sub[1]);
		vars->sc->colours->b = ft_atoi(sub[2]);
		vars->sc->colours->floor = create_trgb(vars->sc->colours->r,
		vars->sc->colours->g, vars->sc->colours->b);
	}
	else if (f_or_c == 2)
	{
		vars->sc->colours->r = ft_atoi(sub[0]);
		vars->sc->colours->g = ft_atoi(sub[1]);
		vars->sc->colours->b = ft_atoi(sub[2]);
		vars->sc->colours->ceiling = create_trgb(vars->sc->colours->r,
		vars->sc->colours->g, vars->sc->colours->b);
	}
	ft_free((void**)sub, 3);
	free(sub);
}

int			ft_southpath(char *file, char **sub, int i, t_vars *vars)
{
	if (file[i] == 'S' && file[i + 1] == 'O')
	{
		vars->error->so_found++;
		sub = ft_split(file, ' ');
		if (ft_strcmp(sub[0], "SO") > 0 || ft_strcmp(sub[0], "SO") < 0)
			ft_error("\e[33mInvalid input for SO texture\n\e[39m");
		if (sub[1] != '\0')
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

int			ft_northpath(char *file, char **sub, int i, t_vars *vars)
{
	if (file[i] == 'N' && file[i + 1] == 'O')
	{
		vars->error->no_found++;
		sub = ft_split(file, ' ');
		if (ft_strcmp(sub[0], "NO") > 0 || ft_strcmp(sub[0], "NO") < 0)
			ft_error("\e[33mInvalid input for NO texture\n\e[39m");
		if (sub[1] != '\0')
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
