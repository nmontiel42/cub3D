/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:56:35 by etornay-          #+#    #+#             */
/*   Updated: 2024/05/15 14:25:21 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	angle_circle(float angle, char axis)
{
	if (axis == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (axis == 'y')
	{
		if (angle > (M_PI / 2) && angle < ((3 * M_PI) / 2))
			return (1);
	}
	return (0);
}

float	vertical_cross(t_data *data, float angle)
{
	float	vertical_x;
	float	vertical_y;
	float	x_limit;
	float	y_limit;
	int		pixel;

	x_limit = SIZE;
	y_limit = SIZE * tan(angle);
	vertical_x = floor(data->person->pers_x / SIZE) * SIZE;
	pixel = check_cross(angle, &vertical_x, &x_limit, 0);
	vertical_y = data->person->pers_y + (vertical_x - data->person->pers_x)
		* tan(angle);
	if ((angle_circle(angle, 'x') && y_limit < 0)
		|| (!angle_circle(angle, 'x') && y_limit > 0))
		y_limit *= -1;
	while (check_wall_hit(data, (vertical_x - pixel), vertical_y))
	{
		vertical_x += x_limit;
		vertical_y += y_limit;
	}
	data->ray->ver_x = vertical_x;
	data->ray->ver_y = vertical_y;
	return (sqrt(pow(vertical_x - data->person->pers_x, 2)
			+ pow(vertical_y - data->person->pers_y, 2)));
}

float	horizontal_cross(t_data *data, float angle)
{
	float	horizontal_x;
	float	horizontal_y;
	float	x_limit;
	float	y_limit;
	int		pixel;

	y_limit = SIZE;
	x_limit = SIZE / tan(angle);
	horizontal_y = floor(data->person->pers_y / SIZE) * SIZE;
	pixel = check_cross(angle, &horizontal_y, &y_limit, 1);
	horizontal_x = data->person->pers_x + (horizontal_y - data->person->pers_y)
		/ tan(angle);
	if ((angle_circle(angle, 'y') && x_limit > 0)
		|| (!angle_circle(angle, 'y') && x_limit < 0))
		x_limit *= -1;
	while (check_wall_hit(data, horizontal_x, (horizontal_y - pixel)))
	{
		horizontal_x += x_limit;
		horizontal_y += y_limit;
	}
	data->ray->hor_x = horizontal_x;
	data->ray->hor_y = horizontal_y;
	return (sqrt(pow(horizontal_x - data->person->pers_x, 2)
			+ pow(horizontal_y - data->person->pers_y, 2)));
}

void	raycasting(t_data *data)
{
	double	hor_cross;
	double	ver_cross;
	int		ray;

	ray = 0;
	data->ray->ang = data->person->ang - (data->person->vis_rd / 2);
	while (ray < WIDTH)
	{
		data->ray->flag = 0;
		hor_cross = horizontal_cross(data, check_angle(data->ray->ang));
		ver_cross = vertical_cross(data, check_angle(data->ray->ang));
		if (ver_cross <= hor_cross)
			data->ray->distan = ver_cross;
		else
		{
			data->ray->distan = hor_cross;
			data->ray->flag = 1;
		}
		render_walls(data, ray);
		ray++;
		data->ray->ang += (data->person->vis_rd / WIDTH);
	}
}
