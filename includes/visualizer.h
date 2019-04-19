/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:57:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/18 23:01:50 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

#include "ncurses.h"
#include <unistd.h>
#include "libft.h"
#include "vm.h"
#include "game.h"

# define DELAY 1000000
# define COLOR_GREY 20
# define COLOR_BRIGHT_WHITE 21
# define COLOR_BROWN_1 22
# define COLOR_PINK 23
# define COLOR_BLUE_L 24
# define COLOR_BROWN_BG 25
# define COLOR_PINK_BG 26
# define COLOR_GREEN_BG 27
# define COLOR_BLUE_BG 28
/* TODO more colors probably required */

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
}				t_window;

t_visualizer_state	vis_state;
t_window			win;

void	create_memory_dump(t_vm_state *vm);
void	create_info(t_vm_state *vm);
int		visualizer(t_game_data *game);
#endif
