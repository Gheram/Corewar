/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:51:12 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 19:34:01 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					main(int ac, char **av)
{
	t_storage		storage;

	ft_bzero(&storage, sizeof(t_storage));
	get_options(&storage, ac, av);
	if (storage.option.flag & HELP)
		ft_error(&storage, NULL, USAGE, 0);
	get_champs(ac, av, &storage);
	set_up_mem(&storage);
	init_process(&storage);
	introduce_champ(&storage);
	if (storage.option.flag & DSP)
		init(&storage);
	start(&storage);
	if (!(storage.option.flag & DUMP))
		print_result(&storage);
	clean(&storage);
	return (0);
}
