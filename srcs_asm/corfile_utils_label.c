/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corfile_utils_label.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 09:58:45 by tigre             #+#    #+#             */
/*   Updated: 2019/09/18 14:52:38 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			find_label(t_storage *storage, int i, unsigned short *val)
{
	size_t			j;

	j = 0;
	while (j < DATA.total_label)
	{
		if (ft_strcmp(COR.lab_cmd[i].name, COR.label[j].name) == 0)
		{
			*val = COR.label[j].pos;
			return (0);
		}
		j++;
	}
	return (1);
}

static void			put_in_body(t_storage *storage, int i, unsigned short val)
{
	unsigned short	pos;

	pos = COR.lab_cmd[i].pos;
	if (COR.lab_cmd[i].size == 4)
		pos += 2;
	if (val > pos)
	{
		val -= COR.lab_cmd[i].index;
		BODY[pos] = val >> 8;
		BODY[pos + 1] = val;
	}
	else
	{
		val = 65535 - (COR.lab_cmd[i].index - val) + 1;
		BODY[pos] = val >> 8;
		BODY[pos + 1] = val;
	}
}

int					replace_label(t_storage *storage)
{
	size_t			i;
	unsigned short	val;

	i = 0;
	val = 0;
	while (i < DATA.call_label)
	{
		if (find_label(storage, i, &val))
			return (1);
		put_in_body(storage, i, val);
		i++;
	}
	return (0);
}

void				index_lab(int dir_type, t_storage *storage, char *label)
{
	COR.lab_cmd[COR.i].pos = HEADER.prog_size;
	if (*label == '%')
	{
		COR.lab_cmd[COR.i].name = label + 2;
		COR.lab_cmd[COR.i].size = 4 - (2 * dir_type);
	}
	else
	{
		COR.lab_cmd[COR.i].name = label + 1;
		COR.lab_cmd[COR.i].size = 2;
	}
	HEADER.prog_size += COR.lab_cmd[COR.i].size;
	COR.i++;
}

void				mem_lab_pos(t_storage *storage, char *label)
{
	COR.label[COR.j].pos = HEADER.prog_size;
	COR.label[COR.j].name = label;
	COR.j++;
}
