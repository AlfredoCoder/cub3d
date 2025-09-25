/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:25:36 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:17:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	handle_empty_line(t_game *game, char *no_nl, int fd)
{
	int	result;

	result = parse_config_line(game, no_nl);
	if (result < 0)
	{
		close(fd);
		get_next_line(-1);
		get_next_line(-1);
		free_game_and_exit(game, "Erro de parsing na linha vazia");
	}
}

static int	handle_line_error(int fd, int result)
{
	close(fd);
	get_next_line(-1);
	get_next_line(-1);
	return (result);
}

static int	process_file_line(t_game *game, char *line, int fd)
{
	char	*no_nl;
	int		k;
	int		result;

	no_nl = ft_strtrim(line, "\n\r");
	if (!no_nl)
		return (0);
	k = 0;
	while (no_nl[k] == ' ' || no_nl[k] == '\t')
		k++;
	if (no_nl[k] == '\0')
	{
		handle_empty_line(game, no_nl, fd);
		free(no_nl);
		return (0);
	}
	result = process_line(game, no_nl, k);
	free(no_nl);
	if (result < 0)
		return (handle_line_error(fd, result));
	return (0);
}

static void	process_file_loop(t_game *game, int fd)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line != NULL)
	{
		result = process_file_line(game, line, fd);
		free(line);
		if (result < 0)
			handle_parse_error(game, result);
		line = get_next_line(fd);
	}
}

void	parse_file(char *path, t_game *game)
{
	int		fd;

	if (!is_valid_cub(path))
		free_game_and_exit(game, "Arquivo deve ter extensão .cub");
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Erro: não foi possível abrir o arquivo %s\n", path);
		exit(EXIT_FAILURE);
	}
	process_file_loop(game, fd);
	close(fd);
	get_next_line(-1);
	convert_list_to_map(game);
	validate_map(game);
}
