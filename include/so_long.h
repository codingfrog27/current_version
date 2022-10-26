/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 16:34:39 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/26 21:04:36 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "MLX42.h"

//not sure if allowed to use
# define TILESIZE 64
// stands for bits per pixel (want to be sizeof(int32_t)
// but norminette doesn't allow it)
# define PLAYER 3
# define BACKGROUND 4

typedef struct s_data {
	mlx_t			*mlx;
	mlx_image_t		*images[5];
	mlx_image_t		*step_text;
	mlx_texture_t	*textures[5];
	char			**map;
	char			**map_copy;
	int				map_height;
	int				map_width;
	int				collect_amount;
	int				player_x;
	int				player_y;
	int				bg_tiles_nb;
	bool			exit_reachable;
	bool			collects_reachable;
}	t_data;

// map making
char	**make_map(int argc, char **argv);

//map validation
void	map_validation(t_data *data);

//sprites
void	draw_sprites(t_data *data);

//movement
void	movement(mlx_key_data_t keydata, t_data *data);
bool	can_player_move(t_data *data, int x_direction, int y_direction);
void	hide_collectible(t_data *data, int y_match, int x_match);
void	place_move_nbr(t_data *data);
void	complete_msg(t_data *data);

//utils
void	error_exit(char *s);
void	find_player_pos(t_data *data);
char	**copy_map(t_data	*data);
void	free_map(char **map);
void	init_data(t_data *data);
void	end_game(t_data *data);
#endif