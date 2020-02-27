/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 20:27:39 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/27 17:02:18 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/get_next_line.h"

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int		ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int		ft_atoi(char *str)
{
	int			i;
	long long	res;
	long long	n;

	i = 0;
	n = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res * 10 + (str[i] - '0')) < res)
			return (((-1 * n) - 1) / 2);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return ((int)res * n);
}

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		getscreenwidth(char *file, int i)
{
	int		j;
	char	*width;
	int		ret;

	j = 0;
	width = malloc(1920);
	if (!width)
		ft_error("\e[33mMalloc failed\n\e[39m");
	while (ft_isdigit(file[i]))
	{
		width[j] = file[i];
		width[j + 1] = '\0';
		j++;
		i++;
	}
	ret = ft_atoi(width);
	free(width);
	return (ret);
}

int		ft_intlen(int in)
{
	int		count;

	count = 1;
	while (in > 9)
	{
		in /= 10;
		count++;
	}
	return (count);
}

void	ft_free(void **sub, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		free(sub[i]);
		i++;
	}
}

void	ft_getlinefunction(char *file, t_vars *vars)
{
	int			i;
	char		**sub;

	i = 0;
	sub = malloc(sizeof(*sub) * 4);
	*sub = malloc(ft_strlen(file) + 1);
	if (!sub || !*sub)
		ft_error("\e[33mMalloc failed\n\e[39m");
	while (file[i] != '\n' && file[i])
	{
		if (file[i] == 'R')
			ft_resolutioncheck(vars, sub, file);
		ft_pathcheck(vars, sub, file, i);
		if (file[i] == 'F')
		{
			vars->error->f_found++;
			if (ft_floorcheck(vars, sub, file) == -1)
				vars->error->fcol_found = -10;
		}
		if (file[i] == 'C')
		{
			vars->error->c_found++;
			if (ft_ceilingcheck(vars, sub, file) == -1)
				vars->error->ccol_found = -10;
		}
		i++;
	}
	free(sub);
}

void	ft_getdirection(t_vars *vars)
{
	if (vars->pos->spawnpos == 'N')
	{
		vars->sc->dirx = 0;
		vars->sc->diry = -1;
		vars->sc->planex = 0.66;
		vars->sc->planey = 0;
	}
	if (vars->pos->spawnpos == 'E')
	{
		vars->sc->dirx = 1;
		vars->sc->diry = 0;
		vars->sc->planex = 0;
		vars->sc->planey = 0.66;
	}
	if (vars->pos->spawnpos == 'S')
	{
		vars->sc->dirx = 0;
		vars->sc->diry = 1;
		vars->sc->planex = -0.66;
		vars->sc->planey = 0;
	}
	if (vars->pos->spawnpos == 'W')
	{
		vars->sc->dirx = -1;
		vars->sc->diry = 0;
		vars->sc->planex = 0;
		vars->sc->planey = -0.66;
	}
}

int		ft_emptyline(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[j])
		j++;
	if (i == j)
		return (1);
	return (0);
}

void	readfile(t_vars *vars)
{
	char	*file;
	int		res;
	int		j;

	res = 1;
	j = 0;
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
				j++;
			}
		}
		free(file);
	}
	ft_getdirection(vars);
	if (vars->error->map_found > 0)
	{
		ft_checkmapvalid(vars, (int)vars->pos->posx, (int)vars->pos->posy);
		ft_resetmap(vars);
	}
	ft_errorcheck(vars);
}

void		ft_getstepandsidedist(t_vars *vars, t_ray *r)
{
	if (r->raydirx < 0)
	{
		vars->pos->stepx = -1;
		vars->pos->sidedistx = (vars->pos->posx - vars->pos->mapx) *
		vars->pos->deltadistx;
	}
	else
	{
		vars->pos->stepx = 1;
		vars->pos->sidedistx = (vars->pos->mapx + 1.0 - vars->pos->posx) *
		vars->pos->deltadistx;
	}
	if (r->raydiry < 0)
	{
		vars->pos->stepy = -1;
		vars->pos->sidedisty = (vars->pos->posy - vars->pos->mapy) *
		vars->pos->deltadisty;
	}
	else
	{
		vars->pos->stepy = 1;
		vars->pos->sidedisty = (vars->pos->mapy + 1.0 - vars->pos->posy) *
		vars->pos->deltadisty;
	}
}

void	ft_move(t_vars *vars)
{
	while (vars->pos->hit == 0)
	{
		if (vars->pos->sidedistx < vars->pos->sidedisty)
		{
			if (vars->pos->stepx < 0)
				vars->pos->side = 1;
			else
				vars->pos->side = 0;
			vars->pos->sidedistx += vars->pos->deltadistx;
			vars->pos->mapx += vars->pos->stepx;
		}
		else
		{
			if (vars->pos->stepy < 0)
				vars->pos->side = 2;
			else
				vars->pos->side = 3;
			vars->pos->sidedisty += vars->pos->deltadisty;
			vars->pos->mapy += vars->pos->stepy;
		}
		if (vars->map[vars->pos->mapy][vars->pos->mapx] == 1)
			vars->pos->hit = 1;
	}
}

