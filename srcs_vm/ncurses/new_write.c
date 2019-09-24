/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:08:01 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 16:08:03 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static t_writer_list	*writers(t_writer_list *new_writer)
{
	static t_writer_list	*new_writers = NULL;
	t_writer_list			*tmp;

	if (new_writer)
	{
		new_writer->next = new_writers;
		new_writers = new_writer;
		return (NULL);
	}
	tmp = new_writers;
	new_writers = NULL;
	return (tmp);
}

void					add_writer(unsigned char content[4],
							unsigned int writer, unsigned int where)
{
	t_writer_list	*new_writer;
	int				i;

	new_writer = malloc(sizeof(t_writer_list));
	i = -1;
	while (++i < 4)
		new_writer->content[i] = content[i];
	new_writer->writer = writer;
	new_writer->where = where;
	(void)writers(new_writer);
}

t_writer_list			*get_writers(void)
{
	return (writers(NULL));
}
