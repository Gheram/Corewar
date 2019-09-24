/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:39:21 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 19:08:17 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		uint_to_uchar(unsigned char *body, unsigned int n, size_t i)
{
	body[i] = n;
	body[i + 1] = n >> 8;
	body[i + 2] = n >> 16;
	body[i + 3] = n >> 24;
}

static int		get_head(int fd, t_header *head)
{
	int			ret;

	ret = read(fd, head, sizeof(t_header));
	head->magic = swap_int_bit(head->magic);
	head->prog_size = swap_int_bit(head->prog_size);
	if (head->magic != COREWAR_EXEC_MAGIC)
		return (MAGIC);
	if (head->prog_size > CHAMP_MAX_SIZE)
		return (CHAMP_SIZE);
	return (0);
}

static int		get_body(int fd, t_champ *champ, int id)
{
	int			buf[CHAMP_MAX_SIZE];
	size_t		i;
	size_t		ret;

	i = 0;
	ret = read(fd, buf, CHAMP_MAX_SIZE);
	while (i < ret)
	{
		uint_to_uchar(champ->body, buf[i / 4], i);
		i += 4;
	}
	champ->body_size = ret;
	champ->id = id;
	champ->live = true;
	return (0);
}

int				get_champ_info(char *name, t_champ *champ, int id)
{
	int			fd;
	int			error;

	if ((fd = open(name, O_RDONLY)) <= -1)
		return (FD);
	if (ft_strcmp(name + ft_strlen(name) - 3, "cor") != 0)
		return (EXT);
	if ((error = get_head(fd, &champ->head)))
		return (error);
	if ((error = get_body(fd, champ, id)))
		return (error);
	close(fd);
	return (0);
}
