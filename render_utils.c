/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:23:18 by etornay-          #+#    #+#             */
/*   Updated: 2024/05/15 14:25:26 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_colors(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

int	reverse_bytes(int i)
{
	unsigned int	j;

	j = 0;
	j |= (i & 0xFF) << 24;
	j |= (i & 0xFF00) << 8;
	j |= (i & 0xFF0000) >> 8;
	j |= (i & 0xFF000000) >> 24;
	return (j);
}

void	create_pixels(t_data *data, int x, int y, int color)
{
	if (x < 0 || x > WIDTH)
		return ;
	if (y < 0 || y > HEIGHT)
		return ;
	mlx_put_pixel(data->img, x, y, color);
}
