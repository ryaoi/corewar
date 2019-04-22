/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/22 22:54:38 by jaelee           ###   ########.fr       */
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
	init_color(FT_COLOR_GREY, 400, 400, 400);
	init_color(FT_COLOR_BRIGHT_WHITE, 1000, 1000, 1000);
	init_color(FT_COLOR_BLUE, 46 * COEFF, 134 * COEFF, 193 * COEFF);
	init_color(FT_COLOR_PURPLE, 142 * COEFF, 68 * COEFF, 173 * COEFF);
	init_color(FT_COLOR_GREEN, 39 * COEFF, 174 * COEFF, 96 * COEFF);
	init_color(FT_COLOR_BROWN, 211 * COEFF, 84 * COEFF, 0 * COEFF);

	init_color(FT_COLOR_LIGHT_BLUE, 133 * COEFF, 193 * COEFF, 233 * COEFF);
	init_color(FT_COLOR_LIGHT_PURPLE, 187 * COEFF, 143 * COEFF, 206 * COEFF);
	init_color(FT_COLOR_LIGHT_GREEN, 130 * COEFF, 224 * COEFF, 170 * COEFF);
	init_color(FT_COLOR_LIGHT_BROWN, 229 * COEFF, 152 * COEFF, 102 * COEFF);

//	init_color(CHAMP1_PC_COLOR);
//	init_color(CHAMP2_PC_COLOR);
//	init_color(CHAMP3_PC_COLOR);
//	init_color(CHAMP4_PC_COLOR);

	/* written memory */
	init_pair(1, FT_COLOR_GREY, FT_COLOR_GREY); //border
	init_pair(50, FT_COLOR_BRIGHT_WHITE, COLOR_BLACK); // info text

	init_pair(2, FT_COLOR_GREY, COLOR_BLACK); //empty memdup
	init_pair(3, FT_COLOR_BLUE, COLOR_BLACK);
	init_pair(4, FT_COLOR_PURPLE, COLOR_BLACK);
	init_pair(5, FT_COLOR_GREEN, COLOR_BLACK);
	init_pair(6, FT_COLOR_BROWN, COLOR_BLACK);

	/* most recent written memory */
	init_pair(12, FT_COLOR_GREY, FT_COLOR_GREY); // PC at empty memdump
	init_pair(13, FT_COLOR_LIGHT_BLUE, COLOR_BLACK);
	init_pair(14, FT_COLOR_LIGHT_PURPLE, COLOR_BLACK);
	init_pair(15, FT_COLOR_LIGHT_GREEN, COLOR_BLACK);
	init_pair(16, FT_COLOR_LIGHT_BROWN, COLOR_BLACK);

	/* program_counter position */
	init_pair(22, FT_COLOR_GREY, FT_COLOR_GREY);
	init_pair(23, COLOR_BLACK, FT_COLOR_BLUE);
	init_pair(24, COLOR_BLACK, FT_COLOR_PURPLE);
	init_pair(25, COLOR_BLACK, FT_COLOR_GREEN);
	init_pair(26, COLOR_BLACK, FT_COLOR_BROWN);

	/* program_counter position + HIGHLIGHT*/
	init_pair(32, FT_COLOR_GREY, FT_COLOR_GREY);
	init_pair(33, FT_COLOR_BRIGHT_WHITE, FT_COLOR_BLUE);
	init_pair(34, FT_COLOR_BRIGHT_WHITE, FT_COLOR_PURPLE);
	init_pair(35, FT_COLOR_BRIGHT_WHITE, FT_COLOR_GREEN);
	init_pair(36, FT_COLOR_BRIGHT_WHITE, FT_COLOR_BROWN);
}

////////////////////////////////pthread..../////////////////////////////////////
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
	if ((*vis_state).speed > 2000)
		(*vis_state).speed = 2000;
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
////////////////////////////////pthread..../////////////////////////////////////

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
