/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 06:17:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:17:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_texture_direction(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (NORTH);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (SOUTH);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (WEST);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (EAST);
	return (-1);
}

static int	handle_texture_config(t_game *game, char *line)
{
	char	*path;
	int		direction;

	path = ft_strtrim(line + 2, " \t");
	if (!path)
		return (-1);
	if (!check_texture_path(path))
	{
		free(path);
		return (-1);
	}
	direction = get_texture_direction(line);
	if (direction == -1)
	{
		free(path);
		return (-9);
	}
	if (game->texture_paths[direction] != NULL)
	{
		free(path);
		return (-6);
	}
	game->texture_paths[direction] = path;
	return (0);
}

static int	handle_color_config(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (handle_floor_color(game, line));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (handle_ceiling_color(game, line));
	return (-4);
}

int	parse_config_line(t_game *game, char *line)
{
	static int	map_started = 0;

	if (!line || !*line)
		return (0);
	if (is_valid_map_line(line))
	{
		map_started = 1;
		add_line_list(game, line);
		return (1);
	}
	if (map_started)
		return (-1);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (handle_texture_config(game, line));
	return (handle_color_config(game, line));
}
