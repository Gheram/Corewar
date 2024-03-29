/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:04:01 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 21:38:49 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *before;

	if (*alst == NULL || alst == NULL)
		return ;
	tmp = *alst;
	while (tmp)
	{
		before = tmp->next;
		ft_lstdelone(&tmp, del);
		tmp = before;
	}
	*alst = NULL;
}
