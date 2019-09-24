/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 20:02:54 by tigre             #+#    #+#             */
/*   Updated: 2019/08/27 16:14:57 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			ft_error(t_storage *storage, char *name, int error, int i)
{
	if (error == MALLOC)
		malloc_error();
	if (error == FD)
		fd_error(name);
	if (error == CHAMP_SIZE)
		size_error(CHAMP[i], name);
	if (error == MAGIC)
		magic_error(CHAMP[i], name);
	if (error == EXT)
		ext_error(name);
	if (error == TOO_MANY_PLAYERS)
		too_many_players_error(NB_CHAMP);
	if (error == USAGE)
		usage(FLAG & HELP);
	if (error == NO_CHAMP)
		no_champ_error();
	clean(storage);
	exit(1);
}
