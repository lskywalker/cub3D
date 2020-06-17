/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 20:22:45 by lsmit          #+#    #+#                */
/*   Updated: 2020/02/26 19:27:36 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include "../inc/cub3d.h"

char		*ft_joinstuff(char *line, char *res, char **buf)
{
	int		i;

	i = 0;
	if (line != NULL)
	{
		while (line[i])
		{
			res[i] = line[i];
			i++;
		}
		free(line);
	}
	while (**buf && **buf != '\n')
	{
		res[i] = **buf;
		(*buf)++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char		*ft_strjoin(char *line, char *buf)
{
	char	*res;
	char	*orig;

	orig = buf;
	res = (char *)malloc(ft_strlen(line) + ft_strlen(buf) + 1);
	if (!res)
		ft_error("\e[33mMalloc failed\n\e[39m");
	res = ft_joinstuff(line, res, &buf);
	ft_tobegin(orig, buf);
	return (res);
}

int				get_next_line(int fd, char **line)
{
	static char		buf[1000];
	ssize_t			sc;
	int				ret;

	*line = NULL;
	ret = 0;
	while (ret == 0)
	{
		if (!*buf)
		{
			sc = read(fd, buf, 1000);
			if (sc <= 0)
			{
				buf[0] = '\0';
				ret = sc;
				*line = (ret == 0) ? ft_strjoin(*line, buf) : NULL;
				break ;
			}
			buf[sc] = '\0';
		}
		ret = (ft_check_n(buf) == 1) ? 1 : ret;
		*line = ft_strjoin(*line, buf);
		ret = (*line == NULL) ? -1 : ret;
	}
	return (ret);
}
