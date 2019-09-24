/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 14:46:43 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 19:06:43 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_champ			*init_champ(t_champ *champ, size_t size)
{
	size_t		i;

	i = 0;
	if (!(champ = (t_champ*)malloc(sizeof(t_champ) * size)))
		return (NULL);
	while (i < size)
	{
		ft_bzero(&champ[i], sizeof(t_champ));
		ft_bzero(&champ[i].head, sizeof(t_header));
		i++;
	}
	return (champ);
}
