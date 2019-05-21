/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:21:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/21 16:57:23 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	control_speed(int input)
{
	if (input == KEY_UP)
		g_vis_state.input_info.speed += 10;
	if (input == KEY_DOWN)
		g_vis_state.input_info.speed -= 10;
	if (input == KEY_RIGHT)
		g_vis_state.input_info.speed += 1;
	if (input == KEY_LEFT)
		g_vis_state.input_info.speed -= 1;
	if (g_vis_state.input_info.speed > 1200)
		g_vis_state.input_info.speed = 1200;
	if (g_vis_state.input_info.speed < 1)
		g_vis_state.input_info.speed = 1;
}

static int	get_keyinput(void)
{
	int		input;

	input = getch();
	if (input == PRESS_KEY_SPACE)
	{
		if (g_vis_state.input_info.pause == 0)
			g_vis_state.input_info.pause = 1;
		else if (g_vis_state.input_info.pause == 1)
			g_vis_state.input_info.pause = 0;
	}
	if (input == 'q' || input == 'Q')
		g_vis_state.input_info.quit = 1;
	if (input == KEY_RESIZE)
		g_vis_state.input_info.resize = 1;
	control_speed(input);
	return (0);
}

void		*input_loop(void *stub)
{
	int key;

	(void)stub;
	while (!g_vis_state.shutdown)
	{
		pthread_mutex_lock(&g_vis_state.input_lock);
		key = 1;
		while (key)
			key = get_keyinput();
		pthread_mutex_unlock(&g_vis_state.input_lock);
		usleep(10000);
	}
	return (NULL);
}
