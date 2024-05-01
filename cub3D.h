/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:04:58 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/01 17:51:52 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>

# define WNAME	1 //nombre del archivo invalido
# define WARG	2 //argumentos invalidos
# define NOFD	3 //archivo inexistente
# define OMAP	4 //error abriendo el mapa
# define EGNL	5 //error de get next line
# define EIMG	6 //error de  imagen
# define DCLRS	7 //Texturas o colores duplicados
# define ELINE	8 //error en line
# define ECLRS	9 //error en los colores
# define EWALL	10 //error en los muros
# define EVYH	11 //error horizontal y vertical
# define ESPC	12 //error de espacios
# define ELMNT	13 //error de elementos
# define ETEXT	14 //error de texturas

typedef struct s_player
{
	int		plyr_x;// player x position in pixels
	int		plyr_y;// player y position in pixels
	double	angle;// player angle
	float	fov_rd;// field of view in radians
	int		rot;// rotation flag
	int		l_r;// left right flag
	int		u_d;// up down flag
}	t_player;

typedef struct s_ray
{
	double	ray_angle;// ray angle
	double	distance;// distance to the wall
	int		flag;// flag for the wall
}	t_ray;

typedef struct s_data
{
	char			**map;// the map
	int				p_x;// player x position in the map
	int				p_y;// player y position in the map
	int				w_map;// map width
	int				h_map;// map height
	int				fd;
	int				e_counter; //Contador de los elementos del mapa, c_pos
	char			orientation; // Caracter de la orientacion del personaje
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
	mlx_image_t		*img; // the image
	mlx_t			*mlx;// the mlx pointer
	t_ray			*ray;// the ray structure
	t_player		*ply;// the player structure
}	t_data;

//check_map.c
int		check_map(t_data *d);
int		check_elements(t_data *data, char **text);
int		check_only_spaces_fl(t_data *d);
int		check_elements_map(t_data *d);
int		check_colors(t_data *d, char *tc, char *split_text);

//error.c
int		ft_error(int e);
int		ft_error2(int e);

//main.c
int		main(int argc, char **argv);
int		check_map_name(char *name);
void	ft_leaks(void);

//map.c
int		save_map(t_data *data);
int		fix_map(t_data *d);
int		read_map(t_data *data, char *map_fd);
int		save_textures(t_data *data, char *text);
int		save_textures_2(t_data *data, char **split_text, char **tc);

//utils.c
void	free_b_arr(char ***s);
void	free_data(t_data *d);
void	free_data2(t_data *d);

#endif