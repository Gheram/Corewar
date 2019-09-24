/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_processus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:02:40 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 19:36:31 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					create_process(t_storage *storage, t_process process)
{
	t_process_lst	*new;

	if (!(new = (t_process_lst*)ft_lstnew(&process, sizeof(t_process))))
		return (MALLOC);
	ft_lstpush_front((t_list**)&PROCESS, (t_list*)new);
	return (0);
}

void				init_process(t_storage *storage)
{
	int				i;
	int				error;
	t_process		process;

	i = 0;
	ft_bzero(&process, sizeof(t_process));
	process.live = true;
	while (i < NB_CHAMP)
	{
		process.pos = (MEM_SIZE / NB_CHAMP) * i;
		process.owner = i + 1;
		process.id = i + 1;
		process.registre[1] = -i - 1;
		if ((error = create_process(storage, process)))
			ft_error(storage, NULL, error, 0);
		i++;
	}
	DISPLAY.process = NB_CHAMP;
}
