/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 18:34:28 by lsmit          #+#    #+#                */
/*   Updated: 2020/03/10 21:00:29 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int			**ft_memcpyint(int **dest, int **src, size_t n, t_vars *vars)
{
	int			i;
	size_t		j;

	j = 0;
	while (j < n)
	{
		i = 0;
		while (i < vars->linelen[j])
		{
			dest[j][i] = src[j][i];
			i++;
		}
		j++;
	}
	return (dest);
}

double		**ft_memcpydouble(double **dest,
			double **src, size_t n, size_t linelen)
{
	size_t		i;
	size_t		j;

	j = 0;
	while (j < n)
	{
		i = 0;
		while (i < linelen)
		{
			dest[j][i] = src[j][i];
			i++;
		}
		j++;
	}
	return (dest);
}

int			**ft_reallocmap(int **array, size_t newsize, t_vars *vars)
{
	int		**newarray;
	size_t	i;

	i = 0;
	if (newsize == 1)
		return (malloc(sizeof(int **) * 1));
	newarray = (int **)malloc(sizeof(int **) * newsize);
	if (!newarray)
		ft_error("\e[33mMalloc failed\n\e[39m");
	while (i < newsize - 1)
	{
		newarray[i] = (int*)malloc(sizeof(int *) * vars->linelen[i]);
		if (!newarray[i])
			ft_error("\e[33mMalloc failed\n\e[39m");
		i++;
	}
	newarray = ft_memcpyint(newarray, array, newsize - 1, vars);
	ft_free((void **)array, newsize - 1);
	free(array);
	return (newarray);
}

double		**ft_reallocsprit(double **array, size_t newsize)
{
	double	**newarray;
	size_t	i;

	i = 0;
	if (newsize == 1)
		return (malloc(sizeof(double **) * 1));
	newarray = (double **)malloc(sizeof(double **) * newsize);
	while (i < newsize - 1)
	{
		newarray[i] = (double*)malloc(sizeof(double *) * 5);
		if (!newarray[i])
			ft_error("\e[33mMalloc failed\n\e[39m");
		i++;
	}
	newarray = ft_memcpydouble(newarray, array, newsize - 1, 5);
	ft_free((void **)array, (int)newsize - 1);
	free(array);
	return (newarray);
}

int			*ft_realloc(int *array, size_t newsize)
{
	int		*newarray;

	if (newsize == 1)
		return (malloc(sizeof(int *) * 1));
	newarray = malloc(sizeof(int *) * newsize);
	if (!newarray)
		ft_error("\e[33mMalloc failed\n\e[39m");
	newarray = ft_memcpy(newarray, array, newsize - 1);
	free(array);
	return (newarray);
}
