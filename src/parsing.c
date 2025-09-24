/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:25:36 by fguerra           #+#    #+#             */
/*   Updated: 2025/05/07 16:25:39 by fguerra          ###   ########.fr       */
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
		return 0;

	return (argument[len - 4] == '.' &&
		argument[len - 3] == 'c' &&
		argument[len - 2] == 'u' &&
		argument[len - 1] == 'b' &&
		argument[len - 5] != '/');
}

int	check_rgb_value(char *str, int *pos)
{
	int	value;
	int	i;

	value = 0;
	i = *pos;
	
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	
	if (str[i] < '0' || str[i] > '9')
		return (-1);	
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
			return (-1);
		i++;
	}
	
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	
	*pos = i;
	return (value);
}

int	parse_rgb(char *line)
{
	int	r, g, b;
	int	pos;

	pos = 0;
	
	// Ler R
	r = check_rgb_value(line, &pos);
	if (r < 0 || r > 255 || line[pos] != ',')
		return (-1);
	pos++; // Pular a vírgula
	
	// Ler G
	g = check_rgb_value(line, &pos);
	if (g < 0 || g > 255 || line[pos] != ',')
		return (-1);
	pos++; // Pular a vírgula
	
	// Ler B
	b = check_rgb_value(line, &pos);
	if (b < 0 || b > 255)
		return (-1);
	
	// Verificar se chegamos ao final da string ou se há apenas espaços
	while (line[pos])
	{
		if (line[pos] != ' ' && line[pos] != '\t')
			return (-1);
		pos++;
	}
	
	return ((r << 16) | (g << 8) | b);
}

int	is_valid_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);

	// Linha vazia é válida apenas antes do mapa
	if (line[0] == '\0')
		return (1);

	// Verifica se é configuração
	if (ft_strncmp(line, "NO ", 3) == 0 ||
		ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0 ||
		ft_strncmp(line, "F ", 2) == 0 ||
		ft_strncmp(line, "C ", 2) == 0)
		return (1);

	// Caso contrário, só pode ser linha de mapa
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_texture_path(char *path)
{
	int	len;

	if (!path || !*path)
		return (0);
	
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	
	// Verificar se termina com .xpm
	if (path[len - 4] != '.' || 
		path[len - 3] != 'x' || 
		path[len - 2] != 'p' || 
		path[len - 1] != 'm')
		return (0);
	
	return (1);
}

void	add_line_list(t_game *game, char *line)
{
	t_lmapp	*new_node;
	t_lmapp	*temp;

	if (!game || !line)
		return ;	
	new_node = malloc(sizeof(t_lmapp));
	if (!new_node)
		return ;
	new_node->line = ft_strdup(line);
	new_node->prev = NULL;
	new_node->next = NULL;
	if (!game->lmap)
	{
		game->lmap = new_node;
		return ;
	}
	temp = game->lmap;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;	
}

/* CONVERT_LIST_TO_MAP: normaliza largura das linhas preenchendo com ' ' */
void	convert_list_to_map(t_game *game)
{
	int		count;
	int		i;
	int		max_len;
	t_lmapp	*tmp;
	size_t	len;

	if (!game || !game->lmap)
		return ;
	count = 0;
	max_len = 0;
	tmp = game->lmap;
	while (tmp)
	{
		len = ft_strlen(tmp->line);
		if ((int)len > max_len)
			max_len = (int)len;
		count++;
		tmp = tmp->next;
	}
	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		return ;
	tmp = game->lmap;
	i = 0;
	while (i < count && tmp)
	{
		len = ft_strlen(tmp->line);
		game->map[i] = malloc(max_len + 1);
		if (!game->map[i])
		{
			/* em caso de falha, libera já o que foi alocado */
			while (--i >= 0)
				free(game->map[i]);
			free(game->map);
			game->map = NULL;
			return ;
		}
		ft_memset(game->map[i], ' ', max_len);
		if (len > 0)
			ft_memcpy(game->map[i], tmp->line, len);
		game->map[i][max_len] = '\0';
		tmp = tmp->next;
		i++;
	}
	game->map[i] = NULL;
	game->map_height = count;
}

void	free_map_list(t_lmapp *list)
{
	t_lmapp	*tmp;
	while (list)
	{
		tmp = list->next;
		free(list->line);
		free(list);
		list = tmp;
	}
}


