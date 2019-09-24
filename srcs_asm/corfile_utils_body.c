/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corfile_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:53:38 by tigre             #+#    #+#             */
/*   Updated: 2019/09/15 19:38:57 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	fill_tab(t_storage *storage, long int val, int n)
{
	if (n == 2)
	{
		if (val < 0)
			val = 0xffff + val + 1;
		val = (unsigned short)val;
		BODY[HEADER.prog_size] = val >> 8;
		BODY[HEADER.prog_size + 1] = val;
	}
	else if (n == 4)
	{
		if (val < 0)
			val = 0xffffffff + val + 1;
		val = (unsigned int)val;
		BODY[HEADER.prog_size] = val >> 24;
		BODY[HEADER.prog_size + 1] = val >> 16;
		BODY[HEADER.prog_size + 2] = val >> 8;
		BODY[HEADER.prog_size + 3] = val;
	}
	HEADER.prog_size += n;
	return (0);
}

int			find_cmd(char *arg, t_storage *storage)
{
	size_t	i;

	i = 0;
	while (ft_strcmp(arg, g_op_tab[i].name) != 0)
		i++;
	BODY[HEADER.prog_size] = i + 1;
	HEADER.prog_size++;
	return (i + 1);
}

void		calc_ocp(t_cmd *cmd, t_storage *storage)
{
	BODY[HEADER.prog_size] = (cmd->opt & 0x3) * 0x40;
	BODY[HEADER.prog_size] += (cmd->opt >> 8 & 0x3) * 0x10;
	BODY[HEADER.prog_size] += (cmd->opt >> 16 & 0x3) * 0x4;
	HEADER.prog_size++;
}

int			find_arg(t_cmd *cmd, size_t i, t_storage *storage, int n)
{
	long int	val;

	if ((cmd->opt >> ((i - 1) * 8) & 0x3) == 1)
	{
		BODY[HEADER.prog_size] = ft_atoi(cmd->arg[i] + 1);
		HEADER.prog_size++;
	}
	else if ((cmd->opt >> ((i - 1) * 8) & 0x3) == 2)
	{
		val = g_op_tab[n - 1].dir_type ? 2 : 4;
		return (fill_tab(storage, ft_latoi(cmd->arg[i] + 1), val));
	}
	else if ((cmd->opt >> ((i - 1) * 8) & 0x3) == 3)
		return (fill_tab(storage, ft_latoi(cmd->arg[i]), 2));
	return (0);
}
