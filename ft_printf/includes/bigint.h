/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:45:15 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:17:38 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BIGINT_H
# define _BIGINT_H
# include <stdint.h>
# include "libft.h"

typedef uint32_t	t_unit;
typedef uint64_t	t_large;

# define UNIT_BITS (4 * 8)

typedef struct		s_bigint
{
	t_unit	*data;
	size_t	size;
}					t_bigint;

t_bigint			*bi_init(size_t size);
void				bi_destroy(t_bigint *num);
t_bigint			*bi_copy(t_bigint *num);
size_t				bi_cut(t_bigint *num);
size_t				bi_append(t_bigint *num, t_unit unit);
void				bi_unitshift_right(t_bigint *num, size_t units);
void				bi_bitshift_right(t_bigint *num, size_t bits);
void				bi_unitshift_left(t_bigint *num, size_t units);
void				bi_bitshift_left(t_bigint *num, size_t bits);
t_bigint			*bi_sum_small(const t_bigint *a, t_unit s);
t_bigint			*bi_sum(const t_bigint *a, const t_bigint *b,
						size_t max_len);
t_bigint			*bi_complement(const t_bigint *a, size_t size);
t_bigint			*bi_difference(const t_bigint *a, const t_bigint *b);
t_bigint			*bi_mul_small(const t_bigint *a, t_unit b);
t_bigint			*bi_div_small(const t_bigint *num, t_unit div,
						t_unit *mod_ret);

#endif
