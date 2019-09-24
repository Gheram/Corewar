/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:04:53 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:04:55 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static int	set_param1(int arg, t_process *process, t_storage *storage,
					unsigned char ocp)
{
	if ((ocp >> 6) % 4 == 1)
		return (process->registre[arg]);
	else if ((ocp >> 6) % 4 == 3)
		return (read_in_ram(MEM, process->pos + (arg % IDX_MOD), 4));
	else
		return (arg);
}

static int	set_param2(int arg, t_process *process, t_storage *storage,
					unsigned char ocp)
{
	if ((ocp >> 4) % 4 == 1)
		return (process->registre[arg]);
	else if ((ocp >> 4) % 4 == 3)
		return (read_in_ram(MEM, process->pos + (arg % IDX_MOD), 4));
	else
		return (arg);
}

void		and(int arg[3], t_process *process, t_storage *storage,
						unsigned char ocp)
{
	int		param1;
	int		param2;
	int		arg_print[3];

	if ((ocp >> 2) % 4 != 1)
		return ;
	arg_print[2] = arg[2];
	param1 = set_param1(arg[0], process, storage, ocp);
	param2 = set_param2(arg[1], process, storage, ocp);
	process->registre[arg[2]] = param1 & param2;
	arg_print[0] = param1;
	arg_print[1] = param2;
	if ((ocp >> 6) % 4 == 3)
		arg_print[0] = (short)arg[0];
	if ((ocp >> 4) % 4 == 3)
		arg_print[1] = (short)arg[1];
	if (OPTION.verb_flag & 4)
		print_instr(arg_print, 2, 3, process);
	if (process->registre[arg[2]] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
