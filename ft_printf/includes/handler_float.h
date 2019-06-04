/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_float.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 22:41:47 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/10 14:05:03 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HANDLER_FLOAT_H
# define _HANDLER_FLOAT_H

# include "bigint.h"
# include "ft_printf.h"

# define EMPTY 1
# define FULL 2

struct			s_float_flags
{
	char	sign;
	char	exponent;
	char	mantissa;
};

typedef struct	s_precise
{
	t_bigint				*mantissa;
	int32_t					exponent;
	int32_t					fractional;
	struct s_float_flags	flags;

}				t_precise;

int				float_80(long double num, t_precise *precise);
int				float_64(double num, t_precise *precise);
int				scale_to_int(t_precise *precise);
char			*print_float(const t_conv *conv, t_precise *precise);

#endif
