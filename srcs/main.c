/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:43:03 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/11 16:16:11 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demo.h"

static inline void	init_player(t_mlx *env)
{
	env->player.x = WDT / 2;
	env->player.y = HGT / 2;
	env->player.xspeed = 8.0f;
	env->player.yspeed = 2.0f;
	env->gravity = 5.0f;
}

static inline int		ft_set_env(t_mlx *env)
{
	if (!(env->mlx_ptr = mlx_init())
		|| !(env->mlx_win = mlx_new_window(env->mlx_ptr, WDT, HGT, "Wolf3D")))
		return (-1);
	if (!(env->img_ptr = mlx_new_image(env->mlx_ptr, WDT, HGT))
		|| !(env->img_data = mlx_get_data_addr(env->img_ptr, &env->bpp, 
		&env->s_l, &env->endian)))
		return (-1);
	if (load_sprites(env) != 0)
		return (-1);
	ft_memset(&env->keys[0], false, sizeof(bool) * NB_KEYS);
	init_player(env);
	return (0);
}

static inline void	set_hooks(t_mlx *env)
{
	mlx_hook(env->mlx_win, KEY_PRESS, KEY_PRESS_MASK, press_key, env);
	mlx_hook(env->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, release_key, env);
	mlx_loop_hook(env->mlx_ptr, base, env);
	mlx_hook(env->mlx_win, 17, (1L << 17), ft_exit, env);
}

static inline int	demo(void)
{
	t_mlx	env;

	ft_memset(&env, 0, sizeof(t_mlx));
	if (ft_set_env(&env) == -1)
		return (-1);
	mlx_put_image_to_window(&env, env.mlx_win, env.img_ptr, 0, 0);

	set_hooks(&env);
	mlx_loop(env.mlx_ptr);
	return (0);
}

int		main(void)
{
	demo();
	return (0);
}
