/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:59:56 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/03 14:53:09 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	keys(mlx_key_data_t k, void *ks)
{
	t_data	*data;

	data = ks;
	if (k.key == MLX_KEY_ESCAPE && (k.action == MLX_PRESS
			|| k.action == MLX_REPEAT))
	{
		mlx_delete_image(data->mlx, data->img);
		mlx_close_window(data->mlx);
		free_data(data);
		mlx_terminate(data->mlx);
		exit(0);
	}
	else if (k.key == MLX_KEY_A && k.action == MLX_PRESS)
		data->person->lf_rt = -1;
	else if (k.key == MLX_KEY_A && k.action == MLX_RELEASE)
		data->person->lf_rt = 0;
	else if (k.key == MLX_KEY_W && k.action == MLX_PRESS)
		data->person->up_dw = 1;
	else if (k.key == MLX_KEY_W && k.action == MLX_RELEASE)
		data->person->up_dw = 0;
	else if (k.key == MLX_KEY_S && k.action == MLX_PRESS)
		data->person->up_dw = -1;
	else if (k.key == MLX_KEY_S && k.action == MLX_PRESS)
		data->person->up_dw = 0;
	keys2(k, ks);
}

void	keys2(mlx_key_data_t k, void *ks)
{
	t_data	*data;

	data = ks;
	if (k.key == MLX_KEY_D && k.action == MLX_PRESS)
		data->person->lf_rt = 1;
	else if (k.key == MLX_KEY_D && k.action == MLX_PRESS)
		data->person->lf_rt = 0;
	else if (k.key == MLX_KEY_RIGHT && k.action == MLX_PRESS)
		data->person->rot = 1;
	else if (k.key == MLX_KEY_LEFT && k.action == MLX_PRESS)
		data->person->rot = -1;
	else if (k.key == MLX_KEY_RIGHT && k.action == MLX_PRESS)
		data->person->rot = 0;
	else if (k.key == MLX_KEY_LEFT && k.action == MLX_PRESS)
		data->person->rot = 0;
}
