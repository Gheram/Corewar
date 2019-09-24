/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 13:48:07 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 14:43:38 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int				create_error(t_storage *storage, int index_error)
{
	t_error		error;
	t_listerror	*new_error;

	error.filename = ft_strdup(DATA.filename);
	error.num_line = DATA.num_line;
	error.index_error = index_error;
	new_error = (t_listerror*)ft_lstnew(&error, sizeof(t_error));
	ft_lstpush_back((t_list**)&LIST_ERRO, (t_list*)new_error);
	if (LIST_ERRO == NULL)
	{
		exit(0);
		return (0);
	}
	return (ERROR);
}
