/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:16:02 by hbaduel           #+#    #+#             */
/*   Updated: 2023/02/22 18:16:03 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_checkendline(char *file)
{
	size_t	i;

	i = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_read(int fd)
{
	char	*letters;
	int		resultread;

	letters = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!letters)
		return (NULL);
	resultread = read(fd, letters, BUFFER_SIZE);
	if (resultread == 0 || resultread == -1)
	{
		free(letters);
		return (NULL);
	}
	letters[resultread] = '\0';
	return (letters);
}

char	*ft_mallocsize1(void)
{
	char	*file;

	file = malloc(sizeof(char) * 1);
	if (!file)
		return (NULL);
	file [0] = '\0';
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file[65534];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(file[fd]);
		file[fd] = NULL;
		return (NULL);
	}
	if (!file[fd])
		file[fd] = ft_mallocsize1();
	while (ft_checkendline(file[fd]) == 1)
	{
		line = ft_read(fd);
		if (!line)
			break ;
		file[fd] = ft_strjoin_modif(file[fd], line);
		if (!file[fd])
			return (NULL);
	}
	line = ft_select(file[fd]);
	file[fd] = ft_reduce(file[fd]);
	return (line);
}
