/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:50:23 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/11 16:02:34 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define HGT 600
# define WDT 1080

# define NB_SPRITES 13

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

# define NB_KEYS 260

# define ESC_KEY 53
# define SPACE_KEY 49
# define SHIFT_KEY 257
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_M 46
# define KEY_N 45

# define PI 3.14159f
# define FLOOR 500
# define JUMP 10

# include "../libft/libft.h"
# include "mlx.h"
# include <stdbool.h>
# include <assert.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

# define MAX_BALLS 32
# define MPA ((t_mlx*)(param))
# define IMG img_ptr
# define IMGD img_data

enum					e_bloc_type
{
					BLOC_VOID,
					BLOC_FULL,
};

typedef union	u_isr
{
	float		f;
	uint32_t	i;
}				t_isr;

typedef struct	s_draw
{
	int		dx;
	int		dy;
	int		j;
	int		xinc;
	int		yinc;
	int		cumul;
	int		x;
	int		y;
}				t_draw;

typedef struct			s_sprite
{
	void			*frame;
	void			*ptr;
	int			height;
	int			width;
	int			alpha;
}				t_sprite;

typedef struct			s_bloc
{
	char				type;
}						t_bloc;

typedef struct			s_ball
{
	float		x;
	float		y;
	float		radius;
	float		speed;
}				t_ball;

typedef struct			s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct				s_player
{
	float				x;
	float				y;
	float				xspeed;
	float				yspeed;
}					t_player;

typedef struct				s_mlx
{
	void				*mlx_ptr;
	void				*mlx_win;
	void				*img_ptr;
	char				*img_data;
	t_ball				balls[MAX_BALLS];
	t_sprite			*sprites;
	t_player			player;
	float				gravity;
	bool				keys[NB_KEYS];
	bool				jump;
	bool				left;
	int				j_step;
	unsigned int			map_hgt;
	unsigned int			map_wdt;
	char				weapon;
	int				bpp;
	int				s_l;
	int				endian;
}						t_mlx;

int					load_sprites(t_mlx *env);
void					ft_fill_pixel(char *img_str, int x, int y, int color);
char					*ft_clear_image(void *param, char *img_data);
int					ft_exit(int status);

int					press_key(int key, void *param);
int					release_key(int key, void *param);
int					pos(int x, int y, void *param);
int					base(void *param);
void					render_player(t_mlx *env);
void					jump(t_mlx *env, bool pulse);
void					shoot(t_mlx *env);

void					ft_draw_line(void *param, int s[2], int e[2]);
void					draw_circle(t_mlx *env, float x, float y, float radius, int color);
void					blit_sprite(t_mlx *env, t_sprite sp, int x, int y, bool rev);
bool					*blit_alpha(void);

#endif
