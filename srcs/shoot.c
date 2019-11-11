#include "demo.h"

void	render_balls(t_mlx *env, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		draw_circle(env, env->balls[i].x, env->balls[i].y, env->balls[i].radius, 0x00ff00);
		env->balls[i].x += env->left ? -env->balls[i].speed : env->balls[i].speed;
		i++;
	}
}

void	shoot(t_mlx *env)
{
	static int	laps = 0;
	static int	nb_balls = 0;

	if (laps == 10)
	{
		laps = 0;
		if (env->keys[SPACE_KEY])
		{
			env->balls[nb_balls].x = env->player.x;
			env->balls[nb_balls].y = env->player.y;
			env->balls[nb_balls].radius = 0.5;
			env->balls[nb_balls].speed = 2;
			nb_balls++;
		}
			
	}
	laps++;
	render_balls(env, nb_balls);
}
