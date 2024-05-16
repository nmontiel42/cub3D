/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:31:04 by etornay-          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:52 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_wall_hit(t_data *data, float x, float y)
{
	int	x_size;
	int	y_size;

	if (x < 0 || y < 0)
		return (0);
	x_size = floor(x / SIZE);
	y_size = floor(y / SIZE);
	if (y_size >= data->h_map || x_size >= data->w_map)
		return (0);
	if (data->map[y_size] && x_size <= (int)ft_strlen(data->map[y_size]))
		if (data->map[y_size][x_size] == '1')
			return (0);
	return (1);
}

int	check_cross(float angle, float *cross, float *step_size, int horizon)
{
	if (horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*cross += SIZE;
			return (-1);
		}
		*step_size *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*cross += SIZE;
			return (-1);
		}
		*step_size *= -1;
	}
	return (1);
}

float	check_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	check_map_name(char *name)
{
	int	i;

	i = ft_strlen(name) - 1;
	if (name[i] != 'b' || name[i - 1] != 'u'
		|| name[i - 2] != 'c' || name[i - 3] != '.')
		return (false);
	return (true);
}
