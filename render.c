/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:33 by etornay-          #+#    #+#             */
/*   Updated: 2024/05/15 14:25:35 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	create_floor_ceiling(t_data *data, int ray, int top_pix, int bot_pix)
{
	int	i;
	int	j;

	i = bot_pix;
	j = get_colors(ft_atoi(data->f_rgb[0]), ft_atoi(data->f_rgb[1]), \
	ft_atoi(data->f_rgb[2]), 255);
	while (i < HEIGHT)
		create_pixels(data, ray, i++, j);
	j = get_colors(ft_atoi(data->c_rgb[0]), ft_atoi(data->c_rgb[1]), \
	ft_atoi(data->c_rgb[2]), 255);
	i = 0;
	while (i < top_pix)
		create_pixels(data, ray, i++, j);
}

double	get_x_coor(t_data *data, mlx_texture_t *texture)
{
	double	x_coor;

	if (data->ray->flag == 1)
		x_coor = (int)fmodf((data->ray->hor_x
					* (texture->width / SIZE)), texture->width);
	else
		x_coor = (int)fmodf((data->ray->ver_y
					* (texture->width / SIZE)), texture->width);
	return (x_coor);
}

mlx_texture_t	*get_texture(t_data *data, int flag)
{
	data->ray->ang = check_angle(data->ray->ang);
	if (flag == 1)
	{
		if (data->ray->ang > M_PI || data->ray->ang < 0)
			return (data->no);
		else
			return (data->so);
	}
	else
	{
		if (data->ray->ang > (M_PI / 2) && data->ray->ang < ((3 * M_PI) / 2))
			return (data->ea);
		else
			return (data->we);
	}
}

void	create_walls(t_data *data, double wall_h, int t_pix, int b_pix)
{
	double			x_coor;
	double			y_coor;
	double			height_factor;
	uint32_t		*pixel_array;
	mlx_texture_t	*texture;

	texture = get_texture(data, data->ray->flag);
	pixel_array = (uint32_t *)texture->pixels;
	height_factor = ((double)texture->height / wall_h);
	x_coor = get_x_coor(data, texture);
	y_coor = (t_pix - (HEIGHT / 2) + (wall_h / 2)) * height_factor;
	if (y_coor < 0)
		y_coor = 0;
	while (t_pix < b_pix)
	{
		create_pixels(data, data->ray->index, t_pix, reverse_bytes \
		(pixel_array[(int)y_coor * texture->width + (int)x_coor]));
		y_coor += height_factor;
		t_pix++;
	}
}

void	render_walls(t_data *data, int ray)
{
	double	wall_height;
	double	top_pixel;
	double	bottom_pixel;

	data->ray->distan *= cos(check_angle(data->ray->ang - data->person->ang));
	wall_height = (SIZE / data->ray->distan) \
	* (WIDTH / 2) / tan(data->person->vis_rd / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	data->ray->index = ray;
	create_walls(data, wall_height, top_pixel, bottom_pixel);
	create_floor_ceiling(data, ray, top_pixel, bottom_pixel);
}
