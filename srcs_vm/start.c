/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 18:43:13 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 19:51:52 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			update_process(t_storage *storage, t_process_lst **begin)
{
	t_process_lst	*ptr;

	ptr = *begin;
	while (ptr)
	{
		if (ptr->content->wcycle == 1)
		{
			(ptr->content->wcycle)--;
			format_args(storage, ptr->content);
		}
		else if (ptr->content->wcycle > 1)
			(ptr->content->wcycle)--;
		else if (is_opc(storage, ptr->content))
		{
			ptr->content->pos = (ptr->content->pos + 1) % MEM_SIZE;
		}
		ptr = ptr->next;
	}
}

static void			killer(t_storage *storage, t_process_lst **begin)
{
	t_process_lst	*ptr;

	ptr = *begin;
	while (ptr)
	{
		if (ptr->content->live == false)
		{
			*begin = ptr->next;
			ft_lstdelone((t_list**)&ptr, &free_process);
			FLAG & DSP ? DISPLAY.process -= 1 : FLAG;
		}
		else
		{
			ptr->content->live = false;
			begin = &(ptr->next);
		}
		ptr = *begin;
	}
	FLAG & DSP ? print_new_cycle(storage) : FLAG;
}

void				check_opc(t_process_lst *lst, t_storage *storage)
{
	while (lst)
	{
		if (lst->content->wcycle == 0)
			is_opc(storage, lst->content);
		lst = lst->next;
	}
}

void				start(t_storage *storage)
{
	unsigned int	cycle;

	cycle = 1;
	ft_bzero(&CYCLE_INFO, sizeof(t_cycle_data));
	CYCLE_INFO.die_time = CYCLE_TO_DIE;
	CYCLE_INFO.last_die_time = CYCLE_TO_DIE;
	while (PROCESS)
	{
		FLAG & DSP ? erase_process(storage) : FLAG;
		if (CYCLE_INFO.die_time <= 0)
		{
			killer(storage, &PROCESS);
			update_die_time(storage);
		}
		if (PROCESS && OPTION.verb_flag & 2)
			print_verb(cycle);
		DISPLAY.cycle = cycle;
		update_process(storage, &PROCESS);
		if ((FLAG & DUMP) && (cycle == OPTION.nbr_cycles))
			return (print_mem(MEM));
		FLAG & DSP ? display(storage) : FLAG;
		CYCLE_INFO.die_time--;
		cycle++;
	}
}
