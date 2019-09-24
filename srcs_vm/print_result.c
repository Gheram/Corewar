/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:43:24 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 20:20:12 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		print_champ(t_champ champ, int *number, int num)
{
	write(1, "* Player ", 9);
	ft_putnbr(number[num] + 1);
	write(1, ", weighing ", 11);
	ft_putnbr(champ.head.prog_size);
	write(1, " bytes, \"", 9);
	write(1, champ.head.prog_name, ft_strlen(champ.head.prog_name));
	write(1, "\" (\"", 4);
	write(1, champ.head.comment, ft_strlen(champ.head.comment));
	write(1, "\") !\n", 5);
}

static void		print_winner(t_champ champ, int num)
{
	write(1, "Contestant ", 11);
	ft_putnbr(num + 1);
	write(1, ", \"", 3);
	write(1, champ.head.prog_name, ft_strlen(champ.head.prog_name));
	write(1, "\", has won !\n", 13);
}

void			introduce_champ(t_storage *storage)
{
	int		i;

	i = 0;
	write(1, "Introducing contestants...\n", 27);
	while (i < NB_CHAMP)
	{
		print_champ(CHAMP[i], OPTION.number, i);
		i++;
	}
}

void			print_result(t_storage *storage)
{
	if (storage->last_live == 0)
		storage->last_live = NB_CHAMP;
	print_winner(CHAMP[storage->last_live - 1],
	OPTION.number[storage->last_live - 1]);
}

void			print_verb(unsigned int cycle)
{
	write(1, "It is now cycle ", 16);
	ft_putnbr(cycle);
	write(1, "\n", 1);
}
