/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmilan <dmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:55:50 by dmilan            #+#    #+#             */
/*   Updated: 2020/12/19 17:34:00 by dmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include <mlx.h>
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define ESC 53
# define SPRITE_BG 0x00B59696

typedef struct		s_image
{
	void			*image;
	char			*address;
	int				bits_per_pixel;
	int				len;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct		s_texture
{
	t_image			north;
	t_image			east;
	t_image			south;
	t_image			west;
	t_image			sprite;
	t_color			floor;
	t_color			ceilling;
}					t_texture;

typedef struct		s_player
{
	t_point			pos;
	t_point			direction;
	t_point			plane;
	double			speed;
	double			turn_speed;
	bool			is_set;
}					t_player;

typedef struct		s_ray
{
	double			x;
	double			y;
	t_point			delta_v;
	t_point			delta_h;
	t_point			side_v;
	t_point			side_h;
	t_point			wall;
	int				wall_height;
	int				wall_start;
	int				wall_end;
	char			side;
	int				map_x;
	int				map_y;
}					t_ray;

typedef struct		s_content
{
	int				x;
	int				y;
	bool			is_shown;
	t_point			contact;
	t_point			transform;
	int				screen_x;
	int				height;
	int				start_y;
	int				end_y;
	int				width;
	int				start_x;
	int				end_x;
	int				tex_x;
	int				tex_y;
}					t_content;

typedef struct		s_vars
{
	void			*mlx;
	void			*window;
	char			**map;
	t_player		player;
	t_image			frame;
	t_point			resolution;
	int				y;
	int				*x;
	t_texture		texture;
	t_list			*sprites;
	double			*rays;
	char			*arg;
	bool			save;
}					t_vars;

typedef struct		s_elements
{
	int				resolution_is_set;
	int				north_is_set;
	int				south_is_set;
	int				west_is_set;
	int				east_is_set;
	int				sprite_is_set;
	int				floor_is_set;
	int				ceiling_is_set;
}					t_elements;

void				read_map(char *file, t_vars *vars);
int					map_validate(t_vars *vars);
void				handle_error(const char *error);
void				put_content(void *content);
void				draw_sprites(t_vars *vars);
void				draw_wall(t_ray *ray, t_vars *vars, int i);
void				check_for_sprite(t_ray *ray, t_vars *vars);
void				cast_ray(t_ray *ray, t_vars *vars);
void				render_frame_for_bmp(t_vars *vars);
void				create_bmp(t_image frame);
int					free_all(t_vars *vars);

/*
**  vector.c
*/
t_point				rotate_vector(t_point point, double angle);
double				vector_len(t_point point);

/*
**  draw.c
*/
void				put_pixel(t_image *image, int x, int y, int color);
unsigned int		get_pixel(t_image *image, int x, int y);
void				draw_line(t_image *image, t_point p1, t_point p2,
								int color);

/*
**  parce.c
*/
void				parce_resolution(t_vars *vars, const char *line);
void				new_texture(t_vars *vars, t_image *texture,
								const char *line);
int					parce_map_element(t_vars *vars, char *line);
int					is_map_element(char *line, t_elements *elements);
t_color				parce_color_line(const char *line);

/*
**  validate_map.c
*/
int					check_cub_extension(char *line);
void				check_elements(t_elements *elements);
void				default_elements(t_elements *elements);
void				check_line_for_player_position(t_vars *vars, char *line,
														int i);
void				check_line_for_sprites(t_vars *vars, char *line, int i);

/*
**  raycasting.c
*/
void				cast_rays(t_vars *vars);

/*
**  bindings.c
*/
int					free_all(t_vars *vars);
int					key_pressed(int keycode, t_vars *vars);

#endif
