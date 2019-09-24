/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 15:20:20 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/18 15:09:23 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			clean_data(t_storage *storage)
{
	ft_strdel(&DATA.filename);
	close(DATA.file_fd);
}

static void		free_cmd(void *s, size_t n)
{
	t_cmd		*ptr;
	int			i;

	ptr = (t_cmd*)s;
	i = 1;
	while (i <= ptr->nb)
		free(ptr->arg[i++]);
	free(ptr->arg);
	free(ptr->label);
	ft_bzero(s, n);
	free(ptr);
}

static void		free_error(void *s, size_t n)
{
	t_error		*ptr;

	ptr = (t_error*)s;
	free(ptr->filename);
	ft_bzero(s, n);
	free(ptr);
}

void			clean_error(t_storage *storage)
{
	if (LIST_ERRO)
		ft_lstdel((t_list**)&LIST_ERRO, &free_error);
	free(LIST_ERRO);
}

void			clean(t_storage *storage)
{
	if (CMD)
		ft_lstdel((t_list**)&CMD, &free_cmd);
}
