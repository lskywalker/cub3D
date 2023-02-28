/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subfunctions.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 10:02:20 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/11 17:08:29 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int			ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int			ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int			ft_atoi(char *str)
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

int			getscreenwidth(char *file, int i)
{
	int		j;
	char	*width;
	int		ret;

	j = 0;
	width = malloc(2147483647);
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
