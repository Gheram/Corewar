/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:27:25 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 19:36:56 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void			print_line_num(unsigned int *line)
{
	write(1, "0x0", 3);
	if (*line == 0)
		write(1, "00", 2);
	else if (*line < 0x0100)
		write(1, "0", 1);
	ft_putnbr_base(*line, "0123456789abcdef", 1);
	write(1, " : ", 3);
	(*line) += 0x40;
}

void				print_mem(unsigned char *mem)
{
	int				x;
	unsigned int	line;

	x = 0;
	line = 0;
	print_line_num(&line);
	while (x < MEM_SIZE)
	{
		if (mem[x] < 16)
		{
			write(1, "0", 1);
			ft_putnbr_base(mem[x], "0123456789abcdef", 1);
		}
		else
			ft_putnbr_base(mem[x], "0123456789abcdef", 1);
		if ((x + 1) % 64 == 0)
		{
			write(1, "\n", 1);
			if (line <= 0x0fc0)
				print_line_num(&line);
		}
		else
			write(1, " ", 1);
		x++;
	}
}
