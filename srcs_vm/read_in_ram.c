/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_in_ram.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:06:14 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 14:06:16 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

unsigned int	read_in_ram(unsigned char ram[MEM_SIZE], int pos, int nb_oct)
{
	unsigned int	content;
	int				i;

	content = 0;
	i = -1;
	if (pos < 0)
		pos = MEM_SIZE + (pos % MEM_SIZE);
	while (++i < nb_oct)
		content = (content << 8) + ram[(pos + i) % MEM_SIZE];
	return (content);
}
