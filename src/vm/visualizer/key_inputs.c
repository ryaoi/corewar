/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:21:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/07 19:33:49 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	control_speed(int input, t_visualizer_state *vis_state)
{
	if (input == KEY_UP)
		vis_state->input_info.speed += 10;
	if (input == KEY_DOWN)
		vis_state->input_info.speed -= 10;
	if (input == KEY_RIGHT)
		vis_state->input_info.speed += 1;
	if (input == KEY_LEFT)
		vis_state->input_info.speed -= 1;
	if (vis_state->input_info.speed > 1200)
		vis_state->input_info.speed = 1200;
	if (vis_state->input_info.speed < 1)
		vis_state->input_info.speed = 1;
}

int			get_keyinput(t_visualizer_state *vis_state)
{
	int		input;

	input = getch();
	if (input == PRESS_KEY_SPACE)
	{
		if (vis_state->input_info.pause == 0)
			vis_state->input_info.pause = 1;
		else if (vis_state->input_info.pause == 1)
			vis_state->input_info.pause = 0;
	}
	if (input == 'q' || input == 'Q')
		vis_state->input_info.quit = 1;
	if (input == KEY_RESIZE)
		vis_state->input_info.resize = 1;
	control_speed(input, vis_state);
	return (0);
}

void	*input_loop(void *stub)
{
	int key;

	(void)stub;
	while (!vis_state.shutdown)
	{
		pthread_mutex_lock(&vis_state.input_lock);
		key = 1;
		while (key)
			key = get_keyinput(&vis_state);
		pthread_mutex_unlock(&vis_state.input_lock);
		usleep(10000);
	}
	return (NULL);
}
