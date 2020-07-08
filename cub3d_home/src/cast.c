/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 20:27:57 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/09 16:59:06 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_floorcast(t_vars *vars)
{
	int		y;

	y = 0;
	while (y < vars->sc->screenheight)
	{
		ft_floorcalc(vars, y);
		ft_floordrawx(vars, 0, y);
		y++;
	}
}

void	ft_wallcast(t_vars *vars)
{
	t_ray			r;
	int				x;

	x = 0;
	while (x < vars->sc->screenwidth)
	{
		ft_wallcameracalc(vars, &r, x);
		ft_getstepandsidedist(vars, &r);
		ft_move(vars);
		ft_wallcalc(vars, &r);
		if ((vars->pos->side == 0 || vars->pos->side == 1) && r.raydirx > 0)
			vars->sc->texx = vars->sc->nesw->img_width_n - vars->sc->texx - 1;
		if ((vars->pos->side == 2 || vars->pos->side == 3) && r.raydiry < 0)
			vars->sc->texx = vars->sc->nesw->img_width_n - vars->sc->texx - 1;
		vars->sc->step = 1.0 * vars->sc->nesw->img_height_n / r.lineheight;
		vars->sc->texpos = (r.drawstart - vars->sc->screenheight / 2 +
		r.lineheight / 2) * vars->sc->step;
		ft_drawwally(vars, r.drawend, x, r.drawstart);
		vars->spr->zbuffer[x] = vars->pos->perpwalldist;
		x++;
	}
}
