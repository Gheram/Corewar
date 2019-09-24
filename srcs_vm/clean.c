/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:15:08 by tigre             #+#    #+#             */
/*   Updated: 2019/08/27 16:13:43 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		champ_clear(t_storage *storage)
{
	int			i;

	i = 0;
	while (i < NB_CHAMP)
		ft_bzero(&CHAMP[i++], sizeof(t_champ));
	free(CHAMP);
}

void			free_process(void *s, size_t n)
{
	t_process	*ptr;

	ptr = (t_process*)s;
	ft_bzero(s, n);
	free(ptr);
}

void			clean(t_storage *storage)
{
	free(OPTION.pos);
	if (CHAMP)
		champ_clear(storage);
	if (PROCESS)
		ft_lstdel((t_list**)&PROCESS, &free_process);
}
