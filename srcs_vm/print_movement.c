/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:06:08 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:06:10 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		print_zero(int value)
{
	int		i;

	i = 0;
	while ((value /= 16) > 0)
		++i;
	value = 3 - i;
	while (value--)
		ft_putchar('0');
}

void			print_movement(int origin, int dest, t_storage *storage)
{
	ft_putstr("ADV ");
	if (dest < origin)
		dest += MEM_SIZE;
	ft_putnbr(dest - origin);
	ft_putstr(" (0x");
	print_zero(origin);
	ft_putnbr_base(origin, "0123456789abcdef", 1);
	ft_putstr(" -> 0x");
	print_zero(dest);
	ft_putnbr_base(dest, "0123456789abcdef", 1);
	ft_putchar(')');
	dest = dest % MEM_SIZE;
	while (origin != dest)
	{
		ft_putchar(' ');
		if (MEM[origin] < 16)
			ft_putchar('0');
		ft_putnbr_base(MEM[origin], "0123456789abcdef", 1);
		origin = (origin + 1) % MEM_SIZE;
	}
	ft_putstr(" \n");
}