int	parse_config_line(t_game *game, char *line)
{
	static int	map_started = 0;

	if (!line || line[0] == '\0')
		return (0);

	// Verificar se é uma linha de textura ou cor
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (map_started)
			return (-1); // Error: texture defined after map start
		if (game->texture_paths[NORTH])
			return (-2); // Error: duplicate texture
		if (!check_texture_path(line + 3))
			return (-3); // Error: invalid texture path
		game->texture_paths[NORTH] = ft_strdup(line + 3);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map_started)
			return (-1);
		if (game->texture_paths[SOUTH])
			return (-2);
		if (!check_texture_path(line + 3))
			return (-3);
		game->texture_paths[SOUTH] = ft_strdup(line + 3);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (map_started)
			return (-1);
		if (game->texture_paths[WEST])
			return (-2);
		if (!check_texture_path(line + 3))
			return (-3);
		game->texture_paths[WEST] = ft_strdup(line + 3);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (map_started)
			return (-1);
		if (game->texture_paths[EAST])
			return (-2);
		if (!check_texture_path(line + 3))
			return (-3);
		game->texture_paths[EAST] = ft_strdup(line + 3);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
	    if (map_started)
		return (-1);
	    if (game->floor_color == -1) // ainda não definido
		game->floor_color = parse_rgb(line + 2);
	    else
		return (-2); // duplicate
	    if (game->floor_color < 0)
		return (-4); // invalid format
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
	    if (map_started)
		return (-1);
	    if (game->ceiling_color == -1) // ainda não definido
		game->ceiling_color = parse_rgb(line + 2);
	    else
		return (-2); // duplicate
	    if (game->ceiling_color < 0)
		return (-4); // invalid format
	}
	else
	{
		// Se não for nenhum dos identificadores acima, deve ser uma linha de mapa
		if (!is_valid_map_line(line))
			return (-5); // invalid map line
		map_started = 1;
		add_line_list(game, line);
	}
	return (0);
}



/**
 * Verifica se o caractere representa um espaço jogável ('0', 'N', 'S', 'E', 'W')
 */


/* get_char_at: devolve 'X' para fora dos limites (inválido absoluto) */
char get_char_at(t_game *game, int row, int col)
{
    if (row < 0 || row >= game->map_height)
        return ('X');
    if (!game->map[row])
        return ('X');
    if (col < 0)
        return ('X');
    if (col >= (int)ft_strlen(game->map[row]))
        return ('X');
    return (game->map[row][col]);
}

int is_playable(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	free_game_and_exit(t_game *game, const char *msg)
{
	if (msg)
		printf("%s\n", msg);

	free_textures(game);

	if (game->map)
	{
		for (int i = 0; i < game->map_height; i++)
			free(game->map[i]);
		free(game->map);
		game->map = NULL;
	}

	if (game->lmap)
	{
		free_map_list(game->lmap);
		game->lmap = NULL;
	}

	// se tiver mlx
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}

	exit(EXIT_FAILURE);
}

/* versão que mostra também a posição (linha,coluna) */
void	free_game_and_exit_xy(t_game *game, const char *msg, int i, int j)
{
	if (msg)
		printf("Erro: %s em [%d,%d]\n", msg, i, j);
	free_game_and_exit(game, NULL);
}

void validate_walls(t_game *game)
{
    int i;
    int j;
    int last_row;
    int row_len;

    if (!game || !game->map || !game->map[0])
        free_game_and_exit(game, "Mapa vazio ou inválido");

    last_row = game->map_height - 1;

    for (i = 0; i < game->map_height; i++)
    {
        row_len = (int)ft_strlen(game->map[i]);
        for (j = 0; j < row_len; j++)
        {
            char current = game->map[i][j];

            /* caractere inválido */
            if (current != '0' && current != '1' &&
                current != 'N' && current != 'S' &&
                current != 'E' && current != 'W' &&
                current != ' ')
            {
                free_game_and_exit_xy(game, "Caractere inválido no mapa", i, j);
            }

            /* se for jogável precisa de vizinhança consistente */
            if (is_playable(current))
            {
                /* bordas rígidas (não pode começar na borda) */
                if (i == 0 || i == last_row || j == 0 || j == row_len - 1)
                    free_game_and_exit_xy(game, "Espaço jogável na borda", i, j);

                char above = get_char_at(game, i-1, j);
                char below = get_char_at(game, i+1, j);
                char left  = get_char_at(game, i, j-1);
                char right = get_char_at(game, i, j+1);

                /* adjacente a espaço explícito no ficheiro => erro */
                if (above == ' ' || below == ' ' || left == ' ' || right == ' ')
                    free_game_and_exit_xy(game, "Espaço jogável adjacente a vazio", i, j);

                /* adjacente a fora do mapa (X) => erro */
                if (above == 'X' || below == 'X' || left == 'X' || right == 'X')
                    free_game_and_exit_xy(game, "Espaço jogável adjacente a fora do mapa", i, j);

                /* adjacente a caractere estranho */
                if ((above != '1' && !is_playable(above)) ||
                    (below != '1' && !is_playable(below)) ||
                    (left  != '1' && !is_playable(left))  ||
                    (right != '1' && !is_playable(right)))
                {
                    free_game_and_exit_xy(game, "Espaço jogável com vizinhança inválida", i, j);
                }
            }

            /* se for espaço explícito, não pode tocar área jogável */
            if (current == ' ')
            {
                char above = get_char_at(game, i-1, j);
                char below = get_char_at(game, i+1, j);
                char left  = get_char_at(game, i, j-1);
                char right = get_char_at(game, i, j+1);

                if (is_playable(above) || is_playable(below) ||
                    is_playable(left)  || is_playable(right))
                {
                    free_game_and_exit_xy(game, "Espaço vazio adjacente a área jogável", i, j);
                }
            }
        }
    }

    /* primeira e última linha: só '1' ou ' ' (padding) */
    for (i = 0; i < game->map_height; i++)
    {
        if (i != 0 && i != last_row)
            continue;
        row_len = (int)ft_strlen(game->map[i]);
        for (j = 0; j < row_len; j++)
        {
            if (game->map[i][j] != '1' && game->map[i][j] != ' ')
                free_game_and_exit_xy(game, "Borda deve conter apenas '1' ou ' '", i, j);
        }
    }
}

