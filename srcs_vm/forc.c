/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:05:10 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:05:12 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	forc(int arg[3], t_process *process, t_storage *storage,
						unsigned char ocp)
{
	t_process	new_proc;
	int			i;
	int			pos;
	int			arg_print[3];

	arg_print[0] = (short)arg[0];
	i = 0;
	ft_bzero(&new_proc, sizeof(t_process));
	pos = process->pos + (((short)arg[0]) % IDX_MOD);
	if (pos < 0)
		pos = MEM_SIZE + pos;
	while (++i <= REG_NUMBER)
		new_proc.registre[i] = process->registre[i];
	new_proc.opc = 0;
	new_proc.live = process->live;
	new_proc.carry = process->carry;
	new_proc.owner = process->owner;
	new_proc.pos = pos % MEM_SIZE;
	arg_print[1] = pos;
	DISPLAY.process += 1;
	new_proc.id = DISPLAY.process;
	if (OPTION.verb_flag & 4)
		print_instr(arg_print, 200, 2, process);
	create_process(storage, new_proc);
	(void)ocp;
}
