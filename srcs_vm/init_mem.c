/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 18:44:04 by tigre             #+#    #+#             */
/*   Updated: 2019/08/27 16:18:30 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void			init_mem(unsigned char *tab)
{
	size_t			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		tab[i] = 0;
		i++;
	}
}

static void			load_champ(t_storage *storage, t_champ champ, int num)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = (MEM_SIZE / NB_CHAMP) * num;
	while (i < champ.body_size)
	{
		MEM[j] = champ.body[i];
		PROPERTY[j] = champ.id;
		i++;
		j++;
	}
}

void				set_up_mem(t_storage *storage)
{
	int				i;

	i = 0;
	init_mem(MEM);
	init_mem(PROPERTY);
	while (i < NB_CHAMP)
	{
		load_champ(storage, CHAMP[i], i);
		i++;
	}
}
