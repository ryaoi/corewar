/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:57:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/25 16:52:28 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

#include "ncurses.h"
#include <unistd.h>
#include "libft.h"
#include "vm.h"
#include "game.h"

#define MAX_NBR_CYCLE 50000

# define DELAY 1000000
# define HIGHLIGHT_CYCLE 20
# define FT_COLOR_GREY 20
# define FT_COLOR_BRIGHT_WHITE 21
# define FT_COLOR_BLUE 22
# define FT_COLOR_PURPLE 23
# define FT_COLOR_GREEN 24
# define FT_COLOR_RED 25

# define FT_COLOR_LIGHT_BLUE 26
# define FT_COLOR_LIGHT_PURPLE 27
# define FT_COLOR_LIGHT_GREEN 28
# define FT_COLOR_LIGHT_RED 29
# define COEFF 4

# define MEM_DUMP_WIDTH 197
# define INFO_WIDTH 58

# define PRESS_KEY_SPACE 32 /* TODO pause and resume */

typedef struct	s_visualizer_state
{
	int		pause;
	int		delay;
	int		speed;
	int		process;
}				t_visualizer_state;

typedef struct	s_window
{
	WINDOW	*mem_dump;
	WINDOW	*info;
	WINDOW	*logging;
}				t_window;

// typedef struct s_visualizer
// {
// 	t_visualizer_state	vis_state;
// 	t_window			win;
// }				t_visualizer;

t_visualizer_state	vis_state;
t_window			win;


void	create_memory_dump(t_vm_state *vm);
void	create_info(t_vm_state *vm, t_game_data *game);
void	create_logging(t_vm_state *vm, t_game_data *game);
int		visualizer(t_game_data *game);




/*parsing input */

// int		parse_cmd(int argc, char **argv, t_corewar_input *cw_input);

// int		is_flag_memdump(char *str, t_corewar_input *cw_input);
// int		is_cycles(char *str, t_corewar_input *cw_input);
// int		is_flag_visualizer(char *str, t_corewar_input *cw_input);
// int		is_flag_champ_nbr(char *str, t_corewar_input *cw_input);
// int		is_champ_nbr(char *str, t_corewar_input *cw_input);
// int		is_champ_name(char *str, t_corewar_input *cw_input);

// void	init_corewar_input(t_corewar_input *cw_input);
// int		check_syntax(char *input, int flags, t_corewar_input *cw_input);
// int		parse_input(char *input, size_t index, t_corewar_input *cw_input);
// void	print_usage(void);

// int		choose_flags(int prev_input);
// void	turn_on_flags(int *bit_field, int on_flags);

// int		get_champ_name(char *input, size_t index, t_corewar_input *cw_input);
// int		get_champ_nbr(char *input, size_t index, t_corewar_input *cw_input);

#endif
