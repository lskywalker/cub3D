/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 20:30:54 by lsmit          #+#    #+#                */
/*   Updated: 2020/01/25 17:50:46 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

int			ft_check_n(char *pbuf)
{
	int i;

	i = 0;
	while (pbuf[i])
	{
		if (pbuf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int			ft_strlen(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void		ft_tobegin(char *orig, char *buf)
{
	if (*buf == '\n')
		buf++;
	while (*buf)
	{
		*orig = *buf;
		orig++;
		buf++;
	}
	*orig = '\0';
}
