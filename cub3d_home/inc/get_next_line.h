/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 20:25:52 by lsmit          #+#    #+#                */
/*   Updated: 2020/01/25 18:59:01 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int				get_next_line(int fd, char **line);
int				ft_strlen(char *str);
int				ft_check_n(char *pbuf);
void			ft_tobegin(char *orig, char *buf);
char			*ft_strjoin(char *line, char *buf);
char			*ft_joinstuff(char *line, char *res, char **buf);
#endif
