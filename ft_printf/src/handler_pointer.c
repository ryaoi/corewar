/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:53:25 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 12:26:47 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdarg.h>

t_string	*h_pointer(const t_conv *conv, va_list *ap)
{
	t_conv	pointer_conv;

	ft_memcpy(&pointer_conv, conv, sizeof(t_conv));
	pointer_conv.flags.alt_form = ALTERNATE_FORCE;
	if (pointer_conv.length_modifier == l_default)
		pointer_conv.length_modifier = l_ptr;
	return (h_u_hex(&pointer_conv, ap));
}
