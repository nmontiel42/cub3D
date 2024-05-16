/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:03:53 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/16 17:59:45 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_angle(t_data *data)
{
	char	degrees;

	degrees = data->map[data->p_y][data->p_x];
	if (degrees == 'N')
		data->person->ang = (3 * M_PI) / 2;
	if (degrees == 'E')
		data->person->ang = 0;
	if (degrees == 'S')
		data->person->ang = M_PI / 2;
	if (degrees == 'W')
		data->person->ang = M_PI;
	data->person->pers_x = (data->p_x * SIZE) + SIZE / 2;
	data->person->pers_y = (data->p_y * SIZE) + SIZE / 2;
	data->person->vis_rd = (VISION * M_PI / 180);
}

void	print_map(void *ks)
{
	t_data	*data;

	data = ks;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	all_movement(data, 0, 0);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int	initialize_game(t_data *data)
{
	if (WIDTH > 2500 || HEIGHT > 1300 || VISION >= 180 || VISION <= 0)
		return (ft_error2(E_LIM));
	data->person = ft_calloc(1, sizeof(t_person));
	data->ray = ft_calloc(1, sizeof(t_ray));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!data->person || !data->ray || !data->mlx)
		return (1);
	ft_angle(data);
	mlx_key_hook(data->mlx, &keys, data);
	mlx_loop_hook(data->mlx, &print_map, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	if (argc == 2)
	{
		if (!check_map_name(argv[1]))
			return (ft_error(W_NAME));
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (ft_error(N_OFD));
		init_data(&data);
		if (read_map(&data, argv[1]))
			return (free_data(&data), 1);
		if (initialize_game(&data))
			return (free_data(&data), 1);
		free_data(&data);
		return (0);
	}
	ft_error(W_ARG);
}
