/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:57:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/30 17:03:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

#include <unistd.h>
#include <pthread.h>
#include "ncurses.h"
#include "libft.h"
#include "vm.h"
#include "game.h"

# define DELAY 1000000
# define MEM_DUMP_WIDTH 197
# define INFO_WIDTH 58
# define PRESS_KEY_SPACE 32

# define COEFF 4
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

# define GREY_GREY 1
# define GREY_BLACK 2
# define WHITE_BLACK 50

# define BLUE_BLACK 3
# define PURPLE_BLACK 4
# define GREEN_BLACK 5
# define RED_BLACK 6

# define LBLUE_BLACK 13
# define LPURPLE_BLACK 14
# define LGREEN_BLACK 15
# define LRED_BLACK 16

# define GREY_GREY2 22
# define BLACK_BLUE 23
# define BLACK_PURPL 24
# define BLACK_GREEN 25
# define BLACK_RED 26

# define WHITE_BLUE 33
# define WHITE_PURPLE 34
# define WHITE_GREEN 35
# define WHITE_RED 36

# define HIGHLIGHT 10
# define PROGRAM_COUNTER_MARK 20

#include "cmd_line.h"

typedef struct	s_input_info
{
	int	quit;
	int pause;
	int speed;
}				t_input_info;

typedef struct	s_visualizer_state
{
	int				delay;
	int				process;
	pthread_t		input_worker;
	pthread_mutex_t	input_lock;
	t_input_info	input_info;
	int				game_over;
	int				shutdown;
}				t_visualizer_state;

typedef struct	s_window
{
	WINDOW	*mem_dump;
	WINDOW	*info;
}				t_window;

// typedef struct s_visualizer
// {
// 	t_visualizer_state	vis_state;
// 	t_window			win;
// }				t_visualizer;

t_visualizer_state	vis_state;
t_window			win;

void	get_colors(void);
int		get_keyinput(t_visualizer_state *vis_state);
void	create_memory_dump(t_vm_state *vm);
void	create_info(t_vm_state *vm, t_game_data *game,
			t_input_info *input_info);
void	create_logging(t_vm_state *vm, t_game_data *game);
int		visualizer(t_game_data *game, t_corewar_input *cw_input,
			t_input_info *info_copy);



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
