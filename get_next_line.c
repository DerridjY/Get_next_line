/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderridj <yderridj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:43:35 by yderridj          #+#    #+#             */
/*   Updated: 2025/11/14 09:44:35 by yderridj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_stocknread(char *stock, int fd)
{
	char		*buf;
	ssize_t		bytes;

	bytes = 1;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!ft_strchr(stock, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			buf = NULL;
			if (stock)
				free(stock);
			return (NULL);
		}
		buf[bytes] = '\0';
		stock = ft_strjoin(stock, buf);
	}
	free(buf);
	return (stock);
}

char	*ft_extract(char *stock)
{
	char	*line;

	line = ft_strdup(stock);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_clean(char *stock)
{
	char	*cleanstock;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	cleanstock = malloc(sizeof(char) * (ft_strlen(stock) - i) + 1);
	if (!cleanstock)
		return (NULL);
	i++;
	while (stock[i])
		cleanstock[j++] = stock[i++];
	cleanstock[j] = '\0';
	free(stock);
	return (cleanstock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = ft_stocknread(stock, fd);
	if (!stock)
		return (NULL);
	line = ft_extract(stock);
	stock = ft_clean(stock);
	if (!stock)
	{
		free(stock);
		stock = NULL;
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	get_next_line(-1);
	close(fd);
	return (0);
}
