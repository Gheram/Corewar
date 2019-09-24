/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_die_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:21:04 by tigre             #+#    #+#             */
/*   Updated: 2019/08/27 14:52:00 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		update_die_time(t_storage *storage)
{
	CYCLE_INFO.die_time = CYCLE_INFO.last_die_time;
	if (CYCLE_INFO.nb_live >= NBR_LIVE || CYCLE_INFO.wcheck == MAX_CHECKS)
	{
		CYCLE_INFO.wcheck = 0;
		CYCLE_INFO.die_time -= CYCLE_DELTA;
		if (OPTION.verb_flag & 2)
		{
			ft_putstr("Cycle to die is now ");
			ft_putnbr(CYCLE_INFO.die_time);
			ft_putchar('\n');
		}
	}
	else
		CYCLE_INFO.wcheck++;
	CYCLE_INFO.nb_live = 0;
	CYCLE_INFO.last_die_time = CYCLE_INFO.die_time;
}
