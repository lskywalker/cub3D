/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readfile2_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 10:24:50 by lsmit         #+#    #+#                 */
/*   Updated: 2023/02/28 15:10:14 by lukesmit      ########   odam.nl         */
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
			ft_error("\e[33mInvalid sprite input\n\e[39m");
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

void		ft_floorwithcolour(t_vars *vars, char **sub)
{
	int		a;

	a = 0;
	if (sub[0] && sub[1] && sub[2] && vars->error->f_found == 1)
	{
		while (a < 3)
			a = (ft_validcolours(sub[a]) == 1) ? a + 1 : 10;
		if (a == 3)
		{
			vars->sc->colours->r = ft_atoi(sub[0]);
			vars->sc->colours->g = ft_atoi(sub[1]);
			vars->sc->colours->b = ft_atoi(sub[2]);
			vars->sc->colours->floor = create_trgb(vars->sc->colours->r,
			vars->sc->colours->g, vars->sc->colours->b);
			if (vars->sc->colours->floor == -10)
				ft_error("\e[33mInvalid floorinput\n\e[39m");
		}
		else
			ft_error("\e[33mInvalid floorinput\n\e[39m");
	}
	else
		ft_error("\e[33mInvalid floorinput\n\e[39m");
}

void		ft_ceilingwithcolour(t_vars *vars, char **sub)
{
	int a;

	a = 0;
	if (sub[0] && sub[1] && sub[2] && vars->error->c_found == 1)
	{
		while (a < 3)
			a = (ft_validcolours(sub[a]) == 1) ? a + 1 : 10;
		if (a == 3)
		{
			vars->sc->colours->r = ft_atoi(sub[0]);
			vars->sc->colours->g = ft_atoi(sub[1]);
			vars->sc->colours->b = ft_atoi(sub[2]);
			vars->sc->colours->ceiling = create_trgb(vars->sc->colours->r,
			vars->sc->colours->g, vars->sc->colours->b);
			if (vars->sc->colours->ceiling == -10)
				ft_error("\e[33mInvalid ceilinginput\n\e[39m");
		}
		else
			ft_error("\e[33mInvalid ceilinginput\n\e[39m");
	}
	else
		ft_error("\e[33mInvalid ceilinginput\n\e[39m");
}
