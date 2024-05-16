/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:20:45 by etornay-          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:19 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	movement(t_data *data, double x, double y)
{
	int	pos_x;
	int	pos_y;
	int	new_pos_x;
	int	new_pos_y;

	new_pos_x = roundf(data->person->pers_x + x);
	new_pos_y = roundf(data->person->pers_y + y);
	pos_x = (new_pos_x / SIZE);
	pos_y = (new_pos_y / SIZE);
	if (data->map[pos_y][pos_x] != '1'
		&& data->map[pos_y][data->person->pers_x / SIZE] != '1'
		&& data->map[data->person->pers_y / SIZE][pos_x] != '1')
	{
		data->person->pers_x = new_pos_x;
		data->person->pers_y = new_pos_y;
	}
}

void	cam_rotation(t_data *data, int i)
{
	if (i == 1)
	{
		data->person->ang += ROTATION;
		if (data->person->ang > (2 * M_PI))
			data->person->ang -= (2 * M_PI);
	}
	else
	{
		data->person->ang -= ROTATION;
		if (data->person->ang < 0)
			data->person->ang += (2 * M_PI);
	}
}

void	all_movement(t_data *data, double x, double y)
{
	if (data->person->rot == 1)
		cam_rotation(data, 1);
	if (data->person->rot == -1)
		cam_rotation(data, 0);
	if (data->person->up_dw == 1)
	{
		x = cos(data->person->ang) * SPEED;
		y = sin(data->person->ang) * SPEED;
	}
	if (data->person->up_dw == -1)
	{
		x = -cos(data->person->ang) * SPEED;
		y = -sin(data->person->ang) * SPEED;
	}
	if (data->person->lf_rt == 1)
	{
		x = -sin(data->person->ang) * SPEED;
		y = cos(data->person->ang) * SPEED;
	}
	if (data->person->lf_rt == -1)
	{
		x = sin(data->person->ang) * SPEED;
		y = -cos(data->person->ang) * SPEED;
	}
	movement(data, x, y);
}
