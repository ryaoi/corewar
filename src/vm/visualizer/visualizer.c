/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/18 23:01:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	visualize_game(t_vm_state *vm)
{
	vis_state.delay = DELAY / vis_state.speed;
	werase(win.mem_dump);
	werase(win.info);
	create_memory_dump(vm);
	create_info(vm);
	//create_others(win);
	refresh();
	wrefresh(win.mem_dump);
	wrefresh(win.info);
}

void	get_color_pairs()
{
	init_color(COLOR_GREY, 350, 350, 350);
	init_color(COLOR_BRIGHT_WHITE, 1000, 1000, 1000);
	init_pair(1, COLOR_GREY, COLOR_GREY);
	init_pair(2, COLOR_BRIGHT_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREY, COLOR_BLACK);
	/* TODO
		needs 4 colors for Program Counter
		4 colors for champios memory_dump
		colors for the informational log
		fuckin many colors
	*/
}

void	control_speed(int input, t_visualizer_state *vis_state)
{
	if (input == KEY_UP)
		(*vis_state).speed += 10;
	if (input == KEY_DOWN)
		(*vis_state).speed -= 10;
	if (input == KEY_RIGHT)
		(*vis_state).speed += 2;
	if (input == KEY_LEFT)
		(*vis_state).speed -= 2;
	if ((*vis_state).speed > 1500)
		(*vis_state).speed = 1500;
	if ((*vis_state).speed < 1)
		(*vis_state).speed = 1;
}

int		get_keyinput(t_visualizer_state *vis_state)
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

void	init_visualizer(void)
{
	ft_bzero(&vis_state, sizeof(t_visualizer_state));
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	get_color_pairs();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	win.mem_dump = newwin(4 + (MEM_SIZE / 64), MEM_DUMP_WIDTH, 0, 0);
	win.info = newwin(4 + (MEM_SIZE / 64), INFO_WIDTH, 0, MEM_DUMP_WIDTH - 1);
	vis_state.speed = 1000;
	vis_state.pause = 1;
}

int		visualizer(t_game_data *game)
{
	int					key;

	if (game->state.cycle_count == 1)
		init_visualizer();
	//ft_bzero(&vis_state, sizeof(t_visualizer_state));
	//initscr();
	//cbreak();
	//noecho();
	//curs_set(0);
	//start_color();
	//get_color_pairs();
//	nodelay(stdscr, TRUE);
//	keypad(stdscr, TRUE); /* TODO hook keys to speed up & down the program */
							/* the whole thing needs to be linked to the corewar */
//	win.mem_dump = newwin(4 + (MEM_SIZE / 64), MEM_DUMP_WIDTH, 0, 0);
//	win.info = newwin(4 + (MEM_SIZE / 64), INFO_WIDTH, 0, MEM_DUMP_WIDTH - 1);
//	win.other = newwin(58, MEM_DUMP_WIDTH + INFO_WIDTH, 4 + (MEM_SIZE / 64) + 1, 0)
	while (vis_state.pause)
	{
		key = get_keyinput(&vis_state);
		visualize_game(&game->state);
		if (key == -1)
			return (-1);
		else if (key == 1)
			return (0);
	}
	visualize_game(&game->state);
	if (get_keyinput(&vis_state) == -1)
		return (-1);
	usleep(vis_state.delay);
	return (0);
}
