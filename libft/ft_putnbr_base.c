/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 22:11:52 by tigre             #+#    #+#             */
/*   Updated: 2019/08/26 18:21:10 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_base(int n, char *base, int fd)
{
	size_t		size;
	long int	nb;

	size = ft_strlen(base);
	nb = n;
	if (nb < 0)
	{
		nb = nb * (-1);
		ft_putchar_fd('-', fd);
	}
	if (nb >= (long int)size)
	{
		ft_putnbr_base(nb / size, base, fd);
		ft_putnbr_base(nb % size, base, fd);
	}
	else
		ft_putchar_fd(base[nb], fd);
}
