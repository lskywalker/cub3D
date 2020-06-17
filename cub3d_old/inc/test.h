/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 12:39:07 by lsmit          #+#    #+#                */
/*   Updated: 2020/01/29 14:10:06 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../mlx/mlx.h"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	int		pressed;
	int		x;
	int		y;
	int		sensitivity;
}				t_vars;

unsigned int	ft_getwidth(int i, const char *input);
int				ft_intlen(int in);

#endif
