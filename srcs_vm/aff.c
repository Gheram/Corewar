/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:04:47 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/17 22:16:43 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	aff(int arg[3], t_process *process, t_storage *storage,
						unsigned char ocp)
{
	if (FLAG & AFF)
	{
		ft_putstr("Aff: ");
		ft_putchar(process->registre[arg[0]] % 256);
		ft_putchar('\n');
	}
	if (process->registre[arg[0]] % 256 == 0)
		process->carry = 1;
	else
		process->carry = 0;
	(void)storage;
	(void)ocp;
}
