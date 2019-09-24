/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 11:27:58 by tigre             #+#    #+#             */
/*   Updated: 2019/08/27 17:05:22 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	detail_usage(void)
{
	write(1, "\n", 1);
	write(1, " -a   : Prints output from \"aff\" ", 33);
	write(1, "(Default is to hide it)\n", 24);
	write(1, " -d N : Dumps memory after N cycles then exits\n", 47);
	write(1, " -v N : Verbosity levels, can be added ", 39);
	write(1, "together to enable several\n", 27);
	write(1, "        - 0 : Show only essentials\n", 35);
	write(1, "        - 1 : Show lives\n", 25);
	write(1, "        - 2 : Show cycles\n", 26);
	write(1, "        - 4 : Show operations\n", 30);
	write(1, "        - 16 : Show PC movements (Except for jumps)\n", 52);
	write(1, " -n N : Attribute number to the next player\n", 44);
	write(1, " -c   : Ncurses output mode\n", 28);
	write(1, " -s   : Create \".s\" file from \".cor\" file\n", 45);
}

void		too_many_players_error(int nb_players)
{
	write(2, "Error : Too many entrant (", 26);
	ft_putnbr_fd(nb_players, 2);
	write(2, " > ", 3);
	ft_putnbr_fd(MAX_PLAYERS, 2);
	write(2, ")\n", 2);
}

void		usage(t_bool h)
{
	write(1, "Usage : ./corewar ", 18);
	write(1, "[-h] ", 5);
	write(1, "[-a] ", 5);
	write(1, "[-s] ", 5);
	write(1, "[-d N -v N | -c] ", 17);
	write(1, "<[-n N] champion.cor> <...>\n", 28);
	if (h)
		detail_usage();
}

void		no_champ_error(void)
{
	write(2, "Error : You don't send any champion\n", 36);
	usage(0);
}
