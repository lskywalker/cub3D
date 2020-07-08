/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getimg.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 16:46:15 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 20:05:26 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	getspriteimg_addr(t_vars *vars, t_data *img)
{
	img->img_spr = mlx_png_file_to_image(vars->run->mlx, vars->spr->spritetex,
	&vars->spr->img_width, &vars->spr->img_height);
	img->addr_spr = mlx_get_data_addr(img->img_spr, &vars->spr->bitspp_spr,
	&vars->spr->line_spr, &img->endian);
	if (vars->bonus == 1)
	{
		img->img_spr2 = mlx_png_file_to_image(vars->run->mlx,
		"./img/coin.png", &vars->spr->img_width2, &vars->spr->img_height2);
		img->addr_spr2 = mlx_get_data_addr(img->img_spr2,
		&vars->spr->bitspp_spr2, &vars->spr->line_spr2, &img->endian);
		vars->weapon->img = mlx_png_file_to_image(vars->run->mlx,
		"./img/karambit.png", &vars->weapon->width, &vars->weapon->height);
		vars->weapon->addr = mlx_get_data_addr(vars->weapon->img,
		&vars->weapon->bitspp, &vars->weapon->line, &img->endian);
	}
}

void	ft_getimgaddr2(t_vars *vars, t_data *img)
{
	if (vars->floor->tex == 1)
	{
		img->img_f = mlx_png_file_to_image(vars->run->mlx,
		vars->floor->floortex, &vars->floor->f_width, &vars->floor->f_height);
		img->addr_f = mlx_get_data_addr(img->img_f, &vars->floor->bitspp_f,
		&vars->floor->line_f, &img->endian);
	}
	if (vars->floor->tex2 == 1)
	{
		img->img_c = mlx_png_file_to_image(vars->run->mlx,
		vars->floor->ceilingtex, &vars->floor->c_width, &vars->floor->c_height);
		img->addr_c = mlx_get_data_addr(img->img_c, &vars->floor->bitspp_c,
		&vars->floor->line_c, &img->endian);
	}
}

void	ft_getimgaddr(t_vars *vars, t_data *img)
{
	img->img_e = mlx_png_file_to_image(vars->run->mlx, vars->sc->nesw->easttex,
	&vars->sc->nesw->img_width_e, &vars->sc->nesw->img_height_e);
	img->addr_e = mlx_get_data_addr(img->img_e, &vars->sc->nesw->bitspp_e,
	&vars->sc->nesw->line_e, &img->endian);
	img->img_w = mlx_png_file_to_image(vars->run->mlx, vars->sc->nesw->westtex,
	&vars->sc->nesw->img_width_w, &vars->sc->nesw->img_height_w);
	img->addr_w = mlx_get_data_addr(img->img_w, &vars->sc->nesw->bitspp_w,
	&vars->sc->nesw->line_w, &img->endian);
	img->img_n = mlx_png_file_to_image(vars->run->mlx, vars->sc->nesw->northtex,
	&vars->sc->nesw->img_width_n, &vars->sc->nesw->img_height_n);
	img->addr_n = mlx_get_data_addr(img->img_n, &vars->sc->nesw->bitspp_n,
	&vars->sc->nesw->line_n, &img->endian);
	img->img_s = mlx_png_file_to_image(vars->run->mlx, vars->sc->nesw->southtex,
	&vars->sc->nesw->img_width_s, &vars->sc->nesw->img_height_s);
	img->addr_s = mlx_get_data_addr(img->img_s, &vars->sc->nesw->bitspp_s,
	&vars->sc->nesw->line_s, &img->endian);
	getspriteimg_addr(vars, img);
	ft_getimgaddr2(vars, img);
}
