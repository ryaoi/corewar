/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_backup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/23 11:11:07 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"
#include "ft_printf.h"
#include "visualizer.h"

void	close_ncurse(t_window *win)
{
	nodelay(stdscr, FALSE);
	wattron((*win).info, COLOR_PAIR(2));
	mvwprintw((*win).info, 10, 3, "GET THE FUCK OUT WITH ANY KEY!!");
	wrefresh((*win).info);
	getch();
	delwin((*win).mem_dump);
	delwin((*win).info);
	endwin();
}

int		main(void)
{
	t_game_data	*game;
	t_array		players;
	t_player	sha1;
	t_player	sha2;
	t_player	sha3;
	t_player	sha4;
	t_log_info	info;

	if (vm_champion_load_file(&sha1, "/Users/jaelee/42/corewar/champs/Gagnant.cor", -1) < 0
		|| vm_champion_load_file(&sha2, "/Users/jaelee/42/corewar/champs/Octobre_Rouge_V4.2.cor", -2) < 0
		|| vm_champion_load_file(&sha3, "/Users/jaelee/42/corewar/death.cor", -3) < 0
		|| vm_champion_load_file(&sha4, "/Users/jaelee/42/corewar/champs/fluttershy.cor", -4) < 0)
		return (0);
	array_init(&players, sizeof(t_player));
	array_push_back(&players, &sha1);
	array_push_back(&players, &sha2);
	array_push_back(&players, &sha3);
	array_push_back(&players, &sha4);
	logs_init(&info);
	info.log_mode = e_mode_stderr;
	ft_memcpy(&info.log_active,
		(uint8_t[e_log_level_max]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		sizeof(info.log_active));
	game = malloc(sizeof(t_game_data));
	prepare_game(game, &players, &info);
	while (game->state.cycle_count < 80000)
	{
		advance_cycle(game);
	//	dump_memory(&game->state);
		if (visualizer(game) == -1)
			break ;
	}
	close_ncurse(&win);
//	ft_printf("%d %d\n", ARRAY_PTR(game->state.players, t_player)[0].live, ARRAY_PTR(game->state.players, t_player)[1].live);
	return (0);
}

////////////////////////////////////////////////////////////////////////////////
/*
typedef struct		s_corewar_input
{
	char	*champions[4];
	int		flags;
}

PARSE_FLAG_MEMDUMP		0b1
PARSE_FLAG_CHAMP_NBR	0b10
PARSE_FLAG_VISUALIZER	0b100
PARSE_NBR_CYCLES		0b1000
PARSE_CHAMP_NBR			0b10000
PARSE_CHAMP_NAME		0b100000

int		(*g_syntax_check[6])(char*) = {
	flag_memdump,
	parse_memdump_nbr,
	flag_visualizer,
	flag_champ_nbr,
	parse_champ_nbr,
	parse_champ_name
};

void	print_usage(void)
{
	ft_printf("Usage : $> ./corewar [-dump N | -v] [-n N champion1.cor] ...\n");
	ft_printf("-dump N : dumps memory after N cycles\n");
	ft_printf("-v : turn on visualizer\n");
	ft_printf("-n N champion.cor : player N and name_of_champion.cor\n");
}

int		check_syntax(int argc, char *input, int flag)
{
	int	index;
	int	ret;

	index = 0;
	while (index < 6)
	{
		if (flag >> index & 1 && g_syntax_check[index](input))
			ret = parse_input(input);
		return (ret);
	}

}

int		main(int argc, char **argv)
{
	int		flags;
	int		index;
	int		ret;

	flag = PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER
			| PARSE_FLAG_CHAMP_NBR | PARSE_CHAMPS_INPUT;
	index = 0;
	if (argc < 2)
		print_usage();
	else
	{
		while (index < argc)
		{
			ret = check_syntax(argc, argv[index], flag);
			flag = choose_flags(ret);
		}
	}
}

int		flag_memdump(char *str);
int		parse_memdump_nbr(char *str);
int		flag_visualizer(char *str);
int		flag_champ_nbr(char *str);
int		parse_champ_nbr(char *str);
int		parse_champ_name(char *str);
*/
