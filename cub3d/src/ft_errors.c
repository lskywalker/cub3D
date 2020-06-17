/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_errors.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 16:31:19 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/05 18:51:05 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_error(char *str)
{
	write(1, "\e[31mERROR\n", 13);
	write(1, str, ft_strlen(str) + 1);
	exit(1);
}

void	ft_emptycheck(t_vars *vars)
{
	if (vars->error->r_found == 0)
		ft_error("\e[33mNo resolution\n\e[39m");
	if (vars->error->no_found == 0)
		ft_error("\e[33mNo input for NO texture\n\e[39m");
	if (vars->error->ea_found == 0)
		ft_error("\e[33mNo input for EA texture\n\e[39m");
	if (vars->error->so_found == 0)
		ft_error("\e[33mNo input for SO texture\n\e[39m");
	if (vars->error->we_found == 0)
		ft_error("\e[33mNo input for WE texture\n\e[39m");
	if (vars->error->f_found == 0)
		ft_error("\e[33mNo floor input\n\e[39m");
	if (vars->error->c_found == 0)
		ft_error("\e[33mNo ceiling input\n\e[39m");
	if (vars->error->s_found == 0)
		ft_error("\e[33mNo sprite input\n\e[39m");
	if (vars->pos->spawnpos == 'U')
		ft_error("\e[33mNo spawnlocation\n\e[39m");
}

void	ft_errorcheck(t_vars *vars)
{
	ft_emptycheck(vars);
	if (vars->error->r_found != 3)
		ft_error("\e[33mInvalid resolution\n\e[39m");
	if (vars->error->no_found > 1)
		ft_error("\e[33mInvalid input for NO texture\n\e[39m");
	if (vars->error->ea_found > 1)
		ft_error("\e[33mInvalid input for EA texture\n\e[39m");
	if (vars->error->so_found > 1)
		ft_error("\e[33mInvalid input for SO texture\n\e[39m");
	if (vars->error->we_found > 1)
		ft_error("\e[33mInvalid input for WE texture\n\e[39m");
	if (vars->error->fcol_found < 0 || vars->error->f_found < 0
	|| vars->error->f_found == 10)
		ft_error("\e[33mInvalid floorinput\n\e[39m");
	if (vars->error->ccol_found < 0 || vars->error->c_found < 0
	|| vars->error->c_found == 10)
		ft_error("\e[33mInvalid ceilinginput\n\e[39m");
	if (vars->error->s_found > 1)
		ft_error("\e[33mInvalid spriteinputn\e[39m");
	if (vars->error->pos_found > 1)
		ft_error("\e[33mDouble spawnlocation\n\e[39m");
}

int		ft_isnumbers(char *str, int type)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (type == 2)
		{
			if (ft_isdigit(str[i]))
				count++;
		}
		if (type == 1)
		{
			if (ft_isdigit(str[i]) && str[0] != '0')
				count++;
		}
		i++;
	}
	if (i == count && i != 0)
		return (1);
	return (0);
}
