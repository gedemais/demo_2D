#include "demo.h"

bool	*blit_alpha(void)
{
	static bool		val = false;

	return (&val);
}

bool	do_copy(int color, char alph[4])
{
	int			diff;
	char		col[4];

	ft_memcpy(&col, &color, sizeof(int));
	diff = 0;
	diff += ft_abs(col[1] - alph[1]);
	diff += ft_abs(col[2] - alph[2]);
	diff += ft_abs(col[3] - alph[3]);

	if (diff < 100)
		return (false);
	return (true);
}

void	alpha_filter(t_sprite *sp)
{
	int				x;
	int				y;
	int				color;
	int				pos;
	char			alph[4];

	y = 0;
	ft_memcpy(&alph[0], &sp->alpha, sizeof(int));
	while (y < sp->height)
	{
		x = 0;
		while (x < sp->width)
		{
			pos = (abs(y - 1) * 288 + x) * sizeof(int);
			color = *(int*)&sp->frame[pos];
			if (!do_copy(color, alph))
				ft_memset(&sp->frame[pos], 0, sizeof(int));
			x++;
		}
		y++;
	}
}

void	blit_sprite(t_mlx *env, t_sprite sp, int x, int y, bool rev)
{
	int		i;
	int		j;
	int		k;
	int		pos;
	int		s_l;
	char	alph[4];

	i = 0;
	ft_memcpy(&alph[0], &sp.alpha, sizeof(int));
	s_l = sp.width * 4;
	while (i < sp.height)
	{
		k = rev ? s_l - 4 : 0;
		j = 0;
		pos = (abs(y + i - 1) * WDT + x) * sizeof(int);
		while (j < s_l)
		{
			ft_memcpy(&env->img_data[pos + k], &sp.frame[i * sp.width * 4 + j], sizeof(int));
			j += 4;
			k += rev ? -4 : 4;
		}
		i++;
	}
}

char	*sp_names(int which)
{
	static char	*filenames[NB_SPRITES] = {"sprites/0.xpm",
						"sprites/1.xpm",
						"sprites/2.xpm",
						"sprites/3.xpm",
						"sprites/4.xpm",
						"sprites/5.xpm",
						"sprites/6.xpm",
						"sprites/7.xpm",
						"sprites/8.xpm",
						"sprites/jump_1.xpm",
						"sprites/jump_2.xpm",
						"sprites/jump_3.xpm",
						"sprites/jump_4.xpm"};
	return (filenames[which]);
}

int		load_sprites(t_mlx *env)
{
	unsigned int	i;
	int				t;

	i = 0;
	if (!(env->sprites = (t_sprite*)malloc(sizeof(t_sprite) * NB_SPRITES)))
		return (-1);
	while (i < NB_SPRITES)
	{
		printf("Loading sprite %d -> %s...\n", i, sp_names(i));
		if (!(env->sprites[i].ptr = mlx_xpm_file_to_image(env->img_ptr,
			sp_names(i), &env->sprites[i].width, &env->sprites[i].height)))
			return (-1);
		if (!(env->sprites[i].frame = mlx_get_data_addr(env->sprites[i].ptr, &env->sprites[i].width, &env->sprites[i].height, &t)))
			return (-1);
	//	env->sprites[i].alpha = 9961608;
		env->sprites[i].width *= 9;
		env->sprites[i].height /= 4;
		i++;
	}
	return (0);
}
