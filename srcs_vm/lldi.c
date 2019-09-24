/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:05:40 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:05:42 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void		print_load(short param1, short param2, int pos)
{
	ft_putstr("       | -> load from ");
	ft_putnbr(param1);
	ft_putstr(" + ");
	ft_putnbr(param2);
	ft_putstr(" = ");
	ft_putnbr(param1 + param2);
	ft_putstr(" (with pc and mod ");
	ft_putnbr(pos + ((short)(param1 + param2)));
	ft_putstr(")\n");
}

static void		set_print_direct(int *arg, int (*arg_print)[3], char ocp)
{
	if ((ocp >> 6) % 4 == 3)
		(*arg_print)[0] = (short)arg[0];
	if ((ocp >> 4) % 4 == 3)
		(*arg_print)[1] = (short)arg[1];
}

static short	set_param(int arg, t_process *process, t_storage *storage,
							unsigned char ocp)
{
	if ((ocp >> 6) % 4 == 1)
		return (process->registre[arg]);
	else if ((ocp >> 6) % 4 == 3)
		return (read_in_ram(MEM, process->pos + arg, 4));
	else
		return (arg);
}

void			update_carry(int i, t_process *process)
{
	if (i == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void			lldi(int arg[3], t_process *process, t_storage *storage,
						unsigned char ocp)
{
	short	param1;
	short	param2;
	int		arg_print[3];

	if ((ocp >> 2) % 4 != 1)
		return ;
	if ((ocp >> 4) % 4 != 2 && (ocp >> 4) % 4 != 1)
		return ;
	arg_print[0] = (short)arg[0];
	arg_print[1] = (short)arg[1];
	arg_print[2] = (short)arg[2];
	param1 = set_param(arg[0], process, storage, ocp);
	if ((ocp >> 6) % 4 == 1)
		arg_print[0] = param1;
	param2 = set_param(arg[1], process, storage, ocp);
	if ((ocp >> 4) % 4 == 1)
		arg_print[1] = param2;
	set_print_direct(arg, &arg_print, ocp);
	if (OPTION.verb_flag & 4)
		print_instr(arg_print, 2, 3, process);
	if (OPTION.verb_flag & 4)
		print_load(param1, param2, process->pos);
	process->registre[arg[2]] = read_in_ram(MEM, process->pos +
						(short)(param1 + param2), 4);
	update_carry(process->registre[arg[2]], process);
}
