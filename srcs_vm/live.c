/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:05:35 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:05:37 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	print_life(int player_id, t_champ champ)
{
	ft_putstr("Player ");
	ft_putnbr(player_id);
	ft_putstr(" (");
	ft_putstr(champ.head.prog_name);
	ft_putendl(") is said to be alive");
}

void	live(int arg[3], t_process *process, t_storage *storage,
				unsigned char ocp)
{
	int		i;
	int		arg_print[3];

	arg_print[0] = arg[0];
	i = (-arg[0]) - 1;
	process->live = true;
	CYCLE_INFO.nb_live++;
	if (OPTION.verb_flag & 4)
		print_instr(arg_print, 5, 1, process);
	if (-arg[0] > storage->nb_champ || (-arg[0]) <= 0)
		return ;
	if (OPTION.verb_flag & 1)
		print_life(i + 1, CHAMP[i]);
	CHAMP[i].live = true;
	storage->last_live = i + 1;
	DISPLAY.last_live[i] = DISPLAY.cycle;
	++(DISPLAY.live_current[i]);
	(void)ocp;
}
