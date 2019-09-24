/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:28:41 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/18 15:21:58 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	void	clean_quit(t_storage *storage)
{
	if (storage->listerror != NULL)
	{
		print_msg_error(storage);
		clean_error(storage);
	}
	clean(storage);
	exit(0);
}

static void		init_storage(t_storage *storage)
{
	ft_bzero(&storage->data, sizeof(t_data));
	ft_bzero(&storage->header, sizeof(t_header));
	ft_bzero(&storage->cor_file, sizeof(t_corfile));
	storage->list_cmd = NULL;
}

int				main(int argc, char const *argv[])
{
	int			i;
	t_storage	storage;

	i = 1;
	if (argc > 1)
	{
		storage.listerror = NULL;
		while (i < argc)
		{
			init_storage(&storage);
			if (invalide_filename(argv[i], &storage) != ERROR)
				if (open_file(argv[i], &storage) != ERROR)
					if (read_header(&storage) != ERROR)
						if (read_body(&storage) != ERROR)
							if (create_corfile(&storage) != ERROR)
								print_create_msg(&storage);
			clean(&storage);
			clean_data(&storage);
			i++;
		}
	}
	else
		return (0);
	clean_quit(&storage);
	return (0);
}
