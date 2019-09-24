/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:06:17 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:06:19 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	st(int arg[3], t_process *process, t_storage *storage,
						unsigned char ocp)
{
	int		arg_print[3];

	arg_print[0] = arg[0];
	if ((ocp >> 6) % 4 != 1)
		return ;
	if ((ocp >> 4) % 4 == 1)
	{
		arg_print[1] = arg[1];
		process->registre[arg[1]] = process->registre[arg[0]];
		if (OPTION.verb_flag & 4)
			print_instr(arg_print, 0, 2, process);
	}
	else if ((ocp >> 4) % 4 == 3)
	{
		arg_print[1] = (short)arg[1];
		write_in_ram(storage, process->pos + ((short)arg[1] % IDX_MOD),
						process->registre[arg[0]], process->owner);
		if (OPTION.verb_flag & 4)
			print_instr(arg_print, 0, 2, process);
	}
}
