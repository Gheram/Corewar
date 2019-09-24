/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:06:51 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:07:03 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	zjmp(int arg[3], t_process *process, t_storage *storage,
					unsigned char ocp)
{
	int		pos;
	int		arg_print[3];

	arg_print[0] = (short)arg[0];
	arg_print[1] = 0;
	pos = (process->pos + ((short)arg[0]) % IDX_MOD) % MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	if (process->carry == 1)
	{
		arg_print[1] = 1;
		if (OPTION.verb_flag & 4)
			print_instr(arg_print, 100, 2, process);
		process->pos = pos;
	}
	else if (OPTION.verb_flag & 4)
		print_instr(arg_print, 100, 2, process);
	(void)storage;
	(void)ocp;
}
