/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:05:14 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:05:16 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "processus.h"

static int		get_param_size(unsigned char ocp, int num_param,
								unsigned char short_d, unsigned char instruc)
{
	if (g_op_tab[instruc - 1].ocp)
	{
		ocp = (ocp >> ((3 - num_param) * 2)) % 4;
		if (ocp == 1)
			return (1);
		if (ocp == 3)
			return (2);
		if (ocp == 2 && short_d)
			return (2);
		if (ocp == 2)
			return (4);
	}
	else
	{
		if (g_op_tab[instruc - 1].bnry_args[num_param] == T_REG)
			return (1);
		if (g_op_tab[instruc - 1].bnry_args[num_param] == T_IND)
			return (2);
		if (g_op_tab[instruc - 1].bnry_args[num_param] == T_DIR && short_d)
			return (2);
		return (4);
	}
	return (0);
}

static void		loop_param(t_storage *storage, t_process *process,
							t_format_args_norme *fan)
{
	while (++(fan->i) < g_op_tab[process->opc - 1].nb_arg)
	{
		fan->param_size = get_param_size(fan->ocp, fan->i,
						g_op_tab[process->opc - 1].dir_type, process->opc);
		if (fan->param_size == 0 || (fan->param_size == 1 && MEM[fan->pos + 1]
			> REG_NUMBER) || (fan->param_size == 1 && MEM[fan->pos + 1] == 0))
		{
			fan->exec = 0;
			if (fan->param_size == 0)
				continue;
		}
		fan->pos = (fan->pos + 1) % MEM_SIZE;
		fan->arg[fan->i] = MEM[fan->pos];
		while (--(fan->param_size) > 0)
		{
			fan->pos = (fan->pos + 1) % MEM_SIZE;
			fan->arg[fan->i] = (fan->arg[fan->i] << 8) + MEM[fan->pos];
		}
	}
}

void			format_args(t_storage *storage, t_process *process)
{
	t_format_args_norme		fan;

	fan.exec = 1;
	fan.i = -1;
	fan.ocp = 0;
	fan.pos = process->pos;
	if (g_op_tab[process->opc - 1].ocp)
	{
		fan.pos = (fan.pos + 1) % MEM_SIZE;
		fan.ocp = MEM[fan.pos];
	}
	loop_param(storage, process, &fan);
	if (fan.exec)
		g_processus[process->opc](fan.arg, process, storage, fan.ocp);
	if ((process->opc != 9 || process->carry == 0) && OPTION.verb_flag & 16)
		print_movement(process->pos, (fan.pos + 1) % MEM_SIZE, storage);
	if (process->opc != 9 || process->carry == 0)
		process->pos = (fan.pos + 1) % MEM_SIZE;
}
