/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corfile_utils_head.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:02:13 by tigre             #+#    #+#             */
/*   Updated: 2019/09/15 16:37:04 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				write_magic(unsigned int magic, int fd)
{
	unsigned char	tab[4];

	tab[0] = magic >> 24;
	tab[1] = magic >> 16;
	tab[2] = magic >> 8;
	tab[3] = magic;
	write_in_corfile(tab, 4, fd);
}

void				write_prog_name(char *name, int fd)
{
	size_t			i;
	unsigned char	c;

	i = 0;
	c = 0;
	while (i < PROG_NAME_LENGTH + 4)
	{
		if (name[i])
			write(fd, &name[i], 1);
		else
			write(fd, &c, 1);
		i++;
	}
}

void				write_prog_size(unsigned int size, int fd)
{
	unsigned char	tab[4];

	tab[0] = size >> 24;
	tab[1] = size >> 16;
	tab[2] = size >> 8;
	tab[3] = size;
	write_in_corfile(tab, 4, fd);
}

void				write_comment(char *com, int fd)
{
	size_t			i;
	unsigned char	c;

	c = 0;
	i = 0;
	while (i < COMMENT_LENGTH + 4)
	{
		if (com[i])
			write(fd, &com[i], 1);
		else
			write(fd, &c, 1);
		i++;
	}
}
