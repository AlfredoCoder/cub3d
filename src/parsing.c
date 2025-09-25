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

static int	process_line(t_game *game, char *no_nl, int k)
{
	char	*tmp;
	int		result;

	if ((no_nl[k] == 'N' && no_nl[k + 1] == 'O' && no_nl[k + 2] == ' ')
		|| (no_nl[k] == 'S' && no_nl[k + 1] == 'O' && no_nl[k + 2] == ' ')
		|| (no_nl[k] == 'W' && no_nl[k + 1] == 'E' && no_nl[k + 2] == ' ')
		|| (no_nl[k] == 'E' && no_nl[k + 1] == 'A' && no_nl[k + 2] == ' ')
		|| (no_nl[k] == 'F' && no_nl[k + 1] == ' ')
		|| (no_nl[k] == 'C' && no_nl[k + 1] == ' '))
	{
		tmp = ft_strdup(no_nl + k);
		result = parse_config_line(game, tmp);
		free(tmp);
		return (result);
	}
	else
	{
		result = parse_config_line(game, no_nl);
		return (result);
	}
}

static void	handle_parse_error(t_game *game, int result)
{
	if (result == -1)
		free_game_and_exit(game, "Erro: Configuração após início do mapa.");
	else if (result == -3 || result == -2)
		free_game_and_exit(game, "Erro: Formato de cor inválido.");
	else if (result == -5)
		free_game_and_exit(game, "Erro: Caractere inválido no mapa.");
	else
		free_game_and_exit(game, "Erro: Arquivo de textura inválido.");
}

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

static void	process_file_line(t_game *game, char *line, int fd)
{
	char	*no_nl;
	int		k;
	int		result;

	no_nl = ft_strtrim(line, "\n\r");
	if (!no_nl)
		return ;
	k = 0;
	while (no_nl[k] == ' ' || no_nl[k] == '\t')
		k++;
	if (no_nl[k] == '\0')
	{
		handle_empty_line(game, no_nl, fd);
		free(no_nl);
		return ;
	}
	result = process_line(game, no_nl, k);
	free(no_nl);
	if (result < 0)
	{
		close(fd);
		get_next_line(-1);
		get_next_line(-1);
		handle_parse_error(game, result);
	}
}

void	parse_file(char *path, t_game *game)
{
	int		fd;
	char	*line;

	if (!is_valid_cub(path))
		free_game_and_exit(game, "Arquivo deve ter extensão .cub");
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Erro: não foi possível abrir o arquivo %s\n", path);
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		process_file_line(game, line, fd);
		free(line);
	}
	close(fd);
	get_next_line(-1);
	convert_list_to_map(game);
	validate_map(game);
}
