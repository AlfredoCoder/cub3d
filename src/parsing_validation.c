/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 06:17:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:17:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_cub(char *argument)
{
	int	len;

	len = 0;
	while (argument[len])
		len++;
	if (len <= 4)
		return (0);
	return (argument[len - 4] == '.' && argument[len - 3] == 'c'
		&& argument[len - 2] == 'u' && argument[len - 1] == 'b'
		&& argument[len - 5] != '/');
}

int	check_texture_path(char *path)
{
	int	len;
	int	fd;

	len = 0;
	while (path[len])
		len++;
	if (len < 4)
		return (0);
	if (!(path[len - 4] == '.' && path[len - 3] == 'x'
			&& path[len - 2] == 'p' && path[len - 1] == 'm'))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	get_char_at(t_game *game, int row, int col)
{
	if (row < 0 || row >= game->map_height)
		return ('X');
	if (col < 0 || col >= (int)ft_strlen(game->map[row]))
		return ('X');
	return (game->map[row][col]);
}

int	is_playable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