void validate_player(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				player_count++;
				game->player.x = j + 0.5; 
				game->player.y = i + 0.5;
				game->player.direction = game->map[i][j];
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("Erro: Deve haver exatamente um jogador no mapa.\n");
		exit(EXIT_FAILURE);
	}
}

void	validate_map(t_game *game)
{
	if (!game->lmap || game->map_height <= 0)
	{
		free_game_and_exit(game, "Mapa não definido ou vazio e inválido");
	}
	if (!game->texture_paths[NORTH] || !game->texture_paths[SOUTH] ||
		!game->texture_paths[WEST] || !game->texture_paths[EAST])
	{
		free_game_and_exit(game, "Caminhos de textura não definidos");
	}
	if (game->floor_color == -1)
	{
		free_game_and_exit(game, "Linha do chão (F) ausente no arquivo de configuração");
	}
	if (game->ceiling_color == -1)
	{
		free_game_and_exit(game, "Linha do teto (C) ausente no arquivo de configuração");
	}
	if (game->floor_color < 0 || game->ceiling_color < 0)
	{
		free_game_and_exit(game, "Cores do chão ou do teto inválidas");
	}
	
	validate_walls(game);
	validate_player(game);
}

void	parse_file(char *path, t_game *game)
{
	int		fd;
	char	*line;
	char	*no_nl;
	char	*tmp;
	int		k;
	int		result;

	if (!is_valid_cub(path))
	{
		printf("Erro: arquivo inválido, deve ser .cub\n");
		exit(EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Erro: não foi possível abrir o arquivo %s\n", path);
		exit(EXIT_FAILURE);
	}
	line = NULL;
	no_nl = NULL;
	tmp = NULL;
	while ((line = get_next_line(fd)))
	{
		/* remover apenas newline/carriage return — preserva espaços */
		no_nl = ft_strtrim(line, "\n\r");
		free(line);
		line = NULL;
		if (!no_nl)
			continue;

		/* primeiro caractere não-espaço */
		k = 0;
		while (no_nl[k] == ' ' || no_nl[k] == '\t')
			k++;

		/* linha vazia (apenas espaços) */
		if (no_nl[k] == '\0')
		{
			result = parse_config_line(game, no_nl);
			free(no_nl);
			no_nl = NULL;
			if (result < 0)
			{
				close(fd);
				get_next_line(-1); // Clean up static buffer
				free_game_and_exit(game, "Erro de parsing na linha vazia");
			}
			continue;
		}

		/* se o primeiro não-espaço é um identificador (NO, SO, WE, EA, F, C),
		   passamos a substring sem espaços iniciais para parse_config_line */
		if ((no_nl[k] == 'N' && no_nl[k + 1] == 'O' && no_nl[k + 2] == ' ') ||
			(no_nl[k] == 'S' && no_nl[k + 1] == 'O' && no_nl[k + 2] == ' ') ||
			(no_nl[k] == 'W' && no_nl[k + 1] == 'E' && no_nl[k + 2] == ' ') ||
			(no_nl[k] == 'E' && no_nl[k + 1] == 'A' && no_nl[k + 2] == ' ') ||
			(no_nl[k] == 'F' && no_nl[k + 1] == ' ') ||
			(no_nl[k] == 'C' && no_nl[k + 1] == ' '))
		{
			tmp = ft_strdup(no_nl + k);
			result = parse_config_line(game, tmp);
			free(tmp);
			tmp = NULL;
			free(no_nl);
			no_nl = NULL;
			if (result < 0)
			{
				close(fd);
				get_next_line(-1); // Clean up static buffer
				if (result == -4)
					free_game_and_exit(game, "Erro: Formato de cor do teto (C) inválido.");
				else
					free_game_and_exit(game, "Erro de parsing na configuração");
			}
		}
		else
		{
			/* é linha de mapa — preservamos espaços à esquerda e à direita */
			result = parse_config_line(game, no_nl);
			free(no_nl);
			no_nl = NULL;
			if (result < 0)
			{
				close(fd);
				get_next_line(-1); // Clean up static buffer
				free_game_and_exit(game, "Erro de parsing na linha de mapa");
			}
		}
	}
	close(fd);

	/* converter e validar */
	convert_list_to_map(game);
	validate_map(game);
	/* limpeza de lista feita fora (como antes) */
}

