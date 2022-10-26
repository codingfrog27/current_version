/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 21:13:44 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/26 18:34:27 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief MLX keyhook function that get's called on every keypress
 * and moves are player when allowed
 * @param keydata needed for mlx_is_key and also autogiven when using keyhook
 * @param data our data struct ptr
 */
void	movement(mlx_key_data_t keydata, t_data *data)
{
	mlx_instance_t	*player;

	player = &data->images[PLAYER]->instances[0];
	if ((mlx_is_key_down(data->mlx, MLX_KEY_D) || \
	mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) && can_player_move(data, 1, 0))
		player->x += TILESIZE;
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_A) || \
	mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) && can_player_move(data, -1, 0))
		player->x -= TILESIZE;
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_S) || \
	mlx_is_key_down(data->mlx, MLX_KEY_DOWN)) && can_player_move(data, 0, 1))
		player->y += TILESIZE;
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_W) || \
	mlx_is_key_down(data->mlx, MLX_KEY_UP)) && can_player_move(data, 0, -1))
		player->y -= TILESIZE;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		end_game(data);
	(void)keydata;
}

/**
 * @brief sees if player can move
 *
 * @param data ptr to our data struct
 * @param x_direction modifier to the player position to see what tile to check
 * @param y_direction modifier to the player position to see what tile to check
 * @return true Move allowed!
 * @return false  Can't move to designated tile
 */
bool	can_player_move(t_data *data, int x_direction, int y_direction)
{
	const int	x = data->player_x + x_direction;
	const int	y = data->player_y + y_direction;

	if (data->map[y][x] == '1')
		return (false);
	if (data->map[y][x] == 'E')
	{
		if (data->collect_amount > 0)
		{
			mlx_put_string(data->mlx, "more pizza plss", \
			data->player_x * TILESIZE, data->player_y * TILESIZE + 50);
			return (false);
		}
		complete_msg(data);
	}
	data->player_x += x_direction;
	data->player_y += y_direction;
	if (data->map[y][x] == 'C')
		hide_collectible(data, y, x);
	place_move_nbr(data);
	return (true);
}

void	complete_msg(t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png("textures/victory.png");
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_image_to_window(data->mlx, image, data->map_width / 2 * TILESIZE, \
	data->map_height / 2 * TILESIZE);
}

/**
 * @brief displayes the amount of moves the player has taken
 * int the top right corner of the screen
 * @param data
 */
void	place_move_nbr(t_data *data)
{
	static int	steps;
	char		*move_str;

	steps++;
	if (data->step_text)
		mlx_delete_image(data->mlx, data->step_text);
	move_str = ft_itoa(steps);
	if (!move_str)
		error_exit("malloc fail");
	data->step_text = mlx_put_string(data->mlx, move_str, 30, 20);
	free(move_str);
	ft_printf("\033[0;32m %i tiles Flown\n\033[0;m", steps);
}

/**
 * @brief Looks for the collectible at our player pos
 * and sets it to disabled
 * @param data pointer to our data struct
 * @param y_match y pos to look for
 * @param x_match x pos to look for
 */
void	hide_collectible(t_data *data, int y_match, int x_match)
{
	int			y;
	int			x;
	int			index;

	x = 0;
	y = 0;
	index = -1;
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			if (data->map_copy[y][x] == 'C')
				index++;
			if (x == x_match && y == y_match)
			{
				ft_printf("\033[0;33mPizza time!\033[0;m\n");
				data->images[1]->instances[index].enabled = false;
				data->map[y][x] = '0';
				data->collect_amount--;
			}
			x++;
		}
	y++;
	x = 0;
	}
}
