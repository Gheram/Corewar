/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:27:11 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 19:52:29 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool		is_opc(t_storage *storage, t_process *content)
{
	if (MEM[content->pos] >= 0x01 && MEM[content->pos] <= 0x10)
	{
		content->opc = MEM[content->pos];
		content->wcycle = g_op_tab[content->opc - 1].cycle_count - 1;
		return (false);
	}
	return (true);
}

void		init_number(int *tab)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		tab[i] = i;
		i++;
	}
}
