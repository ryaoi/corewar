/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:45:25 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 18:48:55 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 21:49:32 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"
#include "ft_printf.h"

int		main(void)
{
	t_player	sha1;

	vm_champion_load_file(&sha1, "somegibberishabffjsdf.cor", 1);
	vm_champion_load_file(&sha1, "resources/invalid_champ_magic.cor", 2);
	vm_champion_load_file(&sha1, "resources/invalid_champ_large.cor", 3);
	vm_champion_load_file(&sha1, "resources/invalid_champ_eof.cor", 4);
	return (0);
}
