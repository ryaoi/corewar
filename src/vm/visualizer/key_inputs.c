/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:21:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/30 16:58:00 by aamadori         ###   ########.fr       */
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
		vis_state->input_info.speed += 2;
	if (input == KEY_LEFT)
		vis_state->input_info.speed -= 2;
	if (vis_state->input_info.speed > 2000)
		vis_state->input_info.speed = 2000;
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
	control_speed(input, vis_state);
	return (0);
}