int		ft_quit(t_vars *vars)
{
	mlx_destroy_window(vars->run->mlx, vars->run->win);
	exit(0);
}

int		ft_keypress(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->run->mlx, vars->run->win);
		exit(0);
	}
	if (keycode == 13)
		vars->key->w = 1;
	if (keycode == 1)
		vars->key->s = 1;
	if (keycode == 0)
		vars->key->a = 1;
	if (keycode == 2)
		vars->key->d = 1;
	if (keycode == 123)
		vars->key->left = 1;
	if (keycode == 124)
		vars->key->right = 1;
	return (0);
}

int		ft_keyrelease(int keycode, t_vars *vars)
{
	if (keycode == 13)
		vars->key->w = 0;
	if (keycode == 1)
		vars->key->s = 0;
	if (keycode == 0)
		vars->key->a = 0;
	if (keycode == 2)
		vars->key->d = 0;
	if (keycode == 123)
		vars->key->left = 0;
	if (keycode == 124)
		vars->key->right = 0;
	return (0);
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
	if (vars->weapon->found == 1)
	{
		vars->weapon->img = mlx_png_file_to_image(vars->run->mlx,
		vars->weapon->weapontex, &vars->weapon->width, &vars->weapon->height);
		vars->weapon->addr = mlx_get_data_addr(vars->weapon->img, 
		&vars->weapon->bitspp, &vars->weapon->line, &img->endian);
	}
}

double	sprite(t_vars *vars, int x, int y)
{
	vars->spr->sprite = ft_reallocsprit(vars->spr->sprite, vars->spr->numsprites + 1);
	if (!vars->spr->sprite)
		ft_error("\e[33mMalloc failed\n\e[39m");
	vars->spr->sprite[vars->spr->numsprites] = malloc(sizeof(double*) * 3);
	if (!vars->spr->sprite[vars->spr->numsprites])
		ft_error("\e[33mMalloc failed\n\e[39m");
	vars->spr->sprite[vars->spr->numsprites][0] = x + 0.5;
	vars->spr->sprite[vars->spr->numsprites][1] = y + 0.5;
	return (0);
}

void	ft_spritecast(t_vars *vars, int i)
{
	int	y;
	int	stripe;
	int	d;
	unsigned int	colour;

	if (vars->error->s_found != 0)
	{
		vars->spr->spritex = vars->spr->sprite[i][0] - vars->pos->posx;
		vars->spr->spritey = vars->spr->sprite[i][1] - vars->pos->posy;
		vars->spr->invdet = 1.0 / (vars->sc->planex * vars->sc->diry -
		vars->sc->dirx * vars->sc->planey);
		vars->spr->transformx = vars->spr->invdet * (vars->sc->diry *
		vars->spr->spritex - vars->sc->dirx * vars->spr->spritey);
		vars->spr->transformy = vars->spr->invdet * (-vars->sc->planey *
		vars->spr->spritex + vars->sc->planex * vars->spr->spritey);
		vars->spr->spritescreenx = (int)((vars->sc->screenwidth / 2) * (1 +
		vars->spr->transformx / vars->spr->transformy));
		vars->spr->spriteheight = abs((int)(vars->sc->screenheight /
		(vars->spr->transformy)));
		vars->spr->drawstarty = -vars->spr->spriteheight / 2
		+ vars->sc->screenheight / 2;
		if (vars->spr->drawstarty < 0)
			vars->spr->drawstarty = 0;
		vars->spr->drawendy = vars->spr->spriteheight / 2
		+ vars->sc->screenheight / 2;
		if (vars->spr->drawendy >= vars->sc->screenheight)
			vars->spr->drawendy = vars->sc->screenheight - 1;
		vars->spr->spritewidth = abs((int)(vars->sc->screenheight /
		vars->spr->transformy));
		vars->spr->drawstartx = -vars->spr->spritewidth / 2
		+ vars->spr->spritescreenx;
		if (vars->spr->drawstartx < 0)
			vars->spr->drawstartx = 0;
		vars->spr->drawendx = vars->spr->spritewidth / 2
		+ vars->spr->spritescreenx;
		if (vars->spr->drawendx >= vars->sc->screenwidth)
			vars->spr->drawendx = vars->sc->screenwidth - 1;
		stripe = vars->spr->drawstartx;
		while (stripe < vars->spr->drawendx)
		{
			vars->spr->texx = (int)(256 * (stripe -
			(-vars->spr->spritewidth / 2 + vars->spr->spritescreenx))
			* vars->spr->img_width / vars->spr->spritewidth) / 256;
			if (vars->spr->transformy > 0 && stripe > 0 &&
			stripe < vars->sc->screenwidth &&
			vars->spr->transformy < vars->spr->zbuffer[stripe])
			{
				y = vars->spr->drawstarty;
				while (y < vars->spr->drawendy)
				{
					d = (y) * 256 - vars->sc->screenheight * 128 +
					vars->spr->spriteheight * 128;
					vars->spr->texy = ((d * vars->spr->img_height) / vars->spr->spriteheight) / 256;
					colour = *(unsigned int*)(vars->img->addr_spr + (vars->spr->texy *
					vars->spr->line_spr + vars->spr->texx *
					(vars->spr->bitspp_spr / 8)));
					if (colour != 0)
					{
						colour = ft_shadow(colour, vars->spr->sprite[i][2]);
						my_mlx_pixel_put(vars->img, stripe, y, colour);
					}
					y++;
				}
			}
			stripe++;
		}
	}
}

