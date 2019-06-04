/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:50:46 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/04 12:26:25 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_ASSERT_H
# define _FT_ASSERT_H

void	ft_assert(char cond, const char *message);
void	ft_malloc_assert(void *ptr);

#endif
