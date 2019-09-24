/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:06:02 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:06:05 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_args(unsigned char dest, int i, t_process *process, int arg[3])
{
	ft_putchar(' ');
	if (dest == 100 && i == 1)
	{
		if (arg[i] == 1)
			ft_putstr("OK");
		else
			ft_putstr("FAILED");
	}
	else
	{
		if (g_op_tab[process->opc - 1].bnry_args[i] == T_REG)
			ft_putchar('r');
		if (dest == 200 && i == 1)
			ft_putchar('(');
		ft_putnbr(arg[i]);
		if (dest == 200 && i == 1)
			ft_putchar(')');
	}
}

void	print_instr(int arg[3], unsigned char dest, unsigned char nb_arg,
				t_process *process)
{
	int		i;
	int		id;

	ft_putchar('P');
	i = -1;
	id = process->id;
	while (id > 0)
	{
		++i;
		id /= 10;
	}
	while (++i < 5)
		ft_putchar(' ');
	ft_putnbr(process->id);
	ft_putstr(" | ");
	ft_putstr(g_op_tab[process->opc - 1].name);
	i = -1;
	while (++i < nb_arg)
		print_args(dest, i, process, arg);
	ft_putchar('\n');
}
