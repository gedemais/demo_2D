#include "demo.h"

void	jump(t_mlx *env, bool pulse)
{
	static int	step = 0;

	if (pulse)
		step = 10;
	else if (step > 0)
	{
		if (env->player.y > 0)
		env->player.y -= env->player.yspeed * step;
		step--;
	}
}

void	blit_jump(t_mlx *env, bool left)
{
	static bool	down = false;
	static float	y = 0;

	down = env->player.y < y ? true : false;
	y = env->player.y;
	if (env->player.y <= FLOOR - 200 && env->player.y >= FLOOR - 250)
		blit_sprite(env, env->sprites[down ? 9 : 12], env->player.x, env->player.y, left);
	if (env->player.y <= FLOOR - 250)
		blit_sprite(env, env->sprites[down ? 10 : 11], env->player.x, env->player.y, left);

}

void	render_walk(t_mlx *env, int *step, bool left)
{
	static int	laps = 0;
	static int	lapses[NB_SPRITES] = {7, 7, 7, 7, 7, 7, 7, 7};

	blit_sprite(env, env->sprites[*step], env->player.x, env->player.y, left);
	if (*step == 8)
		*step = 1;
	if (laps == lapses[*step])
	{
		(*step)++;
		laps = 0;
	}
	laps++;
}

void	render_player(t_mlx *env)
{
	static int	step = 1;
	float		acc;
//	if (env->player.y < FLOOR)//pas collision avec le sol
//		env->player.y += env->player.gravity;
	jump(env, false);
	if (env->keys[RIGHT_KEY] || env->keys[LEFT_KEY])
		env->left = env->keys[LEFT_KEY] ? true : false;
	if (env->player.y < FLOOR - 200)
	{
		acc = env->gravity * (env->player.y / HGT);
		env->player.y += env->gravity + acc;
		blit_jump(env, env->left);
		return ;
	}
	else if (env->keys[RIGHT_KEY] || env->keys[LEFT_KEY])
		render_walk(env, &step, env->left);
	else
	{
		step = 1;
		blit_sprite(env, env->sprites[0], env->player.x, env->player.y, env->left);
	}
}
