/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:27:29 by etornay-          #+#    #+#             */
/*   Updated: 2024/05/06 13:28:11 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	data->person = NULL;
	data->ray = NULL;
	data->e_counter = 0;
}
