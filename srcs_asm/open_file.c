/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:36:41 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 20:42:26 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	extract_name(const char *file, size_t len)
{
	while (len > 0)
	{
		if (file[len] == '/')
		{
			len++;
			break ;
		}
		len--;
	}
	return (len);
}

int				invalide_filename(const char *file, t_storage *storage)
{
	size_t		len;
	size_t		len_file;
	size_t		dif;

	len = ft_strlen(file);
	len_file = extract_name(file, len);
	if (file[len - 2] == '.')
		dif = len - len_file - 2;
	else
		dif = len - len_file;
	DATA.filename = ft_strndup(file + len_file, dif);
	if (file[len - 1] == 's' && file[len - 2] == '.')
		return (0);
	else
		create_error(storage, NOT_POINT_S);
	return (ERROR);
}

int				open_file(const char *file, t_storage *storage)
{
	if ((DATA.file_fd = open(file, O_RDONLY)) <= -1)
		return (create_error(storage, FAILED_TO_OPEN));
	return (0);
}