int		ft_render_frame(t_vars *vars)
{
	int		i;

	vars->img->img = mlx_new_image(vars->run->mlx, vars->sc->screenwidth, vars->sc->screenheight);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel,
								&vars->img->line_length, &vars->img->endian);
	ft_floorcast(vars);
	ft_wallcast(vars);
	ft_getspritedist(vars);
	ft_sortsprites(vars);
	i = 0;
	while (i < vars->spr->numsprites)
	{
		ft_spritecast(vars, i);
		i++;
	}
	mlx_put_image_to_window(vars->run->mlx, vars->run->win, vars->img->img, 0, 0);
	mlx_destroy_image(vars->run->mlx, vars->img->img);
	return (0);
}

int		ft_keycheck(t_vars *vars)
{
	vars->pos->movespeed = 0.08;
	vars->pos->rotspeed = 0.06;
	if (vars->key->w == 1 || vars->key->s == 1 ||
	vars->key->a == 1 || vars->key->d == 1 ||
	vars->key->left == 1 || vars->key->right == 1)
	{
		ft_press_w_s(vars);
		ft_press_a_d(vars);
		ft_rotateleft(vars);
		ft_rotateright(vars);
	}
	ft_render_frame(vars);
	free(vars->spr->zbuffer);
	return (0);
}

void	ft_init(t_vars *vars)
{
	vars->key->w = 0;
	vars->key->a = 0;
	vars->key->s = 0;
	vars->key->d = 0;
	vars->key->left = 0;
	vars->key->right = 0;
	vars->sc->screenwidth = 0;
	vars->sc->screenheight = 0;
	vars->error->r_found = 0;
	vars->error->f_found = 0;
	vars->error->c_found = 0;
	vars->error->fcol_found = 0;
	vars->error->ccol_found = 0;
	vars->error->no_found = 0;
	vars->error->so_found = 0;
	vars->error->ea_found = 0;
	vars->error->we_found = 0;
	vars->error->pos_found = 0;
	vars->error->map_error = 0;
	vars->error->s_found = 0;
	vars->pos->spawnpos = 'U';
	vars->error->map_found = 0;
	vars->maplinelen = 0;
}

int		ft_rungame(t_vars *vars)
{
	t_pos		pos;
	t_screen	sc;
	t_run		run;
	t_keycheck	key;
	t_colours	colours;
	t_nesw		nesw;
	t_error		error;
	t_sprite	sprite;
	t_floor		floor;
	t_data		img;
	t_weapon	weapon;

	vars->error = &error;
	vars->pos = &pos;
	vars->sc = &sc;
	vars->sc->colours = &colours;
	vars->sc->nesw = &nesw;
	vars->spr = &sprite;
	vars->run = &run;
	vars->key = &key;
	vars->floor = &floor;
	vars->img = &img;
	vars->weapon = &weapon;
	ft_init(vars);
	readfile(vars);
	vars->run->mlx = mlx_init();
	vars->run->win = mlx_new_window(vars->run->mlx,
	vars->sc->screenwidth, vars->sc->screenheight, "My Cub3D Game bruv");
	ft_getimgaddr(vars, &img);
	ft_render_frame(vars);
	mlx_loop_hook(vars->run->mlx, ft_keycheck, vars);
	mlx_hook(vars->run->win, 2, 1L<<0, ft_keypress, vars);
	mlx_hook(vars->run->win, 17, 0L, ft_quit, vars);
	mlx_hook(vars->run->win, 3, 1L<<1, ft_keyrelease, vars);
	mlx_loop(vars->run->mlx);
	return (0);
}

int		main(int amount, char **argv)
{
	t_vars		vars;

	if (amount != 2)
	{
		write(1, "ERROR: Invalid runcommand\n", 27);
		return (0);
	}
	vars.fd = open(argv[1], O_RDONLY);
	if (vars.fd == -1)
	{
		write(1, "ERROR: Invalid filename\n", 25);
		return (0);
	}
	ft_rungame(&vars);
}
