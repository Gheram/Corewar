/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:05:38 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:05:39 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	lld(int arg[3], t_process *process, t_storage *storage,
						unsigned char ocp)
{
	int		arg_print[3];

	if ((ocp >> 4) % 4 != 1)
		return ;
	if (ocp >> 6 == 2)
		process->registre[arg[1]] = arg[0];
	else if (ocp >> 6 == 3)
		process->registre[arg[1]] = read_in_ram(MEM, process->pos + arg[0], 4);
	else
		return ;
	arg_print[0] = arg[0];
	arg_print[1] = arg[1];
	if ((ocp >> 6) % 4 == 3)
		arg_print[0] = (short)arg[0];
	if (OPTION.verb_flag & 4)
		print_instr(arg_print, 1, 2, process);
	if (process->registre[arg[1]] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
