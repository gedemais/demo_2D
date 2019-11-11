#include "demo.h"

void	handle_keys(t_mlx *env)
{
	if (env->keys[LEFT_KEY] && env->player.x >= 10)
		env->player.x -= env->player.xspeed;
	 if (env->keys[RIGHT_KEY] && env->player.x <= WDT - 300)
		env->player.x += env->player.xspeed;
	 if (env->keys[UP_KEY])
		jump(env, true);
}

int		base(void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);

	handle_keys(env);
	for (int i = 0; i < HGT; i++)
	{
		for (int j = 0; j < WDT; j++)
			ft_fill_pixel(env->img_data, j, i, 0xffffff);
	}
	render_player(env);
	shoot(env);
	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
	return (0);
}

int		release_key(int key, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	env->keys[key] = false;
	return (0);
}

int		press_key(int key, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	if (key == ESC_KEY)
		exit(EXIT_SUCCESS);
	else
		env->keys[key] = true;
	return (0);
}
