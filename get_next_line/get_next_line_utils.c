/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:10:20 by anematol          #+#    #+#             */
/*   Updated: 2025/06/18 19:09:26 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_lf(char *str, int with_lf)
{
	int	i;

	i = 0;
	if (with_lf)
	{
		while (str[i] != '\0' && str[i] != '\n')
		{
			i++;
		}
		if (str[i] == '\n')
			i++;
		return (i);
	}
	else
	{
		while (str[i] != '\0')
		{
			i++;
		}
		return (i);
	}
}

char	*ft_add_buf(char *line, char *buf)
{
	int		len;
	int		next_len;
	char	*temp;
	int		i;

	i = -1;
	len = ft_strlen_lf(line, 0);
	next_len = ft_strlen_lf(buf, 1);
	temp = (char *)malloc((len + next_len + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (++i < len)
		temp[i] = line[i];
	i = 0;
	while (i < next_len)
	{
		temp[len + i] = buf[i];
		i++;
	}
	temp[len + i] = '\0';
	free(line);
	buf = ft_update_buf(buf, next_len);
	return (temp);
}

int	ft_lf_in_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_update_buf(char *buf, int delete_up_to)
{
	int	i;

	i = 0;
	while (buf[delete_up_to + i] != '\0')
	{
		buf[i] = buf[delete_up_to + i];
		i++;
	}
	while (i < BUFFER_SIZE + 1)
	{
		buf[i] = '\0';
		i++;
	}
	return (buf);
}
