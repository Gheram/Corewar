/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_corfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <tigre@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:32:09 by tigre             #+#    #+#             */
/*   Updated: 2019/09/18 15:03:13 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				write_in_corfile(unsigned char *tab, size_t size, int fd)
{
	size_t			i;

	i = 0;
	while (i < size)
	{
		write(fd, &tab[i], 1);
		i++;
	}
}

static void			write_head(t_storage *storage)
{
	write_magic(COREWAR_EXEC_MAGIC, FD);
	write_prog_name(HEADER.prog_name, FD);
	write_prog_size(HEADER.prog_size, FD);
	write_comment(HEADER.comment, FD);
}

static int			convert_data(t_cmd *cmd, t_storage *storage)
{
	int				i;
	int				opc;

	i = 1;
	if (cmd->label)
		mem_lab_pos(storage, cmd->label);
	else
	{
		opc = find_cmd(cmd->arg[0], storage);
		if (cmd->opt >> 24)
			COR.lab_cmd[COR.i].index = HEADER.prog_size - 1;
		if (g_op_tab[opc - 1].ocp)
			calc_ocp(cmd, storage);
		while (i <= cmd->nb)
		{
			if (i == cmd->opt >> 24)
				index_lab(g_op_tab[opc - 1].dir_type, storage, cmd->arg[i]);
			else if (find_arg(cmd, i, storage, opc))
				return (1);
			i++;
		}
	}
	return (0);
}

static int			set_body(t_storage *storage)
{
	t_list_cmd		*ptr;

	ptr = CMD;
	while (ptr)
	{
		if (convert_data(ptr->content, storage))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int					create_corfile(t_storage *storage)
{
	if (DATA.call_label)
		if (!(COR.lab_cmd =
		(t_label*)ft_memalloc(sizeof(t_label) * DATA.call_label)))
			return (create_error(storage, MALLOC_ERROR));
	if (DATA.total_label)
		if (!(COR.label =
		(t_label*)ft_memalloc(sizeof(t_label) * DATA.total_label)))
			return (create_error(storage, MALLOC_ERROR));
	if (!(COR.body =
	(unsigned char*)ft_memalloc(sizeof(unsigned char) * (DATA.nb_cmd * 8))))
		return (create_error(storage, MALLOC_ERROR));
	set_body(storage);
	if (replace_label(storage))
		return (create_error(storage, LABEL_NOT_FOUND));
	if (!(COR.name = ft_strjoin(DATA.filename, ".cor")))
		return (create_error(storage, MALLOC_ERROR));
	if ((FD = open(COR.name, O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
		return (create_error(storage, FAILED_TO_CREATE_FILE));
	write_head(storage);
	write_in_corfile(BODY, (size_t)HEADER.prog_size, FD);
	close(FD);
	return (0);
}
