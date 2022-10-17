/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 16:34:14 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/17 19:53:28 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	main(int argc, char **argv)
{
	t_data			data;

	init_data(&data);
	data.map = make_map(argc, argv);
	map_validation(&data);
	data.mlx = mlx_init((data.map_width * TILESIZE), \
	(data.map_height * TILESIZE), "froggy_game", true);
	draw_sprites(&data);
	mlx_key_hook(data.mlx, (mlx_keyfunc)movement, &data);
	mlx_loop(data.mlx);
	end_game(&data);
	mlx_terminate(data.mlx);
	return (0);
}
