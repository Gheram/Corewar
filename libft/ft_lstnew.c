/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:15:55 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 21:37:07 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list *my_list;

	if (!(my_list = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		my_list->content = ft_memdup(content, content_size);
		my_list->content_size = content_size;
	}
	else
	{
		my_list->content = NULL;
		my_list->content_size = 0;
	}
	my_list->next = NULL;
	return (my_list);
}
