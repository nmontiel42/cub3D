/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:04:58 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/16 17:58:12 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# define W_NAME		1
# define W_ARG		2
# define N_OFD		3
# define O_MAP		4
# define E_GNL		5
# define E_IMG		6
# define D_CLRS		7
# define E_LINE		8
# define E_CLRS		9
# define E_WALL		10
# define E_VYH		11
# define E_SPC		12
# define E_ELMNT	13
# define E_TEXT		14
# define E_LIM		15
# define E_SPLIT	16
# define EM_CLR		17
# define N_MAP		18

# define WIDTH		2300
# define HEIGHT		1300
# define SIZE		30
# define VISION		70
# define SPEED		3
# define ROTATION	0.08

typedef struct s_person
{
	int		pers_x;
	int		pers_y;
	double	ang;
	float	vis_rd;
	int		rot;
	int		lf_rt;
	int		up_dw;
}	t_person;

typedef struct s_ray
{
	double	ang;
	double	distan;
	int		flag;
	double	ver_x;
	double	ver_y;
	double	hor_x;
	double	hor_y;
	int		index;
}	t_ray;

typedef struct s_data
{
	char			**map;
	int				p_x;
	int				p_y;
	int				w_map;
	int				h_map;
	int				fd;
	int				e_counter;
	char			orientation;
	char			*line;
	int				count_textures;
	int				i;
	int				j;
	int				k;
	char			c;
	char			**f_rgb;
	char			**c_rgb;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_image_t		*img;
	mlx_t			*mlx;
	t_ray			*ray;
	t_person		*person;
}	t_data;

//check_map.c
int				check_map(t_data *d);
int				check_elements(t_data *data, char **text);
int				check_only_spaces_fl(t_data *d);
int				check_elements_map(t_data *d);
int				check_colors(t_data *d, char *tc, char *split_text);

//error.c
int				ft_error(int e);
int				ft_error2(int e);

//main.c
int				main(int argc, char **argv);
int				check_map_name(char *name);
void			ft_leaks(void);
int				initialize_game(t_data *data);
void			ft_angle(t_data *data);
void			print_map(void *ks);
void			init_data(t_data *data);

//map.c
int				save_map(t_data *data);
int				fix_map(t_data *d);
int				read_map(t_data *data, char *map_fd);
int				save_textures(t_data *data, char *text);
int				save_textures_2(t_data *data, char **split_text, char **tc);
int				process_textures_and_colors(t_data *data, char **split_text,
					char **t_c);
void			check_textures(t_data *d, char **texture);

//camera.c
void			all_movement(t_data *data, double x, double y);
void			cam_rotation(t_data *data, int i);
void			movement(t_data *data, double x, double y);

//utils.c
void			free_array(char ***s);
void			free_data(t_data *d);
void			free_data2(t_data *d);

//keys.c
void			keys(mlx_key_data_t k, void *ks);
void			keys2(mlx_key_data_t k, void *ks);

//raycasting.c
void			raycasting(t_data *data);
float			horizontal_cross(t_data *data, float angle);
float			vertical_cross(t_data *data, float angle);
int				check_cross(float angle, float *cross, float *step_size, \
				int horizon);
int				angle_circle(float angle, char axis);
int				check_wall_hit(t_data *data, float x, float y);
float			check_angle(float angle);

//render.c
void			render_walls(t_data *data, int ray);
void			create_walls(t_data *data, double wall_h, int t_pix, int b_pix);
mlx_texture_t	*get_texture(t_data *data, int flag);
double			get_x_coor(t_data *data, mlx_texture_t *texture);
void			create_pixels(t_data *data, int x, int y, int color);
int				reverse_bytes(int i);
int				get_colors(int r, int g, int b, int a);

#endif