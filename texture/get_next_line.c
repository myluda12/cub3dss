/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajrhou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:27:30 by ayajrhou          #+#    #+#             */
/*   Updated: 2019/10/31 22:03:15 by ayajrhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*ft_stock(char *line, char *buff, int i)
{
	char	*newline;
	int		len;
	int		j;

	j = 0;
	len = (line ? ft_strlen(line) : 0);
	newline = (char *)malloc(len + i + 1);
	while (j < len)
	{
		newline[j] = line[j];
		j++;
	}
	if (line)
		free(line);
	while (j < len + i)
	{
		newline[j] = buff[j - len];
		j++;
	}
	newline[j] = '\0';
	return (newline);
}

int			ft_backslash(char ***line, char **str, char **buff, int i)
{
	char	*tmp;

	if ((*str)[i] == '\n')
	{
		*(*line) = ft_stock(*(*line), (*str), i);
		tmp = (*str);
		(*str) = ft_stock(0, (*str) + i + 1, ft_strlen((*str)) - i - 1);
		free(tmp);
		tmp = NULL;
		free(*buff);
		*buff = NULL;
		return (1);
	}
	return (0);
}

int			ft_str(char ***line, char **str, char **buff)
{
	int		i;
	int		c;

	i = 0;
	if ((*str))
	{
		i = 0;
		while ((*str)[i] && (*str)[i] != '\n')
			i++;
		c = ft_backslash(line, str, buff, i);
		if (c == 1)
		{
			return (1);
		}
		if ((*str)[i] == '\0')
		{
			*(*line) = ft_stock(*(*line), (*str), i);
			free((*str));
			(*str) = NULL;
		}
	}
	return (0);
}

int			ft_read(char ***line, char **buff, char **str, int fd)
{
	int		ret;
	char	*tmp;
	int		i;

	while ((ret = read(fd, *buff, BUFFER_SIZE)))
	{
		if (ret < 0)
			return (-1);
		(*buff)[ret] = '\0';
		i = ft_isnewline(*buff);
		if ((*buff)[i] == '\n' || (*buff)[i] == -1)
		{
			*(*line) = ft_stock(*(*line), *buff, i);
			tmp = *str;
			*str = ft_stock(*str, *buff + i + 1, ret - i - 1);
			return (ft_strdel(&tmp, buff, 2, 1));
		}
		if ((*buff)[i] == '\0')
			*(*line) = ft_stock(*(*line), *buff, i);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	int			i;
	static char	*str;
	char		*buff;

	if ((fd < 0) || (BUFFER_SIZE < 1) || (BUFFER_SIZE > MAX_INT) ||
		!(line) || !(buff = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	*line = ft_strdup("");
	if (ft_str(&line, &str, &buff) == 1)
		return (1);
	i = ft_read(&line, &buff, &str, fd);
	if (i == -1)
		return (-1);
	else if (i == 1)
		return (1);
	return (ft_strdel(&buff, &buff, 1, 0));
}
