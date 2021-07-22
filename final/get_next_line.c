/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:55:17 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/21 16:15:27 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*save_line(char *track)
{
	char	*line;
	int		i;

	if (!track)
		return (NULL);
	i = 0;
	while (track[i] != '\n' && track[i] != '\0')
		i++;
	line = malloc ((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (track[i] != '\n' && track[i] != '\0')
	{
		line[i] = track[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_track(char *track, int i, int j)
{
	char	*temp;

	if (!track)
		return (NULL);
	while (track[i] != '\n' && track[i] != '\0')
		i++;
	if (i == ft_strlen(track))
	{
		free(track);
		return (NULL);
	}
	temp = malloc((ft_strlen(track + i) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (track[i + j + 1] != '\0')
	{
		temp[j] = track[i + j + 1];
		j++;
	}
	temp[j] = '\0';
	free(track);
	return (temp);
}

int	free_buffer(char *buffer)
{
	free(buffer);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	int			reader;
	static char	*track;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	reader = 1;
	while (reader && !contains_new_line(track))
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
			return (free_buffer(buffer));
		buffer[reader] = 0;
		track = ft_strjoin(track, buffer);
	}
	*line = save_line(track);
	track = update_track(track, 0, 0);
	free(buffer);
	if (reader == 0)
		return (0);
	return (1);
}
