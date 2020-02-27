/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 10:58:56 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/27 16:59:53 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct	s_colours
{
	int	r;
	int	g;
	int	b;
	int	floorr;
	int	floorg;
	int	floorb;
	int	xorcolour;
	int	xcolour;
	int	ycolour;
	int	xycolour;
	int	floor;
	int	ceiling;
}				t_colours;

typedef struct	s_nesw
{
	char		*northtex;
	char		*southtex;
	char		*easttex;
	char		*westtex;
	int			bitspp_n;
	int			bitspp_e;
	int			bitspp_s;
	int			bitspp_w;
	int			line_e;
	int			line_w;
	int			line_n;
	int			line_s;
	int			img_width_n;
	int			img_width_e;
	int			img_width_s;
	int			img_width_w;
	int			img_height_n;
	int			img_height_e;
	int			img_height_s;
	int			img_height_w;
}				t_nesw;

typedef struct	s_sprite
{
	double		**sprite;
	double		*zbuffer;
	int			*spriteorder;
	double		*spritedist;
	char		*spritetex;
	char		*spritetex2;
	char		*spritetex3;
	int			bitspp_spr;
	int			bitspp_spr2;
	int			bitspp_spr3;
	int			line_spr;
	int			line_spr2;
	int			line_spr3;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			drawstarty;
	int			drawendy;
	int			drawstartx;
	int			drawendx;
	int			texx;
	int			texy;
	int			numsprites;
	int			img_width;
	int			img_height;
}				t_sprite;

typedef struct	s_screen
{
	int			screenwidth;
	int			screenheight;
	double		camerax;
	double		cameray;
	double		dirx;
	double		olddirx;
	double		diry;
	double		planex;
	double		oldplanex;
	double		planey;
	double		time;
	double		oldtime;
	double		frametime;
	int			texnum;
	double		wallx;
	int			texx;
	int			texy;
	double		step;
	double		texpos;
	t_nesw		*nesw;
	t_colours	*colours;
}				t_screen;

typedef struct	s_ray
{
	double	raydirx;
	double	raydiry;
	int		lineheight;
	int		drawstart;
	int		drawend;
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
}				t_ray;

typedef struct	s_pos
{
	char	spawnpos;
	double	posx;
	double	posy;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	double	stepx;
	double	stepy;
	int		hit;
	int		side;
	double	movespeed;
	double	rotspeed;
	int		maph;
	int		mapw;
}				t_pos;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	char	*addr_f;
	char	*addr_c;
	char	*addr_e;
	char	*addr_w;
	char	*addr_n;
	char	*addr_s;
	char	*addr_spr;
	char	*addr_spr2;
	char	*addr_spr3;
	void	*img_e;
	void	*img_w;
	void	*img_n;
	void	*img_s;
	void	*img_spr;
	void	*img_spr2;
	void	*img_spr3;
	void	*img_f;
	void	*img_c;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct	s_run
{
	void		*mlx;
	void		*win;
}				t_run;

typedef struct	s_keycheck
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keycheck;

typedef struct	s_error
{
	int			f_found;
	int			c_found;
	int			r_found;
	int			fcol_found;
	int			ccol_found;
	int			no_found;
	int			so_found;
	int			ea_found;
	int			we_found;
	int			pos_found;
	int			s_found;
	int			map_error;
	int			map_found;
	int			fd_error;
}				t_error;

typedef struct	s_floor
{
	float		raydirx0;
	float		raydiry0;
	float		raydirx1;
	float		raydiry1;
	int			p;
	float		posz;
	float		rowdistance;
	float		floorstepx;
	float		floorstepy;
	float		floorx;
	float		floory;
	int			cellx;
	int			celly;
	int			tx;
	int			ty;
	char		*floortex;
	int			bitspp_f;
	int			line_f;
	int			tex;
	int			tex2;
	char		*ceilingtex;
	int			bitspp_c;
	int			line_c;
	int			f_width;
	int			c_width;
	int			c_height;
	int			f_height;
}				t_floor;

typedef struct	s_weapon
{
	char		*weapontex;
	int			bitspp;
	int			line;
	int			width;
	int			height;
	char		*addr;
	void		*img;
	int			found;
}				t_weapon;

typedef struct	s_vars
{
	int			pressed;
	int			x;
	int			y;
	int			sensitivity;
	int			fd;
	int			**map;
	size_t		maplinelen;
	int			*linenumb;
	int			mapheight;
	t_screen	*sc;
	t_pos		*pos;
	t_run		*run;
	t_keycheck	*key;
	t_error		*error;
	t_sprite	*spr;
	t_floor		*floor;
	t_data		*img;
	t_weapon	*weapon;
}				t_vars;

unsigned int	ft_getwidth(int i, const char *input);
int				ft_intlen(int in);
int				ft_strlen(char *str);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_atoi(char *str);
int				getscreenwidth(char *file, int i);
int				ft_isnumbers(char *str, int type);
void			ft_press_w_s(t_vars *vars);
void			ft_press_a_d(t_vars *vars);
void			ft_rotateleft(t_vars *vars);
void			ft_rotateright(t_vars *vars);
void			ft_mapparser(t_vars *vars, char *file, int j);
void			ft_error(char *str);
void			ft_errorcheck(t_vars *vars);
void			ft_checkmapvalid(t_vars *vars, int x, int y);
void			ft_resetmap(t_vars *vars);
int				create_trgb(int r, int g, int b);
int				ft_validcolours(char *col);
void			ft_resolutioncheck(t_vars *vars, char **sub, char *file);
void			ft_pathcheck(t_vars *vars, char **sub, char *file, int i);
int				ft_floorcheck(t_vars *vars, char **sub, char *file);
int				ft_ceilingcheck(t_vars *vars, char **sub, char *file);
void			ft_fdcheck(t_vars *vars, char *tex, int type);
void			ft_spritecheck(t_vars *vars, char **sub, char *file, int i);
char			**ft_split(char const *s, char c);
double			sprite(t_vars *vars, int x, int y);
int				*ft_realloc(int *array, size_t newsize);
int				**ft_reallocmap(int **array, size_t newsize, t_vars *vars);
double			**ft_reallocsprit(double **array, size_t newsize);
void			ft_getspritedist(t_vars *vars);
void			ft_sortsprites(t_vars *vars);
int				ft_floorwithcolour(t_vars *vars, char **sub);
int				ft_ceilingwithcolour(t_vars *vars, char **sub);
void			ft_free(void **sub, int j);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_floorcast(t_vars *vars);
void			ft_wallcast(t_vars *vars);
void			ft_move(t_vars *vars);
void			ft_getstepandsidedist(t_vars *vars, t_ray *r);
void			ft_spritecast(t_vars *vars, int i);
int				get_r(unsigned int trgb);
int				get_g(unsigned int trgb);
int				get_b(unsigned int trgb);
unsigned int	ft_shadow(unsigned int colour, double distance);
void			ft_sortcolours(char **sub, t_vars *vars, int f_or_c);
#endif
