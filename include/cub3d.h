/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:48:06 by fguerra           #+#    #+#             */
/*   Updated: 2025/04/03 20:48:10 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define W 119
# define A 97
# define S 115
# define D 100
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define SPEED 0.01
# define ROTATE_ANGLE 0.008
# define LEFT 65361
# define RIGHT 65363
# define WIDTH 800
# define HEIGHT 600
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
//# define BUFFER_SIZE 1024
# define FOV 60
# define NUM_RAYS WIDTH
# define TILE_SIZE 64

typedef struct s_comands
{
	bool			key_a;
	bool			key_w;
	bool			key_d;
	bool			key_s;
	bool			key_left;
	bool			key_right;
}					t_comands;

typedef struct s_texture
{
	void				*img_ptr;
	char				*data;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	int direction; // 0: Norte, 1: Leste, 2: Sul, 3: Oeste
}					t_player;

typedef struct s_lmapp
{
	char			*line;
	struct s_lmapp	*next;
	struct s_lmapp	*prev;
}					t_lmapp;

typedef struct s_game
{
	t_texture		wall_texture;
	char			*tex_path_no;
	char			*tex_path_so;
	char			*tex_path_we;
	char			*tex_path_ea;

	int				floor_color;
	int				ceiling_color;
	int				map_height;
	int				bpp;
	int				size_line;
	char			*addr;
	int				endian;
	void			*mlx;
	void			*win;
	void			*img;
	t_texture		textures[4];
	char 		*texture_paths[4];
	t_coord			player_pos;
	t_coord			dir;
	t_coord			plane;
	t_coord			rayDir;
	t_player		player;
	t_comands		comands;
	char			**map;
	t_lmapp			*lmap;
}					t_game;

char				**ft_realloc_map(char **old_map, char *new_line);
void				init_game(t_game *game);
void				draw(t_game *game);
void				add_line_list(t_game *game, char *line);
int					restart_key(int keyboard, t_game *game);
void				convert_list_to_map(t_game *game);
void				free_map_list(t_lmapp *list);
t_coord				get_player_position(t_game *game);
void				clear_img(t_game *game);
void				render(t_game *game);
void				print_map(t_game *game);
void				load_map(char *file_name, t_game *game);
void				print_map(t_game *game);
int					close_game(t_game *game);
int					key_press(int keycode, t_game *game);
int					close_game(t_game *game);
int					is_wall(t_game *game, double x, double y);
int					parse_rgb(char *line);
int					is_valid_cub(char *argument);
int					is_valid_map_line(char *line);
int					check_rgb_value(char *str, int *pos);
int					is_valid_texture_path(char *line);
int					find_max_width(char **map);
int					load_textures(t_game *game);

void				draw_vertical(t_game *game, int x, int start_y, int end,
						int color);
void draw_wall(t_game *game, int pixel, int drawStart, int drawEnd,
	int side, double perpWallDist);
void	free_game_and_exit(t_game *game, const char *msg);
void	free_game_and_exit_xy(t_game *game, const char *msg, int i, int j);
void	put_pixel(t_game *game, int x, int y, int color);
//void				draw_walls(t_game *game);
void				input_key(t_game *game);
char				*read_line(int fd);
void				parse_file(char *path, t_game *game);
void				free_textures(t_game *game);
void				init_player(t_game *game);
int					parse_color(char *str);
void				print_error(char *msg);
int					key_handler(int keyboard, t_game *game);
void				free_game(t_game *game);
void				load_all_textures(t_game *game);
char				**ft_realloc_map(char **map, char *line);
char				*read_line(int fd);

#endif
