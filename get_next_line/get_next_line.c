/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:34:58 by anematol          #+#    #+#             */
/*   Updated: 2025/07/09 12:37:55 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUFFER_SIZE + 1];
	int			bytes_read;

	line = (char *)malloc(sizeof(char));
	if (!line || (read(fd, 0, 0) < 0) || BUFFER_SIZE <= 0 || fd < 0)
		return (free(line), NULL);
	line[0] = '\0';
	if (buf[0] == '\0')
		bytes_read = read(fd, buf, BUFFER_SIZE);
	if (buf[0] == '\0' && bytes_read == 0)
		return (free(line), NULL);
	while (!ft_lf_in_buf(buf) && buf[0] != '\0')
	{
		line = ft_add_buf(line, buf);
		if (!line)
			return (free(line), NULL);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (buf[0] != '\0')
		line = ft_add_buf(line, buf);
	if (!line)
		return (free(line), NULL);
	return (line);
}
