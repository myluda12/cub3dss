/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajrhou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:07:31 by ayajrhou          #+#    #+#             */
/*   Updated: 2019/10/31 22:13:26 by ayajrhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_strdel(char **tmp, char **str, int num, int ret)
{
	if (*tmp != NULL)
	{
		free(*tmp);
		*tmp = NULL;
	}
	if (num == 2)
	{
		if (*str != NULL)
		{
			free(*str);
			*str = NULL;
		}
	}
	return (ret);
}

int			ft_isnewline(char *buff)
{
	int		i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	return (i);
}

int			ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char		*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	dest = malloc(sizeof(char) * (i + 1));
	return (ft_strcpy(dest, src));
}
