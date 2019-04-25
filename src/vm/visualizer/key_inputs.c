/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:21:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/25 18:21:47 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	control_speed(int input, t_visualizer_state *vis_state)
{
	if (input == KEY_UP)
		(*vis_state).speed += 10;
	if (input == KEY_DOWN)
		(*vis_state).speed -= 10;
	if (input == KEY_RIGHT)
		(*vis_state).speed += 2;
	if (input == KEY_LEFT)
		(*vis_state).speed -= 2;
	if ((*vis_state).speed > 2000)
		(*vis_state).speed = 2000;
	if ((*vis_state).speed < 1)
		(*vis_state).speed = 1;
}

int			get_keyinput(t_visualizer_state *vis_state)
{
	int		input;

	input = getch();

	if (input == PRESS_KEY_SPACE)
	{
		if ((*vis_state).pause == 0)
			(*vis_state).pause = 1;
		else if ((*vis_state).pause == 1)
			(*vis_state).pause = 0;
	}
	if (input == 'q' || input == 'Q')
		return (-1);
	if (input == 's' || input == 'S')
		return (1);
	control_speed(input, vis_state);
	return (0);
}
