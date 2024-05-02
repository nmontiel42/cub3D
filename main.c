/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:03:53 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/02 13:18:16 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Comprueba que el archivo del mapa sea .cub

int	check_map_name(char *name)
{
	int	i;

	i = ft_strlen(name) - 1;
	if (name[i] != 'b' || name[i - 1] != 'u'
		|| name[i - 2] != 'c' || name[i - 3] != '.')
		return (false);
	return (true);
}

//Inicializa la estructura de datos que usamos

void	init_data(t_data *data)
{
	data->c_rgb = NULL;
	data->f_rgb = NULL;
	data->count_textures = 0;
	data->fd = 0;
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->h_map = 0;
	data->w_map = 0;
	data->ea = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->img = NULL;
	data->line = NULL;
	data->map = NULL;
	data->mlx = NULL;
	data->p_x = 0;
	data->p_y = 0;
	data->ply = NULL;
	data->ray = NULL;
	data->e_counter = 0;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	atexit(ft_leaks);
	if (argc == 2)
	{
		if (!check_map_name(argv[1]))
			ft_error(WNAME);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_error(NOFD);
		init_data(&data);
		if (read_map(&data, argv[1]))
			return (free_data(&data), 1);
		free_data(&data);
		return (0);
	}
	ft_error(WARG);
}

void	ft_leaks(void)
{
	system("leaks -q cub3D");
}

//imprimir mapa
/*int i = -1;
while (data.map[++i])
	printf("%s\n", data.map[i]);*/