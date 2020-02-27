/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 10:51:13 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/27 17:03:06 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_getspritedist(t_vars *vars)
{
	double		distx;
	double		disty;
	int			i;

	i = 0;
	while (i < vars->spr->numsprites)
	{
		distx = vars->pos->posx - vars->spr->sprite[i][0];
		if (distx < 0)
			distx *= -1;
		disty = vars->pos->posy - vars->spr->sprite[i][1];
		if (disty < 0)
			disty *= -1;
		vars->spr->sprite[i][2] = sqrt((distx * distx) + (disty * disty));
		i++;
	}
}

void	ft_swaparray(t_vars *vars, int i)
{
	int		j;
	double	temp;

	j = 0;
	while (j < 3)
	{
		temp = vars->spr->sprite[i][j];
		vars->spr->sprite[i][j] = vars->spr->sprite[i - 1][j];
		vars->spr->sprite[i - 1][j] = temp;
		j++;
	}
}

void	ft_sortsprites(t_vars *vars)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (done == 0)
	{
		done = 1;
		while (i < vars->spr->numsprites - 1)
		{
			i++;
			if (vars->spr->sprite[i][2] > vars->spr->sprite[i - 1][2])
			{
				ft_swaparray(vars, i);
				done = 0;
			}
		}
	}
}

void	getspriteimg_addr(t_vars *vars, t_data *img)
{
	img->img_spr = mlx_png_file_to_image(vars->run->mlx, vars->spr->spritetex,
	&vars->spr->img_width, &vars->spr->img_height);
	img->addr_spr = mlx_get_data_addr(img->img_spr, &vars->spr->bitspp_spr,
	&vars->spr->line_spr, &img->endian);
	img->img_spr2 = mlx_png_file_to_image(vars->run->mlx, vars->spr->spritetex2,
	&vars->spr->img_width, &vars->spr->img_height);
	img->addr_spr2 = mlx_get_data_addr(img->img_spr2, &vars->spr->bitspp_spr2,
	&vars->spr->line_spr2, &img->endian);
	img->img_spr3 = mlx_png_file_to_image(vars->run->mlx, vars->spr->spritetex3,
	&vars->spr->img_width, &vars->spr->img_height);
	img->addr_spr3 = mlx_get_data_addr(img->img_spr3, &vars->spr->bitspp_spr3,
	&vars->spr->line_spr3, &img->endian);
}
