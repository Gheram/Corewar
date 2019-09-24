/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:59:35 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 20:59:50 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memdup(void const *content, size_t content_size)
{
	void	*copy;

	if (content == NULL)
		return (NULL);
	if (!(copy = ft_memalloc(content_size)))
		return (NULL);
	ft_memcpy(copy, content, content_size);
	return (copy);
}
