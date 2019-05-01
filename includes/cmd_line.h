/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:50:01 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/01 20:49:22 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LINE_H
# define CMD_LINE_H

# include "libft.h"
# include "ft_printf.h"
# include "vm.h"
# include "logging.h"

#define FT_SUCCESS 1
#define FT_FAIL 0

#define FLAG_MEMDUMP 0b1
#define FLAG_VISUALIZER	0b100
#define FLAG_VERBOSITY 0b1000

#define PARSE_FLAG_MEMDUMP		0b1
#define PARSE_FLAG_VISUALIZER	0b10
#define PARSE_FLAG_CHAMP_NBR	0b100
#define PARSE_NBR_CYCLES		0b1000
#define PARSE_CHAMP_NBR			0b10000
#define PARSE_CHAMP_NAME		0b100000
#define PARSE_FLAG_VERBOSITY	0b1000000
#define PARSE_VERBOSITY			0b10000000

#define CHAMP_1		0b1
#define CHAMP_2		0b10
#define CHAMP_3		0b100
#define CHAMP_4		0b1000

#define EXTENSION_LENGTH 4
#define MAX_CHAMP_NBR 4
#define MAX_PROG_NAME_LENGTH_WITH_PATH 2047

#define INVALID_SYNTAX -1
#define INVALID_CYCLE_NBR -2
#define INVALID_CHAMP_NBR -3
#define INVALID_CHAMP_NAMES_LENGTH -4
#define INVALID_CHAMP_NAME -5
#define DUPLICATE_SYMBOLS -6
#define DUPLICATE_CHAMP_NBR -7
#define MALLOC_FAIL -8
#define TOO_MANY_PLAYERS -9

typedef struct		s_corewar_input
{
	char	*champions[MAX_CHAMP_NBR];
	int		nbr_of_champions;
	size_t	nbr_of_cycles;
	int		exec_flags;
	int		champ_flags;
	uint8_t	log_verbosity[e_log_level_max];
	int		incoming_champion;
}					t_corewar_input;

int		parse_cmd(int argc, char **argv, t_corewar_input *cw_input);

int		is_flag_memdump(char *str, t_corewar_input *cw_input);
int		is_cycles(char *str, t_corewar_input *cw_input);
int		is_flag_visualizer(char *str, t_corewar_input *cw_input);
int		is_flag_champ_nbr(char *str, t_corewar_input *cw_input);
int		is_champ_nbr(char *str, t_corewar_input *cw_input);
int		is_champ_name(char *str, t_corewar_input *cw_input);
int		is_flag_verbosity(char *str, t_corewar_input *cw_input);
int		is_verbosity(char *str, t_corewar_input *cw_input);

void	init_corewar_input(t_corewar_input *cw_input);
int		check_syntax(char *input, int flags, t_corewar_input *cw_input);
int		parse_input(char *input, int index, t_corewar_input *cw_input);
void	print_usage(void);
int		choose_flags(int prev_input);
void	turn_on_flags(int *bit_field, int on_flags);
int		get_champ_name(char *input, int index, t_corewar_input *cw_input);
int		get_champ_nbr(char *input, int index, t_corewar_input *cw_input);
int		get_log_verbosity(char *input, int index, t_corewar_input *cw_input);
size_t	ft_a_to_sizet(const char *str);

void	print_usage(void);
#endif
