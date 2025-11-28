/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderridj <yderridj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:43:35 by yderridj          #+#    #+#             */
/*   Updated: 2025/10/31 16:08:49 by yderridj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stock[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock[fd] = ft_stocknread(stock[fd], fd);
	if (!stock[fd])
		return (NULL);
	line = ft_extract(stock[fd]);
	stock[fd] = ft_clean(stock[fd]);
	if (!stock[fd])
	{
		free(stock[fd]);
		stock[fd] = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	int		fd1;
// 	int		fd2;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	fd1 = open("test1.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	get_next_line(-1);
// 	close(fd);
// 	while ((line = get_next_line(fd1)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	get_next_line(-1);
// 	close(fd1);
// 	while ((line = get_next_line(fd2)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	get_next_line(-1);
// 	close(fd2);
// 	return (0);
// }
