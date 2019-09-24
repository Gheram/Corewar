/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:04:03 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:04:07 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	add(int arg[3], t_process *process, t_storage *storage,
					unsigned char ocp)
{
	int				arg_print[3];

	if ((ocp >> 2) % 4 != 1 || (ocp >> 4) % 4 != 1 || (ocp >> 6) % 4 != 1)
		return ;
	arg_print[0] = arg[0];
	arg_print[1] = arg[1];
	arg_print[2] = arg[2];
	process->registre[arg[2]] = process->registre[arg[0]] +
								process->registre[arg[1]];
	if (OPTION.verb_flag & 4)
		print_instr(arg_print, 2, 3, process);
	if (process->registre[arg[2]] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	(void)storage;
	(void)ocp;
}
