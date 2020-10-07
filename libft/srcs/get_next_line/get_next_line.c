/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:03:14 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/07 13:06:28 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

ssize_t		ft_makeline(char **line, char **tab, const int fd)
{
	size_t	k;
	char	*temp;

	k = 0;
	temp = NULL;
	while (tab[fd][k] != '\n' && tab[fd][k] != '\0')
		k++;
	(k == 0 && tab[fd][k] == '\0') ? free(tab[fd]) : 0;	
	if (k == 0 && tab[fd][k] == '\0')
		return (0);
	if (tab[fd][k] == '\n')
	{
		if (!(*line = ft_strsub(tab[fd], 0, k)))
			return (-1);
		if (!(temp = ft_strdup(tab[fd] + (k + 1))))
			return (-1);
		free(tab[fd]);
		tab[fd] = temp;
	}
	else
	{
		if (!(*line = ft_strsub(tab[fd], 0, k)))
			return (-1);
		tab[fd][0] = '\0';
	}
	return (1);
}

int			get_next_line(const int fd, char **line, int end)
{
	ssize_t		ret;
	static char	*tab[MAX_FD];
	char		*temp;
	char		buf[BUFF_SIZE + 1];
	int			stop;

	ret = 0;
	stop = 0;
	if (fd < 0 || fd > MAX_FD || !line || BUFF_SIZE < 1)
		return (-1);
	if (tab[fd] == NULL && !(tab[fd] = ft_strnew(0)))
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(temp = ft_strjoin(tab[fd], buf, 1)))
			return (-1);
		tab[fd] = temp;
		if (ft_strchr(tab[fd], '\n') || (end > 0 && ++stop == end))
			break ;
	}
	if (ret < 0)
		return (-1);
	return (ft_makeline(line, tab, fd));
}
