/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 21:13:44 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/15 00:43:59 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	movement_2_electric_boogaloo(mlx_key_data_t keydata, t_data *data)
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

bool	can_player_move(t_data *data, int x_direction, int y_direction)
{
	static int	steps;
	const int	x = data->p_x + x_direction;
	const int	y = data->p_y + y_direction;

	if (data->map[y][x] == '1')
		return (false);
	if (data->map[y][x] == 'E')
	{
		if (data->collect_amount > 0)
		{
			mlx_put_string(data->mlx, "can i haz all the pizza? uwu", \
			data->p_x * TILESIZE, data->p_y * TILESIZE + 50);
			return (false);
		}
		end_game(data);
	}
	data->p_x += x_direction;
	data->p_y += y_direction;
	if (data->map[y][x] == 'C')
		hide_collectible(data, x, y);
	steps++;
	mlx_put_string(data->mlx, ft_itoa(steps), data->p_x * 64, data->p_y * 64);
	ft_printf("\033[0;32m %i tiles Flown\n\033[0;m", steps);
	return (true);
}

void	hide_collectible(t_data *data, int y_match, int x_match)
{
	int	y;
	int	x;
	int	index;

	x = 0;
	y = 0;
	index = -1;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'C')
				index++;
			if (x == x_match && y == y_match)
			{
				ft_printf("\033[0;33mPizza time!\033[0;m\n");
				data->map[y][x] = '0';
				data->images[1]->instances[index].enabled = false;
				data->collect_amount--;
			}
			x++;
		}
	y++;
	x = 0;
	}
}
