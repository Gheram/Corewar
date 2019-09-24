/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:57:55 by tigre             #+#    #+#             */
/*   Updated: 2019/09/18 15:02:07 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	void	free_label(t_label *label, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		ft_bzero(&label[i], sizeof(t_label));
		i++;
	}
}

void			free_corfile(t_storage *storage)
{
	free(COR.name);
	free_label(COR.lab_cmd, DATA.call_label);
	free_label(COR.label, DATA.total_label);
	free(COR.lab_cmd);
	free(COR.label);
	free(BODY);
	ft_bzero(&COR, sizeof(t_corfile));
}
