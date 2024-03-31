/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 05:05:07 by abelechg          #+#    #+#             */
/*   Updated: 2024/03/28 05:05:56 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_data(char **data, size_t flag)
{
	char	*save;
	size_t	size;
	size_t	z;

	size = update_size(&(*data)[flag]);
	if (!size)
	{
		clear_string(data);
		return ;
	}
	save = malloc(sizeof(char) * (size + 1));
	if (!save)
	{
		clear_string(data);
		return ;
	}
	z = 0;
	while (size > z)
	{
		save[z] = (*data)[flag + z];
		z++;
	}
	save[z] = 0;
	clear_string(data);
	*data = save;
}

char	*sorte_new_line(char *data, size_t flag)
{
	char	*line;
	size_t	z;

	if (!flag)
		return (NULL);
	line = malloc(sizeof(char) * (flag + 1));
	if (!line)
		return (NULL);
	z = 0;
	while (flag > z)
	{
		line[z] = data[z];
		z++;
	}
	line[z] = 0;
	return (line);
}

void	function_read(int fd, char **data, size_t *flag)
{
	char	*buffer;
	ssize_t	size;

	size = search_for_nline(*data, flag);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		clear_string(data);
		return ;
	}
	while (!size)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == 0)
			break ;
		buffer[size] = 0;
		join_string(data, buffer, *flag, size);
		if (!*data)
		{
			clear_string(&buffer);
			return ;
		}
		size = search_for_nline(buffer, flag);
	}
	clear_string(&buffer);
}

char	*read_data(char **data, size_t flag)
{
	char	*line;

	if (!data || !*data)
		return (NULL);
	line = sorte_new_line(*data, flag);
	if (!line)
	{
		clear_string(data);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;
	size_t		new_line;

	new_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		clear_string(&data);
		return (NULL);
	}
	function_read(fd, &data, &new_line);
	line = read_data(&data, new_line);
	if (!line)
		return (NULL);
	update_data(&data, new_line);
	return (line);
}
