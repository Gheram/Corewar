/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:45:44 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 19:33:41 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			get_champ_number(t_storage *storage, int arg)
{
	OPTION.number[OPTION.champ_index] = arg;
	OPTION.champ_index++;
}

static	int			find_option(unsigned int options, char c)
{
	int				ret;

	ret = 0;
	if (c == 'd')
		ret = (options & DUMP) ? -1 : 1;
	else if (c == 'n')
		ret = (options & CHAMP_NUM) ? -1 : 2;
	else if (c == 'v')
		ret = (options & VERB) ? -1 : 4;
	else if (c == 'c')
		ret = (options & DSP) ? -1 : 8;
	else if (c == 'h')
		ret = (options & HELP) ? -1 : 16;
	else if (c == 'a')
		ret = (options & AFF) ? -1 : 32;
	else if (c == 's')
		ret = (options & AFF) ? -1 : 64;
	return (ret);
}

static void			read_option(t_storage *storage, char *arg, int *mem)
{
	size_t			i;

	i = 1;
	if (*mem >= 1 && *mem <= 4)
	{
		*mem == DUMP ? OPTION.nbr_cycles = ft_atoi(arg) : *mem;
		*mem == CHAMP_NUM ? get_champ_number(storage, ft_atoi(arg)) : *mem;
		*mem == VERB ? OPTION.verb_flag = ft_atoi(arg) : *mem;
		*mem = -1;
	}
	else if (*mem == 2)
	{
		*mem = -1;
	}
	else
	{
		while (arg[i])
		{
			if ((*mem = find_option(FLAG, arg[i])) > 0)
				if (*mem != CHAMP_NUM)
					FLAG += *mem;
			i++;
		}
	}
}

void				get_options(t_storage *storage, int ac, char **av)
{
	int				i;
	int				mem;

	i = 1;
	mem = 0;
	ft_bzero(&OPTION, sizeof(t_option));
	ac < 2 ? ft_error(storage, NULL, USAGE, 0) : ac;
	if (!(OPTION.pos = (int*)ft_memalloc(sizeof(int) * ac)))
		ft_error(storage, NULL, MALLOC, 0);
	init_number(OPTION.number);
	NB_CHAMP = ac - 1;
	while (i < ac)
	{
		if (av[i][0] == '-' || (mem >= 1 && mem <= 4))
			read_option(storage, av[i], &mem);
		else
			mem = 0;
		if (mem)
		{
			OPTION.pos[i] = 1;
			NB_CHAMP--;
		}
		i++;
	}
}
