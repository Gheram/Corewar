/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:06:22 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:06:24 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void			print_store(int param1, int param2, int pos)
{
	ft_putstr("       | -> store to ");
	ft_putnbr(param1);
	ft_putstr(" + ");
	ft_putnbr(param2);
	ft_putstr(" = ");
	ft_putnbr(param1 + param2);
	ft_putstr(" (with pc and mod ");
	ft_putnbr(pos + (((short)(param1 + param2)) % IDX_MOD));
	ft_putstr(")\n");
}

static void		set_print_direct(int *arg, int (*arg_print)[3], char ocp)
{
	if ((ocp >> 4) % 4 != 1)
		(*arg_print)[1] = (short)arg[1];
	if ((ocp >> 2) % 4 != 1)
		(*arg_print)[2] = (short)arg[2];
}

static short	set_param(int arg, t_process *process, t_storage *storage,
							unsigned char ocp)
{
	if ((ocp >> 4) % 4 == 1)
		return (process->registre[arg]);
	else if ((ocp >> 4) % 4 == 3)
		return (read_in_ram(MEM, process->pos + (arg % IDX_MOD), 4));
	else
		return (arg);
}

void			sti(int arg[3], t_process *process, t_storage *storage,
							unsigned char ocp)
{
	short	param2;
	short	param3;
	int		arg_print[3];

	if ((ocp >> 6) % 4 != 1)
		return ;
	arg_print[0] = arg[0];
	param2 = set_param(arg[1], process, storage, ocp);
	if ((ocp >> 4) % 4 == 1)
		arg_print[1] = process->registre[arg[1]];
	if ((ocp >> 2) % 4 == 1)
		param3 = process->registre[arg[2]];
	else if ((ocp >> 2) % 4 == 2)
		param3 = arg[2];
	else
		return ;
	if ((ocp >> 2) % 4 == 1)
		arg_print[2] = process->registre[arg[2]];
	set_print_direct(arg, &arg_print, ocp);
	if (OPTION.verb_flag & 4)
		print_instr(arg_print, 0, 3, process);
	if (OPTION.verb_flag & 4)
		print_store(arg_print[1], arg_print[2], process->pos);
	write_in_ram(storage, process->pos + ((short)(param3 + param2) % IDX_MOD),
					process->registre[arg[0]], process->owner);
}
