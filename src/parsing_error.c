/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 07:46:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 07:46:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	handle_parse_error(t_game *game, int result)
{
	if (result == -1)
		free_game_and_exit(game, "Erro: Arquivo de textura inválido.");
	else if (result == -3 || result == -2)
		free_game_and_exit(game, "Erro: Formato de cor inválido.");
	else if (result == -5)
		free_game_and_exit(game, "Erro: Caractere inválido no mapa.");
	else if (result == -6)
		free_game_and_exit(game, "Erro: Textura duplicada.");
	else if (result == -7)
		free_game_and_exit(game, "Erro: Cor do chão (F) duplicada.");
	else if (result == -8)
		free_game_and_exit(game, "Erro: Cor do teto (C) duplicada.");
	else if (result == -9)
		free_game_and_exit(game, "Erro: textura inválida (NO, SO, WE, EA).");
	else
		free_game_and_exit(game, "Erro: Configuração após início do mapa.");
}
