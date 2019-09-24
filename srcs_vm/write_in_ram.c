/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_ram.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:06:43 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:06:46 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	write_in_ram(t_storage *storage, int pos, unsigned int content,
				unsigned int player_id)
{
	int				i;
	unsigned char	str[4];

	i = 4;
	if (pos < 0)
		pos = MEM_SIZE + (pos % MEM_SIZE);
	while (i--)
	{
		str[i] = content % 256;
		MEM[(pos + i) % MEM_SIZE] = str[i];
		PROPERTY[(pos + i) % MEM_SIZE] = player_id;
		content = content >> 8;
	}
	add_writer(str, player_id, pos % MEM_SIZE);
}
