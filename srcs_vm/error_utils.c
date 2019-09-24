/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 21:33:52 by tigre             #+#    #+#             */
/*   Updated: 2019/08/27 12:41:37 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		malloc_error(void)
{
	write(2, "Can't perform malloc\n", 21);
}

void		fd_error(char *name)
{
	write(2, "Can't read source file ", 23);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
}

void		size_error(t_champ champ, char *name)
{
	write(2, "Error : File ", 13);
	write(2, name, ft_strlen(name));
	write(2, " has too large a code (", 23);
	ft_putnbr_fd(champ.head.prog_size, 2);
	write(2, " bytes > ", 9);
	ft_putnbr_fd(CHAMP_MAX_SIZE, 2);
	write(2, " bytes)\n", 8);
}

void		magic_error(t_champ champ, char *name)
{
	write(2, "Error : File ", 13);
	write(2, name, ft_strlen(name));
	write(2, " don't have the good magic number (0x", 37);
	ft_putnbr_base(champ.head.magic, "0123456789ABCDEF", 2);
	write(2, " != 0x", 6);
	ft_putnbr_base(COREWAR_EXEC_MAGIC, "0123456789ABCDEF", 2);
	write(2, ")\n", 2);
}

void		ext_error(char *name)
{
	write(2, "Error : File ", 13);
	write(2, name, ft_strlen(name));
	write(2, " have to be a \".cor\" file\n", 26);
}
