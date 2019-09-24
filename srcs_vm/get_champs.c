/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:19:20 by tigre             #+#    #+#             */
/*   Updated: 2019/08/27 11:46:32 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				get_champs(int ac, char **av, t_storage *storage)
{
	int				i;
	int				j;
	int				error;

	i = 1;
	j = 0;
	if (NB_CHAMP == 0)
		ft_error(storage, NULL, NO_CHAMP, 0);
	if (NB_CHAMP > MAX_PLAYERS)
		ft_error(storage, NULL, TOO_MANY_PLAYERS, 0);
	if (!(CHAMP = (t_champ*)ft_memalloc(sizeof(t_champ) * NB_CHAMP)))
		ft_error(storage, NULL, MALLOC, 0);
	while (i < ac)
	{
		if (OPTION.pos[i] == 0)
		{
			if ((error = get_champ_info(av[i], &CHAMP[j], j + 1)))
				ft_error(storage, av[i], error, j);
			j++;
		}
		i++;
	}
}
