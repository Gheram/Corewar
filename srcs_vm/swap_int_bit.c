/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_int_bit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:06:27 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:06:31 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

unsigned int		swap_int_bit(unsigned int n)
{
	unsigned int	ret;

	ret = 0;
	ret = n >> 24;
	ret += (n >> 8) & 0xff00;
	ret += (n << 8) & 0xff0000;
	ret += n << 24;
	return (ret);
}
