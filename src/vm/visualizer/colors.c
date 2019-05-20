/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:19:00 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/07 16:05:43 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	get_color_pairs(void)
{
	init_pair(GREY_GREY, FT_COLOR_GREY, FT_COLOR_GREY);
	init_pair(GREY_BLACK, FT_COLOR_GREY, COLOR_BLACK);
	init_pair(BLUE_BLACK, FT_COLOR_BLUE, COLOR_BLACK);
	init_pair(PURPLE_BLACK, FT_COLOR_PURPLE, COLOR_BLACK);
	init_pair(GREEN_BLACK, FT_COLOR_GREEN, COLOR_BLACK);
	init_pair(RED_BLACK, FT_COLOR_RED, COLOR_BLACK);
	init_pair(LBLUE_BLACK, FT_COLOR_LIGHT_BLUE, COLOR_BLACK);
	init_pair(LPURPLE_BLACK, FT_COLOR_LIGHT_PURPLE, COLOR_BLACK);
	init_pair(LGREEN_BLACK, FT_COLOR_LIGHT_GREEN, COLOR_BLACK);
	init_pair(LRED_BLACK, FT_COLOR_LIGHT_RED, COLOR_BLACK);
	init_pair(GREY_GREY2, FT_COLOR_GREY, FT_COLOR_GREY);
	init_pair(BLACK_BLUE, COLOR_BLACK, FT_COLOR_BLUE);
	init_pair(BLACK_PURPL, COLOR_BLACK, FT_COLOR_PURPLE);
	init_pair(BLACK_GREEN, COLOR_BLACK, FT_COLOR_GREEN);
	init_pair(BLACK_RED, COLOR_BLACK, FT_COLOR_RED);
	init_pair(WHITE_BLUE, FT_COLOR_BRIGHT_WHITE, FT_COLOR_BLUE);
	init_pair(WHITE_PURPLE, FT_COLOR_BRIGHT_WHITE, FT_COLOR_PURPLE);
	init_pair(WHITE_GREEN, FT_COLOR_BRIGHT_WHITE, FT_COLOR_GREEN);
	init_pair(WHITE_RED, FT_COLOR_BRIGHT_WHITE, FT_COLOR_RED);
	init_pair(WHITE_BLACK, FT_COLOR_BRIGHT_WHITE, COLOR_BLACK);
}

void		get_colors(void)
{
	init_color(FT_COLOR_GREY, 400, 400, 400);
	init_color(FT_COLOR_BRIGHT_WHITE, 1000, 1000, 1000);
	init_color(FT_COLOR_BLUE, 46 * COEFF, 134 * COEFF, 193 * COEFF);
	init_color(FT_COLOR_PURPLE, 142 * COEFF, 68 * COEFF, 173 * COEFF);
	init_color(FT_COLOR_GREEN, 39 * COEFF, 174 * COEFF, 96 * COEFF);
	init_color(FT_COLOR_RED, 192 * COEFF, 57 * COEFF, 43 * COEFF);
	init_color(FT_COLOR_LIGHT_BLUE, 133 * COEFF, 193 * COEFF, 233 * COEFF);
	init_color(FT_COLOR_LIGHT_PURPLE, 187 * COEFF, 143 * COEFF, 206 * COEFF);
	init_color(FT_COLOR_LIGHT_GREEN, 130 * COEFF, 224 * COEFF, 170 * COEFF);
	init_color(FT_COLOR_LIGHT_RED, 245 * COEFF, 183 * COEFF, 177 * COEFF);
	get_color_pairs();
}
